#include <stdio.h>
#include <memory>
#include <cstring>
#include <random>
#include <ctime>
#include <algorithm>
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
        case Colour::WHITE: {
            auto it = std::find(whitePieces.begin(), whitePieces.end(), p);
            if (it != whitePieces.end()) {
                whitePieces.erase(it);
            }
            break;
        }
        case Colour::BLACK: {
            auto it = std::find(blackPieces.begin(), blackPieces.end(), p);
            if (it != blackPieces.end()) {
                blackPieces.erase(it);
            }
            break;
        }
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
        int captureX = m.getCapture()->getPos().getX();
        int captureY = m.getCapture()->getPos().getY();
        if (board[captureX][captureY] != nullptr) {
            capture(board[captureX][captureY]); // delete captured piece
            board[captureX][captureY] = nullptr;
        }
    }

    board[newX][newY] = board[x][y]; // move target piece
    board[x][y] = nullptr;

    board[newX][newY]->setPos(Position{newX, newY});
}

bool Board::checkPawnPromotion(int newX, int newY) {
    if (board[newX][newY]->getType() == Type::PAWN &&
        ((board[newX][newY]->getSide() == Colour::WHITE &&
        newY == BOARD_MAX_HEIGHT - 1) ||
        (board[newX][newY]->getSide() == Colour::BLACK &&
        newY == BOARD_MIN_HEIGHT))) {
            return true;
        }
    return false;
}

void Board::promptPawnPromotion(int newX, int newY) {
    std::cout << "~ It is Pawn Promotion time ~" << std::endl;
    Piece *newPiece = nullptr;
    char type;

    while (newPiece == nullptr) {
        std::cout << "Enter piece type (Q, R, B, N): ";
        std::cin >> type;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid Input. Try again." << std::endl;
        }
        switch (type) {
            case 'Q': newPiece = new Queen; break;
            case 'R': newPiece = new Rook; break;
            case 'B': newPiece = new Bishop; break;
            case 'N': newPiece = new Knight; break;
            default:
            std::cout << "Invalid type. Try again." << std::endl;
                continue;
        }
    }
    std::cout << "Promoted!" << std::endl;
    newPiece->setSide(board[newX][newY]->getSide());
    newPiece->setPos(Position{newX, newY});
    capture(board[newX][newY]);
    board[newX][newY] = newPiece;
    switch (newPiece->getSide()) {
        case Colour::BLACK: blackPieces.push_back(newPiece); break;
        case Colour::WHITE: whitePieces.push_back(newPiece); break;
        default:
            throw std::invalid_argument("Invalid side when placing piece");
    }
}

void Board::promote(int newX, int newY, Type t) {
    Piece * newPiece = nullptr;
    switch (t) {
        case Type::QUEEN: newPiece = new Queen; break;
        case Type::ROOK: newPiece = new Rook; break;
        case Type::BISHOP: newPiece = new Bishop; break;
        case Type::KNIGHT: newPiece = new Knight; break;
        default:
            throw std::invalid_argument("invalid promote");
    }
    newPiece->setSide(board[newX][newY]->getSide());
    newPiece->setPos(Position{newX, newY});
    capture(board[newX][newY]);
    board[newX][newY] = newPiece;
    switch (newPiece->getSide()) {
        case Colour::BLACK: blackPieces.push_back(newPiece); break;
        case Colour::WHITE: whitePieces.push_back(newPiece); break;
        default:
            throw std::invalid_argument("Invalid side when placing piece");
    }
}

void Board::forcePlayMove(const Move & m) {
    int x = m.getOldPosition().getX();
    int y = m.getOldPosition().getY();
    int newX = m.getNewPosition().getX();
    int newY = m.getNewPosition().getY(); 

    if (board[x][y] == nullptr) {
        throw std::logic_error("NO PIECE TO MOVE");
    }

    if (m.getCapture()) { // has a target
        int captureX = m.getCapture()->getPos().getX();
        int captureY = m.getCapture()->getPos().getY();
        if (board[captureX][captureY] != nullptr) {
            capture(board[captureX][captureY]); // delete captured piece
            board[captureX][captureY] = nullptr;
        }
    }

    board[newX][newY] = board[x][y]; // move target piece
    board[x][y] = nullptr;
    board[newX][newY]->setPos(Position{newX, newY});
}

void Board::playMove(Position oldPos, Position newPos, Colour turn) {
    Piece *target = board[oldPos.getX()][oldPos.getY()];
    // std::cout << "PLAYING MOVE: " << oldPos.getX() << "," << oldPos.getY() << " " << newPos.getX() << "," << newPos.getY()  << std::endl;
    if (target == nullptr) {
        throw std::logic_error("No piece to move");
    }
    if (target->getSide() != turn) {
        throw std::logic_error("Not your turn");
    }

    Piece *capture = board[newPos.getX()][oldPos.getY()]; // En Passant Case
    if (capture && capture->getSide() != turn && capture->getType() == Type::PAWN
        && target->getType() == Type::PAWN) {
        playMove(Move(oldPos, newPos, target, capture)); 
    } else { // Normal case
        playMove(Move(oldPos, newPos, target, board[newPos.getX()][newPos.getY()])); 
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

bool Board::isCheck(Colour side) {
    std::vector<Piece *> pieces;

    if (side == Colour::WHITE) {
        pieces = getPieces(Colour::BLACK);
    }
    else{
        pieces = getPieces(Colour::WHITE);
    }

    for (auto p : pieces) { // check opposing pieces
        std::vector<Move> captures = p->getPossibleCaptures(board);
        if (captures.empty()) continue;
        for (auto cap : captures) {
            if (cap.getCapture()->getType() == Type::KING) return true;
        }
    }

    return false;

}

bool Board::isCheckmate(Colour side) {
    std::vector<Piece *> pieces = getPieces(side);

    for (auto p : pieces) {
        std::vector<Move> moves = p->getPossibleMoves(board);
        if (moves.empty()) continue;
        for (auto m : moves) {
            if (isValidMove(m)) return false;
        }
    }

    return true;
}

bool Board::isStalemate(Colour side)  {
    std::vector<Piece *> pieces = getPieces(side);
            
    if (isCheck(side)) return false;
    
    for (auto p : pieces) {
        std::vector<Move> moves = p->getPossibleMoves(board);
        if (moves.empty()) continue;
        for (auto m : moves) {
            if (isValidMove(m)) return false;
        }
    }

    return true;
}

bool Board::isInsufficientMaterial() const {
    return whitePieces.size() == 1 && blackPieces.size() == 1
        && whitePieces[0]->getType() == Type::KING
        && blackPieces[0]->getType() == Type::KING;
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

std::vector<Piece* > Board::getPieces(const Colour & side) {
    if (side == Colour::WHITE) {
        return whitePieces;
    }
    else {
        return blackPieces; 
    }
}

std::vector<Move> Board::getCheckMoves(Colour side) {
    std::vector<Piece *> pieces = getPieces(side);
    std::vector<Move> captures = getCaptureMoves(side);
    std::vector<Move> checkMoves;
    
    
    if (captures.empty()) return captures;
    for (auto cap : captures) {
        if (cap.getCapture()->getType() == Type::KING) {
            checkMoves.push_back(cap);
        }
    }
    
    return checkMoves;
}

std::vector<Move> Board::getAvoidCaptureMoves(Colour side) {
    std::vector<Piece *> opponentPieces = getPieces(side == Colour::WHITE ? Colour::BLACK : Colour::WHITE);
    std::vector<Piece *> friendlyPieces;
    std::vector<Move> avoidCaptureMoves;
    std::vector<Move> threatenedPieceMoves;
    std::vector<Move> potentialMoves;

    // Get all potential capture moves by the opponent
    for (auto p : opponentPieces) {
        std::vector<Move> captures = p->getPossibleCaptures(board);
        threatenedPieceMoves.insert(threatenedPieceMoves.end(), captures.begin(), captures.end());
    }

    if (threatenedPieceMoves.empty()) return {};

    // Collect all friendly pieces that are under threat
    for (auto m : threatenedPieceMoves) {
        Position pos = m.getTarget()->getPos();
        Piece * threatenedPiece = board[pos.getX()][pos.getY()];
        if (threatenedPiece && threatenedPiece->getSide() == side) {
            friendlyPieces.push_back(threatenedPiece);
        }
    }

    // Collect all possible moves for those friendly pieces to give bot 3 edge
    for (auto p : friendlyPieces) {
        std::vector<Move> captures = p->getPossibleCaptures(board);
        std::vector<Move> moves = p->getPossibleMoves(board);
        potentialMoves.insert(potentialMoves.end(), captures.begin(), captures.end());
        potentialMoves.insert(potentialMoves.end(), moves.begin(), moves.end());
    }

    for (auto m : potentialMoves) {
        if (isValidMove(m)) avoidCaptureMoves.push_back(m);
    }

    return avoidCaptureMoves;
}

std::vector<Move> Board::getCaptureMoves(Colour side) {
    std::vector<Piece *> pieces = getPieces(side);
    std::vector<Move> captureMoves;
    std::vector<Move> moves;

    for (auto p : pieces) {
        for (auto m : p->getPossibleCaptures(board)) {
            moves.push_back(m);
        }
    }

    for (auto m : moves) {
        if (isValidMove(m)) captureMoves.push_back(m);
    }

    return captureMoves;
}

std::vector<Move> Board::getLegalMoves(Colour side) {
    std::vector<Piece *> pieces = getPieces(side);
    std::vector<Move> legalMoves;
    std::vector<Move> moves;

    for (auto p : pieces) {
        for (auto m : p->getPossibleMoves(board)) {
            moves.push_back(m);
        }
        for (auto m : p->getPossibleCaptures(board)) {
            moves.push_back(m);
        }
    }

    for (auto m : moves) {
        if (isValidMove(m)) legalMoves.push_back(m);
    }

    return legalMoves;
}


Move Board::getRandomMove(const std::vector<Move> legalMoves) {
    // generate seed for random number generator 
    std::srand(static_cast<unsigned int>(std::time(0)));
    // Random number generator
    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<std::size_t> distribution(0, legalMoves.size() - 1);
    int randIndex = distribution(generator);
    return legalMoves[randIndex];
}