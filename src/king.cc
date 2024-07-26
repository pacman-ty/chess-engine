#include "king.h"

King::King() : Piece{Type::KING} {}

// checks each direction the King can move in and returns a vector of valid moves  
std::vector<Move> King::getPossibleMoves(const Board::BoardType & board) const {
    std::vector<Move> output;
    int curX = currPosition.getX();
    int curY = currPosition.getY();

    auto addMove = [&](int newX, int newY) {
        if (newX >= BOARD_MIN_WIDTH && newX < BOARD_MAX_WIDTH &&
            newY >= BOARD_MIN_HEIGHT && newY < BOARD_MAX_HEIGHT) {
            if (board[newX][newY] == nullptr) {
                output.emplace_back(currPosition, Position{newX, newY}, this, nullptr);
            }
        }
    };

    addMove(curX + 1, curY + 1); // Move diagonally right-up
    addMove(curX + 1, curY - 1); // Move diagonally right-down
    addMove(curX + 1, curY);     // Move right
    addMove(curX - 1, curY + 1); // Move diagonally left-up
    addMove(curX - 1, curY - 1); // Move diagonally left-down
    addMove(curX - 1, curY);     // Move left
    addMove(curX, curY + 1);     // Move up
    addMove(curX, curY - 1);     // Move down

    return output;
}

// checks each direction the king can move in and sees if it captures anything and returns a vector containing the catures
std::vector<Move> King::getPossibleCaptures(const Board::BoardType & board) const {
    std::vector<Move> output;
    int curX = currPosition.getX();
    int curY = currPosition.getY();

    auto addMove = [&](int newX, int newY) {
        if (newX >= BOARD_MIN_WIDTH && newX < BOARD_MAX_WIDTH &&
            newY >= BOARD_MIN_HEIGHT && newY < BOARD_MAX_HEIGHT) {
            if (board[newX][newY] != nullptr) {
                output.emplace_back(currPosition, Position{newX, newY}, this, board[newX][newY]);
            }
        }
    };

    addMove(curX + 1, curY + 1); // Move diagonally right-up
    addMove(curX + 1, curY - 1); // Move diagonally right-down
    addMove(curX + 1, curY);     // Move right
    addMove(curX - 1, curY + 1); // Move diagonally left-up
    addMove(curX - 1, curY - 1); // Move diagonally left-down
    addMove(curX - 1, curY);     // Move left
    addMove(curX, curY + 1);     // Move up
    addMove(curX, curY - 1);     // Move down

    return output;
}