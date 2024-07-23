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

// checks each direction the king can move in and sees if it captures anything and returns a vector containing the catures
std::vector<Move> Knight::getPossibleCaptures(const Board::BoardType & board) const {
    std::vector<Move> output;
    int curX = currPosition.getX();
    int curY = currPosition.getY();

    if (curX + 2 < BOARD_MAX_WIDTH && curY + 1 < BOARD_MAX_HEIGHT) {
        if (board[curX + 2][curY + 1] != nullptr ) {
            if (board[curX + 2][curY + 1]->getSide() != this->getSide()) {    
                output.emplace_back(currPosition, Position(curX + 2, curY + 1), this, board[curX + 2][curY + 1]);
            }
        }
    }
    if (curX + 2 < BOARD_MAX_WIDTH && curY - 1 >= BOARD_MIN_HEIGHT) {
        if (board[curX + 2][curY - 1] != nullptr) {
            if (board[curX + 2][curY - 1]->getSide() != this->getSide()) {    
                output.emplace_back(currPosition, Position(curX + 2, curY - 1), this, board[curX + 2][curY - 1]);
            }
        }
    }

    if (curX - 2 >= BOARD_MIN_WIDTH && curY + 1 < BOARD_MAX_HEIGHT) {
        if (board[curX - 2][curY + 1] != nullptr) {
            if (board[curX - 2][curY + 1]->getSide() != this->getSide()) {    
                output.emplace_back(currPosition, Position(curX - 2, curY + 1), this, board[curX - 2][curY + 1]);
            }
        }
    }
    if (curX - 2 >= BOARD_MIN_WIDTH && curY - 1 >= BOARD_MIN_HEIGHT) {
        if (board[curX - 2][curY - 1] != nullptr) {
            if (board[curX - 2][curY - 1]->getSide() != this->getSide()) {    
                output.emplace_back(currPosition, Position(curX - 2, curY - 1), this, board[curX - 2][curY - 1]);
            }
        }
    }

    if (curX + 1 < BOARD_MAX_WIDTH && curY + 2 < BOARD_MAX_HEIGHT) {
        if (board[curX + 1][curY + 2] != nullptr) {
            if (board[curX + 1][curY + 2]->getSide() != this->getSide()) {    
                output.emplace_back(currPosition, Position(curX + 1, curY + 2), this, board[curX + 1][curY + 2]);
            }
        }
    }
    if (curX + 1 < BOARD_MAX_WIDTH && curY - 2 >= BOARD_MIN_HEIGHT) {
        if (board[curX + 1][curY - 2] != nullptr) {
            if (board[curX + 1][curY - 2]->getSide() != this->getSide()) {    
                output.emplace_back(currPosition, Position(curX + 1, curY - 2), this, board[curX + 1][curY - 2]);
            }
        }
    }

    if (curX - 1 >= BOARD_MIN_WIDTH && curY + 2 < BOARD_MAX_HEIGHT) {
        if (board[curX - 1][curY + 2] != nullptr) {
            if (board[curX - 1][curY + 2]->getSide() != this->getSide()) {    
                output.emplace_back(currPosition, Position(curX - 1, curY + 2), this, board[curX - 1][curY + 2]);
            }
        }
    }
    if (curX - 1 >= BOARD_MIN_WIDTH && curY - 2 >= BOARD_MAX_HEIGHT) {
        if (board[curX - 1][curY - 2] != nullptr) {
            if (board[curX - 1][curY - 2]->getSide() != this->getSide()) {    
                output.emplace_back(currPosition, Position(curX - 1, curY - 2), this, board[curX - 1][curY - 2]);
            }
        }
    }

    return output;
}