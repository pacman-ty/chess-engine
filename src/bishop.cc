#include "bishop.h"

Bishop::Bishop() : Piece{Type::BISHOP} {}

// checks each direction the bishop can move not including captures and return a vector contain the moves
std::vector<Move> Bishop::getPossibleMoves(const Board::BoardType & board) const {
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

    return output; 
}

std::vector<Move> Bishop::getPossibleCaptures(const Board::Type & board) const {
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
    
    return output;
}
