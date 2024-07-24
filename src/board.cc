#include <stdio.h>
#include <memory>
#include <cstring>
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
    for (int i = 0; i < BOARD_MAX_WIDTH; ++i) {
        for (int j = 0; j < BOARD_MAX_HEIGHT; ++j) {
            delete board[i][j];
        }
    }
    blackPieces.clear();
    whitePieces.clear();
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
            std::cerr << "Invalid colour when capturing" << std::endl;
    }
    if (p) delete p;
}

void Board::placePiece(Colour side, Type t, const Position & pos) {
    if (board[pos.getX()][pos.getY()]) {
        std::cerr << "Invalid placement (Slot taken)" << std::endl;
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
            std::cerr << "Invalid type" << std::endl;
            return;
    }
    toAdd->setSide(side);
    toAdd->setPos(Position{pos.getX(), pos.getY()});
    switch (side) {
        case Colour::BLACK: blackPieces.push_back(toAdd); break;
        case Colour::WHITE: whitePieces.push_back(toAdd); break;
        default:
            std::cerr << "Invalid Side" << std::endl;
            return;
    }
    // Add to the board
    board[pos.getX()][pos.getY()] = toAdd;
}

void Board::removePiece(Position p) {
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

void Board::playMove(Position oldPos, Position newPos, Colour turn) {
    Piece *capture = board[newPos.getX()][newPos.getY()];
    Piece *target = board[oldPos.getX()][oldPos.getY()];
    if (target == nullptr) {
        throw std::logic_error("No piece to move");
    }
    if (target->getSide() != turn) {
        throw std::logic_error("Not your turn");
    }
    playMove(Move(oldPos, newPos, target, capture));
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
            std::cerr << "Invalid Colour" << std::endl;
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
                    if (isValidMove(m)) std::cout << '[' << m.getNewPosition().getX() + 1 << ',' << m.getNewPosition().getY() + 1 << ']' << std::endl; return false;
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
            std::cerr << "Invalid Colour" << std::endl;
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


