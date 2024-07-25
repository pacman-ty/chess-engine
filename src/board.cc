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
    for (auto p : whitePieces) {
        delete p;
    }
    for (auto p : blackPieces) {
        delete p;
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
    toAdd->setPos(pos);
    switch (side) {
        case Colour::BLACK: blackPieces.push_back(toAdd); break;
        case Colour::WHITE: whitePieces.push_back(toAdd); break;
        default:
            std::cerr << "Invalid Side" << std::endl;
            delete toAdd;
            return;
    }
    std::cout << "Piece created" << std::endl;
    // Add to the board
    board[pos.getX()][pos.getY()] = toAdd;
}

void Board::removePiece(Position p) {
    delete board[p.getX()][p.getY()];
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
    if (m.getCapture()) { // has a target
        delete board[newX][newY]; // delete captured piece
        board[newX][newY] = board[x][y]; // move target piece
        board[x][y] = nullptr;                    
    } else { // no target
        board[newX][newY] = board[x][y]; // move target piece
        board[x][y] = nullptr;
    }
}
/*
void Board::playMove(Position oldPos, Position newPos) {
    delete board[newPos.getX()][newPos.getY()];
    board[newPos.getX()][newPos.getY()] = board[oldPos.getX()][oldPos.getY()];
}
*/
void Board::cloneBoard(const Board & b) {
    for (int y = BOARD_MIN_HEIGHT; y < BOARD_MAX_HEIGHT; ++y) {
        for (int x = BOARD_MIN_WIDTH; x < BOARD_MAX_WIDTH; ++x) {
            const Piece* curItem = b.getItem(x, y);
            placePiece(curItem->getSide(), curItem->getType(), curItem->getPos());     
        }
    }
}

bool Board::isValidMove(const Move & m) const {
    // check if you can go there
    bool found = false;
    for (auto p : m.getTarget()->getPossibleMoves(board)) { // simple move
        if (p.getNewPosition() == m.getNewPosition()) {
            found = true;
            break;
        }
    }
    if (!found) {
        for (auto p : m.getTarget()->getPossibleCaptures(board)) { // capture move
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
    temp_board->playMove(m);
    // check simulated move is valid
    return temp_board->isCheck(m.getTarget()->getSide());
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