#include "move.h"
#include "piece.h"

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

bool Move::isCastle() const {
    if (target->getType() != Type::KING) {
        return false;
    }
    if (target->getSide() == Colour::WHITE) {
        return oldPos == Position{4, 0} && (newPos == Position{6, 0} || newPos == Position{2, 0});
    } else {
        return oldPos == Position{4, 7} && (newPos == Position{6, 7} || newPos == Position{2, 7});
    }
}
