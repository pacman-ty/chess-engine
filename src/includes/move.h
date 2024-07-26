#ifndef MOVE_H
#define MOVE_H

#include "position.h"

class Piece;

class Move {
private:
    Position oldPos;
    Position newPos;
    const Piece* target;
    Piece* capture; 
public:
    Move(Position oldPos, Position newPos, const Piece *target, Piece *capture);
    Position getOldPosition() const;
    Position getNewPosition() const;
    Piece* getCapture() const;
    const Piece* getTarget() const;
};

#endif
