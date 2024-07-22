#include "rook.h"

Rook::Rook() : Piece{Type::ROOK} {}

// check each direction the rook can move not including captures and return a vector containing the moves 
std::vector<Move> Rook::getPossibleMoves(Board::BoardType & curBoard) const {
    std::vector<Move> output;
    int curX = currPosition.getX();
    int curY = currPosition.getY();

    for (int i = curX; i < BOARD_MAX_WIDTH; ++i) {
        if (curBoard[i][curY] != nullptr) break;
        output.emplace_back(currPosition, Position(i, curY), this, nullptr);
    }
    for (int i = curX; i >= BOARD_MIN_WIDTH; --i) {
        if (curBoard[i][curY] != nullptr) break;
        output.emplace_back(currPosition, Position(i, curY), this, nullptr);        
    }
    for (int i = curY; i < BOARD_MAX_HEIGHT; ++i) {
        if (curBoard[curX][i] != nullptr) break;
        output.emplace_back(currPosition, Position(curX, i), this, nullptr);
    }
    for (int i = curY; i >= BOARD_MIN_HEIGHT; --i) {
        if (curBoard[curX][i] != nullptr) break;
        output.emplace_back(currPosition, Position(curX, i), this, nullptr);
    }
    return output;

}

// checks each direction the rook can move in and sees if it captures anything and returns a vector containing the catures  
std::vector<Move> Rook::getPossibleCaptures(Board::BoardType & curBoard) const {
    std::vector<Move> output;
    int curX = currPosition.getX();
    int curY = currPosition.getY();

    for (int i = curX; i < BOARD_MAX_WIDTH; ++i) {
        if (curBoard[i][curY] != nullptr) {
            if (curBoard[i][curY].getSide() != this.getSide()) { 
                output.emplace_back(currPosition, Position(i, curY), this, curBoard[i][curY]);
                break;
            }
            else {
                break;
            }
        }
    }
    for (int i = curX; i >= BOARD_MIN_WIDTH; --i) {
        if (curBoard[i][curY] != nullptr) {
            if (curBoard[i][curY].getSide() != this.getSide()) {
                output.emplace_back(currPosition, Position(i, curY), this, curBoard[i][curY]);
                break;
            }
            else {
                break;
            }
        }
    }
    for (int i = curY; i < BOARD_MAX_HEIGHT; ++i) {
        if (curBoard[CurX][i] != nullptr) {
            if (curBoard[curX][i].getSide() != this.getSide()) {
                output.emplace_back(currPosition, Position(curX, i), this, curBoard[curX][i]);
                break;
            }
            else {
                break;
            }
        }
    }
    for (int i = curY; i >= BOARD_MIN_HEIGHT; --i) {
        if (curBoard[curX][i] != nullptr) {
            if (curBoard[curX][i].getSide() != this.getSide()) {
                output.emplace_back(currPosition, Position(curX, i), this, curBoard[curX][i]);
                break;
            }
            else {
                break;
            }
        }
    }
    return output;
}
