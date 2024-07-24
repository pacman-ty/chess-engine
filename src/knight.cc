#include "knight.h"

Knight::Knight() : Piece{Type::KNIGHT} {}

// check each direction the knight can move not including captures and return a vector containing the moves 
std::vector<Move> Knight::getPossibleMoves(const Board::BoardType & board) const {
    std::vector<Move> output;
    int curX = currPosition.getX();
    int curY = currPosition.getY();
    const int knightMoves[8][2] = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };

    for (const auto& move : knightMoves) {
        int newX = curX + move[0];
        int newY = curY + move[1];

        if (newX >= BOARD_MIN_WIDTH && newX < BOARD_MAX_WIDTH && newY >= BOARD_MIN_HEIGHT && newY < BOARD_MAX_HEIGHT) {
            if (board[newX][newY] == nullptr) {
                output.emplace_back(currPosition, Position(newX, newY), this, nullptr);
            }
        }
    }

    return output;
}

// checks each direction the king can move in and sees if it captures anything and returns a vector containing the catures
std::vector<Move> Knight::getPossibleCaptures(const Board::BoardType & board) const {
    std::vector<Move> output;
    int curX = currPosition.getX();
    int curY = currPosition.getY();
    const int knightMoves[8][2] = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };

    for (const auto& move : knightMoves) {
        int newX = curX + move[0];
        int newY = curY + move[1];

        if (newX >= BOARD_MIN_WIDTH && newX < BOARD_MAX_WIDTH && newY >= BOARD_MIN_HEIGHT && newY < BOARD_MAX_HEIGHT) {
            if (board[newX][newY] != nullptr && board[newX][newY]->getSide() != side) {
                output.emplace_back(currPosition, Position(newX, newY), this, board[newX][newY]);
            }
        }
    }

    return output;
}
