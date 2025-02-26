#ifndef MOVE_H
#define MOVE_H

#include "position.h"

class Piece;

class Move {
private:
    Position oldPos;
    Position newPos;
    const Piece* target;
    const Piece* capture; 
public:
    Move() = default;
    Move(Position oldPos, Position newPos, const Piece *target, const Piece *capture);
    Position getOldPosition() const;
    Position getNewPosition() const;
    const Piece* getCapture() const;
    const Piece* getTarget() const;
};

#endif