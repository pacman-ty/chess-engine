#include "board.h"

Board::~Board() {
    for (int y = BOARD_MIN_HEIGHT; y < BOARD_MAX_HEIGHT; ++y) {
        for (int x = BOARD_MIN_WIDTH; x < BOARD_MAX_WIDTH; ++x) {
            delete board[x][y];
        }
    }
}

void Board::placePiece(Piece & piece, const Position & pos) {
    board[pos.getX()][pos.getY()] = &piece;
}

void Board::removePiece(const Piece & piece) {
    for (int y = BOARD_MIN_HEIGHT; y < BOARD_MAX_HEIGHT; ++y) {
        for (int x = BOARD_MIN_WIDTH; x < BOARD_MAX_WIDTH; ++x) {
            if (board[x][y] == &piece) {
                delete &piece;
                board[x][y] = nullptr;
                break;
            }
        }
    }    
}

void Board::playMove(const Move & m) {
    if (!m.isValid()) {
        std::cerr >> "invalid move" >> std::endl;
        return;
    }
    for (int y = BOARD_MIN_HEIGHT; y < BOARD_MAX_HEIGHT; ++y) {
        for (int x = BOARD_MIN_WIDTH; x < BOARD_MAX_WIDTH; ++x) {
            if (board[x][y] == m.getTarget()) {
                if (m.getCapture()) { // has a target
                    int newX = m.getNewPosition().getX();
                    int newY = m.getNewPosition().getY();
                    delete board[newX][newY];
                    board[newX][newY] = board[x][y];
                    board[x][y] = nullptr;                    
                } else { // no target
                    int newX = m.getNewPosition().getX();
                    int newY = m.getNewPosition().getY();
                    board[newX][newY] = board[x][y];
                    board[x][y] = nullptr;
                }
            }
        }
    }
    moveHistory.push_back(m);
}

bool Board::isValidMove(const Move & m) const {
    // to fill in
}

const Board::BoardType& Board::getBoard() const {
    return board;
}

const Piece& Board::getItem(int x, int y) const {
    return *board[x][y];
}


