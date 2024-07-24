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

    // Helper lambda to check captures in a straight line
    auto checkLine = [&](int dx, int dy) {
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

    // Check all four straight-line directions
    checkLine(1, 0);   // Moving right
    checkLine(-1, 0);  // Moving left
    checkLine(0, 1);   // Moving up
    checkLine(0, -1);  // Moving down

    return output;
}
