#include "king.h"

King::King() : Piece{Type::KING} {}

// checks each direction the King can move in and returns a vector of valid moves  
std::vector<Move> King::getPossibleMoves(const Board::BoardType & board) const {
    std::vector<Move> output;
    int curX = currPosition.getX();
    int curY = currPosition.getY();

    if (curX + 1 < BOARD_MAX_WIDTH && curY + 1 < BOARD_MAX_HEIGHT) {
        if (board[curX + 1][curY + 1] == nullptr) {
            output.emplace_back(currPosition, Position(curX + 1, curY + 1), this, nullptr);
        }
    }
    if (curX + 1 < BOARD_MAX_WIDTH && curY - 1 >= BOARD_MIN_HEIGHT) {
        if (board[curX + 1][curY - 1] == nullptr) {
            output.emplace_back(currPosition, Position(curX + 1, curY - 1), this, nullptr);
        }
    }
    if (curX + 1 < BOARD_MAX_WIDTH) {
        if (board[curX + 1][curY] == nullptr) {
            output.emplace_back(currPosition, Position(curX + 1, curY), this, nullptr);
        }
    }
    
    if (curX - 1 < BOARD_MAX_WIDTH && curY + 1 < BOARD_MAX_HEIGHT) {
        if (board[curX - 1][curY + 1] == nullptr) {
            output.emplace_back(currPosition, Position(curX - 1, curY + 1), this, nullptr);
        }
    }
    if (curX - 1 < BOARD_MAX_WIDTH && curY - 1 >= BOARD_MIN_HEIGHT) {
        if (board[curX - 1][curY - 1] == nullptr) {
            output.emplace_back(currPosition, Position(curX - 1, curY - 1), this, nullptr);
        }
    }
    if (curX - 1 < BOARD_MAX_WIDTH) {
        if (board[curX - 1][curY] == nullptr) {
            output.emplace_back(currPosition, Position(curX - 1, curY), this, nullptr);
        }
    }

    if (curY + 1 < BOARD_MAX_HEIGHT) {
        if (board[curX][curY + 1] == nullptr) {
            output.emplace_back(currPosition, Position(curX, curY + 1), this, nullptr);
        }
    }
    if (curY - 1 < BOARD_MIN_HEIGHT) {
        if (board[curX][curY - 1] == nullptr) {
            output.emplace_back(currPosition, Position(curX, curY - 1), this, nullptr);
        }
    }

    return output;
}

// checks each direction the king can move in and sees if it captures anything and returns a vector containing the catures
std::vector<Move> King::getPossibleCaptures(const Board::BoardType & board) const {
    std::vector<Move> output;
    int curX = currPosition.getX();
    int curY = currPosition.getY();

    if (curX + 1 < BOARD_MAX_WIDTH && curY + 1 < BOARD_MAX_HEIGHT) {
        if (board[curX + 1][curY + 1] != nullptr) {
            if (board[curX + 1][curY + 1]->getSide() != this->getSide()) {
                output.emplace_back(currPosition, Position(curX + 1, curY + 1), this, board[curX + 1][curY + 1]);
            }
        }
    }
    if (curX + 1 < BOARD_MAX_WIDTH && curY - 1 >= BOARD_MIN_HEIGHT) {
        if (board[curX + 1][curY - 1] != nullptr) {
            if (board[curX + 1][curY - 1]->getSide() != this->getSide()) {
                output.emplace_back(currPosition, Position(curX + 1, curY - 1), this, board[curX + 1][curY - 1]);
            }
        }
    }
    if (curX + 1 < BOARD_MAX_WIDTH) {
        if (board[curX + 1][curY] != nullptr) {
            if (board[curX + 1][curY]->getSide() != this->getSide()) {
                output.emplace_back(currPosition, Position(curX + 1, curY), this, board[curX + 1][curY]);
            }
        }
    }

    if (curX - 1 >= BOARD_MIN_WIDTH && curY + 1 < BOARD_MAX_HEIGHT) {
        if (board[curX - 1][curY + 1] != nullptr) {
            if (board[curX - 1][curY + 1]->getSide() != this->getSide()) {
                output.emplace_back(currPosition, Position(curX - 1, curY + 1), this, board[curX - 1][curY + 1]);
            }
        }
    }
    if (curX - 1 >= BOARD_MIN_WIDTH && curY - 1 >= BOARD_MIN_HEIGHT) {
        if (board[curX - 1][curY - 1] != nullptr) {
            if (board[curX - 1][curY - 1]->getSide() != this->getSide()) {
                output.emplace_back(currPosition, Position(curX - 1, curY - 1), this, board[curX - 1][curY - 1]);
            }
        }
    }
    if (curX - 1 >= BOARD_MIN_WIDTH) {
        if (board[curX - 1][curY] != nullptr) {
            if (board[curX - 1][curY]->getSide() != this->getSide()) {
                output.emplace_back(currPosition, Position(curX - 1, curY), this, board[curX - 1][curY]);
            }
        }
    }

    if (curY + 1 < BOARD_MAX_WIDTH) {
        if (board[curX][curY + 1] != nullptr) {
            if (board[curX][curY + 1]->getSide() != this->getSide()) {
                output.emplace_back(currPosition, Position(curX, curY + 1), this, board[curX][curY + 1]);
            }
        }
    }
    if (curY - 1 >= BOARD_MIN_WIDTH) {
        if (board[curX][curY - 1] != nullptr) {
            if (board[curX][curY - 1]->getSide() != this->getSide()) {
                output.emplace_back(currPosition, Position(curX, curY - 1), this, board[curX][curY - 1]);
            }
        }
    }
    

    return output;
}