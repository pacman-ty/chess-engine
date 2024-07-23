#include "knight.h"
Knight::Knight() : Piece{Type::Knight} {}

// check each direction the rook can move not including captures and return a vector containing the moves 
std::vector<Move> Rook::getPossibleMoves(const Board::BoardType & board) const {
    std::vector<Move> output;
    int curX = currPosition.getX();
    int curY = currPosition.getY();