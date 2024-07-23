#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

const int INITIAL_DASH = 2;
const int WHITE_PAWN_START = 1;
const int BLACK_PAWN_START = 6;

class Pawn : public Piece {
    // keeps track if the pawn has moved yet for double move purposes
    mutable bool hasMoved = false;
public:
    Pawn();
    // return list of possible moves (does not mean that moves are legal)
    virtual std::vector<Move> getPossibleMoves(const Board::BoardType &) const override;
    // return list of attacking moves (does not mean that moves are legal)
    virtual std::vector<Move> getPossibleCaptures(const Board::BoardType &) const override;
};

#endif 
