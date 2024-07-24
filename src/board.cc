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
    Piece* toRemove = board[p.getX()][p.getY()];
    if(toRemove) delete toRemove;
    board[p.getX()][p.getY()] = nullptr; 
}

void Board::playMove(const Move & m) {
    if (!isValidMove(m)) {
        std::cerr << "invalid move" << std::endl;
        return;
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
        if (board[newX][newY] != nullptr) delete board[newX][newY]; // delete captured piece               
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
        if (!board[newX][newY]) delete board[newX][newY]; // delete captured piece               
    }
    board[newX][newY] = board[x][y]; // move target piece
    board[x][y] = nullptr;
    board[newX][newY]->setPos(Position{newX, newY});
}

void Board::playMove(Position oldPos, Position newPos) {
    Piece *capture = board[newPos.getX()][newPos.getY()];
    Piece *target = board[oldPos.getX()][oldPos.getY()];
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
    // for (auto p : possibleMoves) {
    //     std::cout << p.getNewPosition().getX() << ',' << p.getNewPosition().getY() << std::endl;
    // }

    bool found = false;
    for (auto p : possibleMoves) { // simple move
        if (p.getNewPosition() == m.getNewPosition()) {
            found = true;
            break;
        }
    }
    
    if (!found) {
        std::vector<Move> possibleCaptures = target->getPossibleCaptures(board);
        // for (auto p : possibleMoves) {
        //     std::cout << p.getNewPosition().getX() << ',' << p.getNewPosition().getY() << std::endl;
        // }
        if (possibleCaptures.empty()) return false;
        for (auto p : possibleCaptures) { // capture move
            if (p.getNewPosition() == m.getNewPosition()) {
                //  std::cout << "CAPTURE" << std::endl;
                found = true;
                break;
            }
    }
    }
    if (!found) return false;
    // simulate move
    // std::unique_ptr<Board> temp_board{new Board};
    // temp_board->cloneBoard(*this);
    // temp_board->forcePlayMove(m);
    // // check simulated move is valid
    // return temp_board->isCheck(target->getSide());
    return true;
}

bool Board::isCheck(Colour side) const {
    switch(side) {
        case Colour::BLACK:
            for (auto p : whitePieces) { // check opposing pieces
                for (auto cap : p->getPossibleCaptures(board)) {
                    if (cap.getCapture()->getType() == Type::KING) return false;
                }
            }
            break;
        case Colour::WHITE:
            for (auto p : blackPieces) {
                for (auto cap : p->getPossibleCaptures(board)) {
                    if (cap.getCapture()->getType() == Type::KING) return false;
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


