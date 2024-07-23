#include "knight.h"
Knight::Knight() : Piece{Type::KNIGHT} {}

// check each direction the knight can move not including captures and return a vector containing the moves 
std::vector<Move> Knight::getPossibleMoves(const Board::BoardType & board) const {
    std::vector<Move> output;
    int curX = currPosition.getX();
    int curY = currPosition.getY();

    if (curX + 2 < BOARD_MAX_WIDTH && curY + 1 < BOARD_MAX_HEIGHT) {
        if (board[curX + 2][curY + 1] == nullptr) {
            output.emplace_back(currPosition, Position(curX + 2, curY + 1), this, nullptr);
        }
    }
    if (curX + 2 < BOARD_MAX_WIDTH && curY - 1 >= BOARD_MIN_HEIGHT) {
        if (board[curX + 2][curY - 1] == nullptr) {
            output.emplace_back(currPosition, Position(curX + 2, curY - 1), this, nullptr);
        }
    }

    if (curX - 2 >= BOARD_MIN_WIDTH && curY + 1 < BOARD_MAX_HEIGHT) {
        if (board[curX - 2][curY + 1] == nullptr) {
            output.emplace_back(currPosition, Position(curX - 2, curY + 1), this, nullptr);
        }
    }
    if (curX - 2 >= BOARD_MIN_WIDTH && curY - 1 >= BOARD_MIN_HEIGHT) {
        if (board[curX - 2][curY - 1] == nullptr) {
            output.emplace_back(currPosition, Position(curX - 2, curY - 1), this, nullptr);
        }
    }

    if (curX + 1 < BOARD_MAX_WIDTH && curY + 2 < BOARD_MAX_HEIGHT) {
        if (board[curX + 1][curY + 2] == nullptr) {
            output.emplace_back(currPosition, Position(curX + 1, curY + 2), this, nullptr);
        }
    }
    if (curX + 1 < BOARD_MAX_WIDTH && curY - 2 >= BOARD_MIN_HEIGHT) {
        if (board[curX + 1][curY - 2] == nullptr) {
            output.emplace_back(currPosition, Position(curX + 1, curY - 2), this, nullptr);
        }
    }

    if (curX - 1 >= BOARD_MIN_WIDTH && curY + 2 < BOARD_MAX_HEIGHT) {
        if (board[curX - 1][curY + 2] == nullptr) {
            output.emplace_back(currPosition, Position(curX - 1, curY + 2), this, nullptr);
        }
    }
    if (curX - 1 >= BOARD_MIN_WIDTH && curY - 2 >= BOARD_MAX_HEIGHT) {
        if (board[curX - 1][curY - 2] == nullptr) {
            output.emplace_back(currPosition, Position(curX - 1, curY - 2), this, nullptr);
        }
    }

    return output;
}

std::vector<Move> Knight::getPossibleMoves(const Board::BoardType & board) const {
    std::vector<Move> output;
    int curX = currPosition.getX();
    int curY = currPosition.getY();

    if (curX + 2 < BOARD_MAX_WIDTH && curY + 1 < BOARD_MAX_HEIGHT) {
        if (board[curX + 2][curY + 1] != nullptr ) {
            if (board[curX + 2][curY + 1]->getSide() != this->getSide()) {    
                output.emplace_back(currPosition, Position(curX + 2, curY + 1), this, nullptr);
            }
        }
    }
    if (curX + 2 < BOARD_MAX_WIDTH && curY - 1 >= BOARD_MIN_HEIGHT) {
        if (board[curX + 2][curY - 1] != nullptr) {
            if (board[curX + 2][curY - 1]->getSide() != this->getSide()) {    
                output.emplace_back(currPosition, Position(curX + 2, curY - 1), this, nullptr);
            }
        }
    }

    if (curX - 2 >= BOARD_MIN_WIDTH && curY + 1 < BOARD_MAX_HEIGHT) {
        if (board[curX - 2][curY + 1] != nullptr) {
            if (board[curX - 2][curY + 1]->getSide() != this->getSide()) {    
                output.emplace_back(currPosition, Position(curX - 2, curY + 1), this, nullptr);
            }
        }
    }
    if (curX - 2 >= BOARD_MIN_WIDTH && curY - 1 >= BOARD_MIN_HEIGHT) {
        if (board[curX - 2][curY - 1] != nullptr) {
            if (board[curX - 2][curY - 1]->getSide() != this->getSide()) {    
                output.emplace_back(currPosition, Position(curX - 2, curY - 1), this, nullptr);
            }
        }
    }

    if (curX + 1 < BOARD_MAX_WIDTH && curY + 2 < BOARD_MAX_HEIGHT) {
        if (board[curX + 1][curY + 2] != nullptr) {
            if (board[curX + 1][curY + 2]->getSide() != this->getSide()) {    
                output.emplace_back(currPosition, Position(curX + 1, curY + 2), this, nullptr);
            }
        }
    }
    if (curX + 1 < BOARD_MAX_WIDTH && curY - 2 >= BOARD_MIN_HEIGHT) {
        if (board[curX + 1][curY - 2] != nullptr) {
            if (board[curX + 1][curY - 2]->getSide() != this->getSide()) {    
                output.emplace_back(currPosition, Position(curX + 1, curY - 2), this, nullptr);
            }
        }
    }

    if (curX - 1 >= BOARD_MIN_WIDTH && curY + 2 < BOARD_MAX_HEIGHT) {
        if (board[curX - 1][curY + 2] != nullptr) {
            if (board[curX - 1][curY + 2]->getSide() != this->getSide()) {    
                output.emplace_back(currPosition, Position(curX - 1, curY + 2), this, nullptr);
            }
        }
    }
    if (curX - 1 >= BOARD_MIN_WIDTH && curY - 2 >= BOARD_MAX_HEIGHT) {
        if (board[curX - 1][curY - 2] != nullptr) {
            if (board[curX - 1][curY - 2]->getSide() != this->getSide()) {    
                output.emplace_back(currPosition, Position(curX - 1, curY - 2), this, nullptr);
            }
        }
    }

    return output;
}