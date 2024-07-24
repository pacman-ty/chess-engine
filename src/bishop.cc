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

std::vector<Move> Bishop::getPossibleCaptures(const Board::BoardType & board) const {
    std::vector<Move> output;
    int curX = currPosition.getX();
    int curY = currPosition.getY();

    // Helper lambda to check captures in a given direction
    auto checkDirection = [&](int dx, int dy) {
        int x = curX + dx;
        int y = curY + dy;

        while (x >= BOARD_MIN_WIDTH && x < BOARD_MAX_WIDTH && y >= BOARD_MIN_HEIGHT && y < BOARD_MAX_HEIGHT) {
            if (board[x][y] != nullptr) {
                if (board[x][y]->getSide() != this->getSide()) {
                    output.emplace_back(currPosition, Position(x, y), this, board[x][y]);
                }
                break; // Stop scanning in this direction after a capture or obstacle
            }
            x += dx;
            y += dy;
        }
    };

    // Check all four diagonal directions
    checkDirection(1, 1);   // Moving up-right
    checkDirection(1, -1);  // Moving down-right
    checkDirection(-1, 1);  // Moving up-left
    checkDirection(-1, -1); // Moving down-left

    return output;
}
