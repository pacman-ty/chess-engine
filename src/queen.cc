#include "queen.h"

Queen::Queen() : Piece{Type::QUEEN} {}

// checks each direction the queen can move not including captures and return a vector contain the moves
std::vector<Move> Queen::getPossibleMoves(const Board::BoardType & board) const {
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
std::vector<Move> Queen::getPossibleCaptures(const Board::BoardType & board) const {
    std::vector<Move> output;
    int curX = currPosition.getX();
    int curY = currPosition.getY();

    // Define all eight directions: horizontal, vertical, and diagonal
    const int directions[8][2] = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1},  // horizontal and vertical
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}  // diagonal
    };

    for (const auto& dir : directions) {
        int i = curX + dir[0];
        int j = curY + dir[1];

        while (i >= BOARD_MIN_WIDTH && i < BOARD_MAX_WIDTH && 
               j >= BOARD_MIN_HEIGHT && j < BOARD_MAX_HEIGHT) {
            if (board[i][j] != nullptr) {
                if (board[i][j]->getSide() != this->getSide()) {
                    output.emplace_back(currPosition, Position(i, j), this, board[i][j]);
                }
                break;  // Stop checking this direction after encountering any piece
            }
            i += dir[0];
            j += dir[1];
        }
    }
    
    return output;
}
