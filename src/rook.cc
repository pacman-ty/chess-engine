#include "rook.h"

Rook::Rook(Board *board) : Piece{board} {}

std::vector<Move> Rook::getPossibleMove() const {
    std::vector<Move> output;
    const Piece*** curBoard = board.getBoard();
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

std::vector<Move> Rook::getPossibleCaptures() const {
    std::vector<Move> output;
    const Piece*** curBoard = board->getBoard();
    int curX = currPosition.getX();
    int curY = currPosition.getY();

    for (int i = curX; i < BOARD_MAX_WIDTH; ++i) {
        if (curBoard[i][curY] != nullptr) {
            output.emplace_back(currPosition, Position(i, curY),
                                this, curBoard[curY][i]);
            break;
        }
    }
    for (int i = curX; i >= 0; --i) {
        if (curBoard[i][curY] != nullptr) {
            output.emplace_back(currPosition, Position(i, curY),
                                this, curBoard[curY][i]);
            break;
        }
    }
    for (int i = curY; i < BOARD_MAX_HEIGHT; ++i) {
        if (curBoard[curX][i] != nullptr) {
            output.emplace_back(currPosition, Position(curX, i),
                                this, curBoard[i][curX]);
            break;
        }
    }
    for (int i = curY; i >= 0; --i) {
        if (curBoard[curX][i] != nullptr) {
            output.emplace_back(currPosition, Position(curX, i),
                                this, curBoard[i][curX]);
            break;
        }
    }
    return output;
}
