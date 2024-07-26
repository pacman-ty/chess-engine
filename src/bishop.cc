#include "bishop.h"

Bishop::Bishop() : Piece{Type::BISHOP} {}

// checks each direction the bishop can move not including captures and return a vector contain the moves
std::vector<Move> Bishop::getPossibleMoves(const Board::BoardType &board) const {
    std::vector<Move> output;
    int curX = currPosition.getX();
    int curY = currPosition.getY();

    // Direction vectors for the four diagonal directions
    const std::vector<std::pair<int, int>> directions = {
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    for (const auto& direction : directions) {
        int x = curX + direction.first;
        int y = curY + direction.second;

        // Bounds Checking
        while (x >= BOARD_MIN_WIDTH && x < BOARD_MAX_WIDTH &&
               y >= BOARD_MIN_HEIGHT && y < BOARD_MAX_HEIGHT) {
            if (board[x][y] != nullptr) break; // Check if there is a piece
            output.emplace_back(currPosition, Position(x, y), this, nullptr);
            // move diagonal
            x += direction.first;
            y += direction.second;
        }
    }

    return output;
}

std::vector<Move> Bishop::getPossibleCaptures(const Board::BoardType & board) const {
    std::vector<Move> output;
    int curX = currPosition.getX();
    int curY = currPosition.getY();

    auto checkDirection = [&](int dx, int dy) {
        int x = curX + dx;
        int y = curY + dy;

        // Bounds check
        while (x >= BOARD_MIN_WIDTH && x < BOARD_MAX_WIDTH && y >= BOARD_MIN_HEIGHT && y < BOARD_MAX_HEIGHT) {
            if (board[x][y] != nullptr) { // Check if it hits a piece
                if (board[x][y]->getSide() != this->getSide()) {
                    output.emplace_back(currPosition, Position(x, y), this, board[x][y]);
                }
                break;
            }
            // Move diagonally
            x += dx;
            y += dy;
        }
    };

    checkDirection(1, 1);   // Moving up-right
    checkDirection(1, -1);  // Moving down-right
    checkDirection(-1, 1);  // Moving up-left
    checkDirection(-1, -1); // Moving down-left

    return output;
}
