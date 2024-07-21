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
    Pos getOldPosition() const;
    Pos getNewPosition() const;
    Piece* getCapture() const;
    Piece* getTarget() const;
};

#endif
