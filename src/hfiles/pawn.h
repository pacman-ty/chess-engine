#ifndef PAWN_H
#define PAWN_H

#include "piece.h" 
#include "move.h"
#include "position.h"

class Pawn : public Piece {
protected:
    // keeps track if the pawn has moved yet for double move purposes
    bool hasMoved = false;
public:
    // return list of possible moves (does not mean that moves are legal)
    virtual std::vector<Move> getPossibleMoves(Board::BoardType &) const override;
    // return list of attacking moves (does not mean that moves are legal)
    virtual std::vector<Move> getPossibleCaptures(Board::BoardType &) const override;
};

#endif 
