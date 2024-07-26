#include "move.h"

Move::Move(Position oldPos, Position newPos, const Piece *target, Piece *capture) 
    : oldPos(oldPos), newPos(newPos), target(target), capture(capture) {}

Position Move::getOldPosition() const {
    return oldPos;
}
Position Move::getNewPosition() const {
    return newPos;
}
Piece* Move::getCapture() const {
    return capture;
}
const Piece* Move::getTarget() const {
    return target;
}
