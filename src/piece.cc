#include "piece.h"

Piece::Piece(Type t) : t{t} {}

Colour Piece::getSide() const {
    return side;
}

Type Piece::getType() const {
    return t;
}

Position Piece::getPos() const {
    return currPosition;
}

void Piece::setSide(Colour c) {
    side = c;
}

void Piece::setPos(Position p) {
    currPosition = p;
}
