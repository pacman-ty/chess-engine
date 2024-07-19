#ifndef KING_H
#define KING_H

#include "piece.h"
#include "move.h"
#include "position.h"

class King : public Piece {
protected:
    // keeps track if the king has moved yet for castling purposes
    bool hasMoved = false;
public:
    // check hasMoved variable to see if the king has moved yet
    getHasMoved();
    // set hasMoved to true after king does its first move 
    didFirstMove();
    // return list of possible moves (does not mean that moves are legal)
    getPossibleMoves();
    // return list of attacking moves (does not mean that moves are legal)
    getPossibeAttacks();
}

#endif
