#include "queen.h"

// checks each direction the queen can move not including captures and return a vector contain the moves
std::vector<Move> getPossibleMoves(Board::BoardType & board) {
    std::vector<Move> output;
    int curX = currPosition.getX();
    int curY = currPosition.getY();

    for (int i = curX + 1; i < BOARD_MAX_WIDTH; ++i) {
        for (int j = curY + 1; j < BOARD_MAX_HEIGHT; ++j) {
            if (board[i][j] != nullptr) break;
            output.emplace_back(currPosition, Position(i, j), this, nullptr);
       }
    }

    for (int i = curX + 1; i < BOARD_MAX_WIDTH; ++i) {
        for (int j = curY + 1; j >= BOARD_MAX_HEIGHT; --j) {
            if (board[i][j] != nullptr) break;
            output.emplace_back(currPosition, Position(i, j), this, nullptr);
       }
    }

    for (int i = curX + 1; i >= BOARD_MIN_WIDTH; --i) {
        for (int j = curY + 1; j < BOARD_MAX_HEIGHT; ++j) {
            if (board[i][j] != nullptr) break;
            output.emplace_back(currPosition, Position(i, j), this, nullptr);
       }
    }

    for (int i = curX + 1; i >= BOARD_MIN_WIDTH; --i) {
        for (int j = curY + 1; j >= BOARD_MIN_HEIGHT; --j) {
            if (board[i][j] != nullptr) break;
            output.emplace_back(currPosition, Position(i, j), this, nullptr);
       }
    }

    for (int i = curX + 1; i < BOARD_MAX_WIDTH; ++i) {
        if (board[i][curY] != nullptr) break;
        output.emplace_back(currPosition, Position(i, curY), this, nullptr);
    }

    for (int i = curX + 1; i >= BOARD_MIN_WIDTH; --i) {
        if (board[i][curY] != nullptr) break;
        output.emplace_back(currPosition, Position(i, curY), this, nullptr);
    }

    for (int i = curY + 1; i < BOARD_MAX_HEIGHT; ++i) {
        if (board[curX][i] != nullptr) break;
        output.emplace_back(currPosition, Position(curX, i), this, nullptr);
    }
    
    for (int i = curY + 1; i >= BOARD_MIN_HEIGHT; --i) {
        if (board[curX][i] != nullptr) break;
        output.emplace_back(currPosition, Position(curX, i), this, nullptr);
    }

    return output;
}

// checks each direction the queen can move in and sees if it captures anything and returns a vector containing the catures
std::vector<Move> getPossibleCaptures(Board::Type & Board) {
    std::vector<Move> output;
    int curX = currPosition.getX();
    int curY = currPosition.getY();

    for (int i = curX + 1; i < BOARD_MAX_WIDTH; ++i) {
        for (int j = curY + 1; j < BOARD_MAX_HEIGHT; ++j) {
            if (board[i][j] != nullptr) {
                if (board->getSide() != this->getSide()) {
                    output.emplace_back(currPosition, Position(i, j), this, board[i][j]);
                    break;
                }
                else {
                    break;
                }
            }
        }
    }

    for (int i = curX + 1; i < BOARD_MAX_WIDTH; ++i) {
        for (int j = curY + 1; j >= BOARD_MAX_HEIGHT; --j) {
            if (board[i][j] != nullptr) {
                if (board->getSide() != this->getSide()) {
                    output.emplace_back(currPosition, Position(i, j), this, board[i][j]);
                    break;
                }
                else {
                    break;
                }
            }
        }
    }

    for (int i = curX + 1; i >= BOARD_MIN_WIDTH; --i) {
        for (int j = curY+ 1; j < BOARD_MAX_HEIGHT; ++j) {
            if (board[i][j] != nullptr) {
                if (board->getSide() != this->getSide()) {
                    output.emplace_back(currPosition, Position(i, j), this, board[i][j]);
                    break;
                }
                else {
                    break;
                }
            }
        }
    }

    for (int i = curX + 1; i >= BOARD_MIN_WIDTH; --i) {
        for (int j = curY + 1; j >= BOARD_MIN_HEIGHT; --j) {
            if (board[i][j] != nullptr) {
                if (board->getSide() != this->getSide()) {
                    output.emplace_back(currPosition, Position(i, j), this, board[i][j]);
                    break;
                }
                else {
                    break;
                }
            }
        }
    }

    for (int i = curX + 1; i < BOARD_MAX_WIDTH; ++i) {
        if (board[i][curY] != nullptr) {
            if (board[i][curY]->getSide() != this->getSide()) {
                output.emplace_back(currPosition, Position(i, curY), this, board[i][curY]);
                break;
            }
            else {
                break;
            }
        }
    }

    for (int i = curX + 1; i >= BOARD_MIN_WIDTH; --i) {
        if (board[i][curY] != nullptr) {
            if (board[i][curY]->getSide() != this->getSide()) {
                output.emplace_back(currPosition, Position(i, curY), this, board[i][curY]);
                break;
            }
            else {
                break;
            }
        }
    }

    for (int i = curY + 1; i < BOARD_MAX_HEIGHT; ++i) {
        if (board[curX][i] != nullptr) {
            if (board[curX][i]->getSide() != this->getSide()) {
                output.emplace_back(currPosition, Position(curX, i), this, board[curX][i]);
                break;
            }
            else {
                break;
            }
        }
    }

    for (int i = curY + 1; i >= BOARD_MIN_HEIGHT; --i) {
        if (board[curX][i] != nullptr) {
            if (board[curX][i]->getSide() != this->getSide()) {
                output.emplace_back(currPosition, Position(curX, i), this, board[curX][i]);
                break;
            }
            else {
                break;
            }
        }
    }

    return output;
}
    
