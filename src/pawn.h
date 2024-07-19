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
    // check hasMoved variable to see if the pawn has moved yet
    getHasMoved();
    // set hasMoved to true after pawn does its first move
    didFirstMove();
    // return list of possible moves (does not mean that moves are legal)
    getPossibleMoves();
    // return list of attacking moves (does not mean that moves are legal)
    getPossibeAttacks();
}

#endif 
