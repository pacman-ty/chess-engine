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
<<<<<<< HEAD
    Move() = default;
    Move(Position oldPos, Position newPos, const Piece *target, Piece *capture);
=======
    Move(Position oldPos, Position newPos, const Piece *target, const Piece *capture);
>>>>>>> 7e486e5fa6fa83927de3a84903739f2446a56554
    Position getOldPosition() const;
    Position getNewPosition() const;
    const Piece* getCapture() const;
    const Piece* getTarget() const;
};

#endif