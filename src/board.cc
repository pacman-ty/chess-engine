#include <stdio.h>
#include <memory>
#include <cstring>
#include <random>
#include <ctime>
#include "board.h"
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "pawn.h"


Board::Board() {
    for (int i = 0; i < BOARD_MAX_WIDTH; ++i) {
        for (int j = 0; j < BOARD_MAX_HEIGHT; ++j) {
            board[i][j] = nullptr;
        }
    }
}

Board::~Board() {
    clear();
}

void Board::capture(Piece *p) {
    switch (p->getSide()) {
        case Colour::WHITE:
            for (auto it = whitePieces.begin(); it != whitePieces.end(); ++it) {
                if (p == *it) {
                    whitePieces.erase(it);
                    break;
                }
            }
            break;
        case Colour::BLACK:
            for (auto it = blackPieces.begin(); it != blackPieces.end(); ++it) {
                if (p == *it) {
                    blackPieces.erase(it);
                    break;
                }
            }
            break;
        default:
            throw std::invalid_argument("Invalid colour when capturing");
    }
    if (p) delete p;
}

void Board::placePiece(Colour side, Type t, const Position & pos) {
    if (board[pos.getX()][pos.getY()]) {
        throw std::logic_error("Invalid placement (Slot taken)");
        return;
    }
    Piece* toAdd;
    switch (t) {
        case Type::KING: toAdd = new King; break;
        case Type::QUEEN: toAdd = new Queen; break;
        case Type::ROOK: toAdd = new Rook; break;
        case Type::BISHOP: toAdd = new Bishop; break;
        case Type::KNIGHT: toAdd = new Knight; break;
        case Type::PAWN: toAdd = new Pawn; break;
        default:
            throw std::invalid_argument("Invalid type when placing piece");
    }
    toAdd->setSide(side);
    toAdd->setPos(Position{pos.getX(), pos.getY()});
    switch (side) {
        case Colour::BLACK: blackPieces.push_back(toAdd); break;
        case Colour::WHITE: whitePieces.push_back(toAdd); break;
        default:
            delete toAdd;
            throw std::invalid_argument("Invalid side when placing piece");
    }
    // Add to the board
    board[pos.getX()][pos.getY()] = toAdd;
}

void Board::removePiece(Position p) {
    if (board[p.getX()][p.getY()] == nullptr) {
        throw std::logic_error("No piece to remove");
    }
    capture(board[p.getX()][p.getY()]);
    board[p.getX()][p.getY()] = nullptr;
}

void Board::playMove(const Move & m) {
    if (!isValidMove(m)) {
        throw std::logic_error("Invalid move");
    }
    int x = m.getOldPosition().getX();
    int y = m.getOldPosition().getY();
    int newX = m.getNewPosition().getX();
    int newY = m.getNewPosition().getY(); 

    if (board[x][y] == nullptr) {
        std::cerr << "No piece to move" << std::endl;
        return;
    }

    if (m.getCapture()) { // has a target
        if (board[newX][newY] != nullptr) capture(board[newX][newY]); // delete captured piece               
    }

    board[newX][newY] = board[x][y]; // move target piece
    board[x][y] = nullptr;

    board[newX][newY]->setPos(Position{newX, newY});
}

void Board::forcePlayMove(const Move & m) {
    int x = m.getOldPosition().getX();
    int y = m.getOldPosition().getY();
    int newX = m.getNewPosition().getX();
    int newY = m.getNewPosition().getY();    
    if (m.getCapture()) { // has a target
        if (board[newX][newY] != nullptr) capture(board[newX][newY]); // delete captured piece               
    }
    board[newX][newY] = board[x][y]; // move target piece
    board[x][y] = nullptr;
    board[newX][newY]->setPos(Position{newX, newY});
}

bool Board::tryCastle(const Move & m) {
    const Piece *king = m.getTarget();
    int curX = king->getPos().getX();
    int curY = king->getPos().getY();

    bool castleRight = curX < m.getNewPosition().getX();
    Piece *piece = castleRight ? board[curX+3][curY] : piece = board[curX-3][curY];

    // Is there a piece?
    if (!piece) return false; 
    // Is the piece on the same side?
    if (piece->getSide() != king->getSide()) return false;
    // Is the piece a rook? 
    if (piece->getType() != Type::ROOK) return false;
    Rook *rook = static_cast<Rook*>(piece);
    // Has the rook moved?
    if (rook->getHasMoved()) return false;

    if (castleRight) {
        // Can king move 1 space?
        if (!isValidMove(Move{m.getOldPosition(), Position{curX+1, curY}, king, NULL})) return false;
        // Can king move 2 spaces?
        if (!isValidMove(Move{Position{curX+1, curY}, Position{curX+2, curY}, king, NULL})) return false;
        // Move king
        forcePlayMove(Move{m.getOldPosition(), Position{curX+2, curY}, king, NULL});
        // Move rook
        forcePlayMove(Move{m.getOldPosition(), Position{curX+1, curY}, rook, NULL});
    }
    else { // castle left
        // Can king move 1 space?
        if (!isValidMove(Move{m.getOldPosition(), Position{curX-1, curY}, king, NULL})) return false;
        // Can king move 2 spaces?
        if (!isValidMove(Move{m.getOldPosition(), Position{curX-2, curY}, king, NULL})) return false;
        // Can king move 3 spaces?
        if (!isValidMove(Move{m.getOldPosition(), Position{curX-3, curY}, king, NULL})) return false;
        // Move king
        forcePlayMove(Move{m.getOldPosition(), Position{curX-2, curY}, king, NULL});
        // Move rook
        forcePlayMove(Move{m.getOldPosition(), Position{curX-1, curY}, rook, NULL});
    }

    return true;
}

void Board::playMove(Position oldPos, Position newPos, Colour turn) {
    Piece *capture = board[newPos.getX()][newPos.getY()];
    Piece *target = board[oldPos.getX()][oldPos.getY()];
    if (target == nullptr) {
        throw std::logic_error("No piece to move");
    }
    if (target->getSide() != turn) {
        throw std::logic_error("Not your turn");
    }

    Move move = Move{oldPos, newPos, target, capture};
    if (move.isCastle()) {
        if (!tryCastle(Move(oldPos, newPos, target, NULL))) {
            throw std::logic_error("Can not castle");
        }
    } else {
        playMove(move);
    }
}

void Board::cloneBoard(const Board & b) {
    for (int y = BOARD_MIN_HEIGHT; y < BOARD_MAX_HEIGHT; ++y) {
        for (int x = BOARD_MIN_WIDTH; x < BOARD_MAX_WIDTH; ++x) {
            const Piece* curItem = b.getItem(x, y);
            if (!curItem) continue;
            placePiece(curItem->getSide(), curItem->getType(), curItem->getPos());     
        }
    }
}

bool Board::isValidMove(const Move & m) const {
    // check if you can go there
    const Piece *target = m.getTarget();
    if (!target) return false;
    std::vector<Move> possibleMoves = target->getPossibleMoves(board);

    bool found = false;
    for (auto p : possibleMoves) { // simple move
        if (p.getNewPosition() == m.getNewPosition()) {
            found = true;
            break;
        }
    }
    
    if (!found) {
        std::vector<Move> possibleCaptures = target->getPossibleCaptures(board);
        if (possibleCaptures.empty()) return false;
        for (auto p : possibleCaptures) { // capture move
            if (p.getNewPosition() == m.getNewPosition()) {
                found = true;
                break;
            }
    }
    }
    if (!found) return false;
    // simulate move
    std::unique_ptr<Board> temp_board{new Board};
    temp_board->cloneBoard(*this);
    temp_board->forcePlayMove(m);
    // check simulated move is validva
    return !temp_board->isCheck(target->getSide());
}

bool Board::isCheck(Colour side) const {
    switch(side) {
        case Colour::BLACK:
            for (auto p : whitePieces) { // check opposing pieces
                std::vector<Move> captures = p->getPossibleCaptures(board);
                if (captures.empty()) continue;
                for (auto cap : captures) {
                    if (cap.getCapture()->getType() == Type::KING) return true;
                }
            }
            break;
        case Colour::WHITE:
            for (auto p : blackPieces) {
                std::vector<Move> captures = p->getPossibleCaptures(board);
                if (captures.empty()) continue;
                for (auto cap : captures) {
                    if (cap.getCapture()->getType() == Type::KING) return true;
                }
            }
            break;
        default:
            throw std::invalid_argument("Invalid Colour when performing check");
            return false;
    }
    return false;
}

bool Board::isCheckmate(Colour side) const {
    switch(side) {
        case Colour::BLACK:
            for (auto p : blackPieces) {
                std::vector<Move> moves = p->getPossibleMoves(board);
                if (moves.empty()) continue;
                for (auto m : moves) {
                    if (isValidMove(m)) return false;
                }
            }
            break;
        case Colour::WHITE:
            for (auto p : whitePieces) {
                std::vector<Move> moves = p->getPossibleMoves(board);
                if (moves.empty()) continue;
                for (auto m : moves) {
                    if (isValidMove(m)) return false;
                }
            }
            break;
        default:
            throw std::invalid_argument("Invalid Colour when checking for checkmate");
            return false;
    }
    return true;
}

bool Board::isStalemate(Colour side) const {
    switch (side) {
        case Colour::BLACK:
            if (isCheck(Colour::BLACK)) return false;
            for (auto p : blackPieces) {
                std::vector<Move> moves = p->getPossibleMoves(board);
                if (moves.empty()) continue;
                for (auto m : moves) {
                    if (isValidMove(m)) return false;
                }
            }
            break;
        case Colour::WHITE:
            if (isCheck(Colour::WHITE)) return false;
            for (auto p : whitePieces) {
                std::vector<Move> moves = p->getPossibleMoves(board);
                if (moves.empty()) continue;
                for (auto m : moves) {
                    if (isValidMove(m)) return false;
                }
            }
            break;
        default:
            throw std::invalid_argument("Invalid Colour when checking for stalemate");
            return false;
    }
    return true;
}

const Board::BoardType& Board::getBoard() const {
    return board;
}

const Piece* Board::getItem(int x, int y) const {
    return board[x][y];
}

void Board::clear() {
    for (int i = 0; i < BOARD_MAX_WIDTH; ++i) {
        for (int j = 0; j < BOARD_MAX_HEIGHT; ++j) {
            delete board[i][j];
            board[i][j] = nullptr;
        }
    }
    blackPieces.clear();
    whitePieces.clear();    
}

std::vector<Piece* > Board::getPieces(Colour side) {
    if (side == Colour::WHITE) {
        return whitePieces;
    }
    else {
        return blackPieces; 
    }
}
std::vector<Move> Board::getLegalMoves(const Piece & p) {
    std::vector<Move> moves = p.getPossibleMoves(board);
    std::vector<Move> legalMoves;

    for (auto m : p.getPossibleCaptures(board)) {
        moves.emplace_back(m);
    }

    for (auto m : moves) {
        if (isValidMove(m)) legalMoves.emplace_back(m);
    }

    return legalMoves;
}

Piece* Board::getRandomPiece(Colour side) {
    // generate seed for random number generator 
    std::srand(static_cast<unsigned int>(std::time(0)));
    Piece* randPiece = nullptr;
    // Random number generator
    std::default_random_engine generator1(std::random_device{}());
    std::uniform_int_distribution<std::size_t> distribution1(0, whitePieces.size() - 1);
    // Random number generator
    std::default_random_engine generator2(std::random_device{}());
    std::uniform_int_distribution<std::size_t> distribution2(0, blackPieces.size() - 1);
    int randIndex;

    switch(side) { 
        case Colour::WHITE:
            // select a random piece
            randIndex = distribution1(generator1);
            randPiece = whitePieces[randIndex];
            break;
        case Colour::BLACK:
            // select a random piece
            randIndex = distribution2(generator2);
            randPiece = blackPieces[randIndex];
            break;
        default:
            // should never get here not possible piece always has colour 
            // could potenially break program otherwise
            std::cerr << "Invalid Colour" << std::endl;
    }

    return randPiece;
}

Move Board::getRandomMove(const Piece & p) {
    std::vector<Move> legalMoves = getLegalMoves(p);

    // generate seed for random number generator 
    std::srand(static_cast<unsigned int>(std::time(0)));
    // Random number generator
    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<std::size_t> distribution(0, legalMoves.size() - 1);
    int randIndex = distribution(generator);
    return legalMoves[randIndex];
}