#include "rook.h"

Rook::Rook(Board *board) : Piece{board} {}

std::vector<Move> Rook::getPossibleMove() const {
    std::vector<Move> output;
    Piece*** curBoard = board->getBoard();
    int curX = currPosition.getX();
    int curY = currPosition.getY();


    for (int i = curX; i < BOARD_WIDTH; ++i) {
        if (curBoard[curY][i] != nullptr) break;
        output.emplace_back(currPosition, Pos(curY, i), this, nullptr);
    }
    for (int i = curX; i >= 0; --i) {
        if (curBoard[curY][i] != nullptr) break;
        output.emplace_back(currPosition, Pos(curY, i), this, nullptr);        
    }
    for (int i = curY; i < BOARD_HEIGHT; ++i) {
        if (curBoard[i][curX] != nullptr) break;
        output.emplace_back(currPosition, Pos(i, curX), this, nullptr);
    }
    for (int i = curY; i >= 0; --i) {
        if (curBoard[i][curX] != nullptr) break;
        output.emplace_back(currPosition, Pos(i, curX), this, nullptr);
    }
    return output;
}

std::vector<Move> Rook::getPossibleMove() const {
    std::vector<Move> output;
    Piece*** curBoard = board->getBoard();
    int curX = currPosition.getX();
    int curY = currPosition.getY();

    for (int i = curX; i < BOARD_WIDTH; ++i) {
        if (curBoard[curY][i] != nullptr) {
            output.emplace_back(currPosition, Pos(curY, i),
                                this, curBoard[curY][i]);
            break;
        }
    }
    for (int i = curX; i >= 0; --i) {
        if (curBoard[curY][i] != nullptr) {
            output.emplace_back(currPosition, Pos(curY, i),
                                this, curBoard[curY][i]);
            break;
        }
    }
    for (int i = curY; i < BOARD_HEIGHT; ++i) {
        if (curBoard[i][curX] != nullptr) {
            output.emplace_back(currPosition, Pos(i, curX),
                                this, curBoard[i][curX]);
            break;
        }
    }
    for (int i = curY; i >= 0; --i) {
        if (curBoard[i][curX] != nullptr) {
            output.emplace_back(currPosition, Pos(i, curX),
                                this, curBoard[i][curX]);
            break;
        }
    }
    return output;
}
