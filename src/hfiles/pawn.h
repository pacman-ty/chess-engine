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
    std::vector<Move> getPossibleMove() override;
    // return list of attacking moves (does not mean that moves are legal)
    std::vector<Move> getPossibleCaptures() override;
}

#endif 
