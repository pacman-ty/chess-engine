#include "piece.h"

Piece::Piece(Type t) : t{t} {}

Piece::getSide() {
    return side;
}

Piece::getType() {
    return t;
}

Piece::getPos() {
    return currPosition;
}

Piece::setSide(Colour c) {
    colour = c;
}

Piece::setPos(Position p) {
    currPosition = p;
}
