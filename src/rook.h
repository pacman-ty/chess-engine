#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include "move.h"
#include "position.h"

class Rook : public Piece {
protected:
    // keeps track if the rook has moved yet for castling purposes
    bool hasMoved = false;
public:
    // check hasMoved variable to see if the rook has moved yet
    getHasMoved();
    // set hasMoved to true after rook does its first move
    didFirstMove();
    // return list of possible moves (does not mean that moves are legal)
    getPossibleMoves();
    // return list of attacking moves (does not mean that moves are legal)
    getPossibeAttacks();
}

#endif
