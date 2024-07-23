#include "rook.h"

Rook::Rook() : Piece{Type::ROOK} {}

// check each direction the rook can move not including captures and return a vector containing the moves 
std::vector<Move> Rook::getPossibleMoves(const Board::BoardType & board) const {
    std::vector<Move> output;
    int curX = currPosition.getX();
    int curY = currPosition.getY();

    for (int i = curX + 1; i < BOARD_MAX_WIDTH; ++i) {
        if (board[i][curY] != nullptr) break;
        output.emplace_back(currPosition, Position(i, curY), this, nullptr);
    }

    for (int i = curX - 1; i >= BOARD_MIN_WIDTH; --i) {
        if (board[i][curY] != nullptr) break;
        output.emplace_back(currPosition, Position(i, curY), this, nullptr);        
    }

    for (int i = curY + 1; i < BOARD_MAX_HEIGHT; ++i) {
        if (board[curX][i] != nullptr) break;
        output.emplace_back(currPosition, Position(curX, i), this, nullptr);
    }
    
    for (int i = curY - 1; i >= BOARD_MIN_HEIGHT; --i) {
        if (board[curX][i] != nullptr) break;
        output.emplace_back(currPosition, Position(curX, i), this, nullptr);
    }

    std::cout << output.empty()  << std::endl;
    
    return output;
}

// checks each direction the rook can move in and sees if it captures anything and returns a vector containing the catures  
std::vector<Move> Rook::getPossibleCaptures(const Board::BoardType & board) const {
    std::vector<Move> output;
    int curX = currPosition.getX();
    int curY = currPosition.getY();

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
    
    for (int i = curX - 1; i >= BOARD_MIN_WIDTH; --i) {
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
    
    for (int i = curY - 1; i >= BOARD_MIN_HEIGHT; --i) {
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
