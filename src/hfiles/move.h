#ifndef MOVE_H
#define MOVE_H

#include "position.h"
#include "piece.h"

class Move {
private:
    Pos oldPos;
    Pos newPos;
    Piece* target;
    Piece* capture; 
public:
    Move(Pos oldPos, Pos newPos, Piece target, Piece capture);
    Pos getOldPosition();
    Pos getNewPosition();
    Piece* getCapture();
    Piece* getTarget();
};

#endif
