#include "piece.h"

Piece::Piece(Type t) : t{t} {}

int Piece::getValue() const {
    switch(t) {
        case Type::PAWN: return 1;
        case Type::BISHOP: return 3;
        case Type::KNIGHT: return 3;
        case Type::ROOK: return 5;
        case Type::QUEEN: return 9;
        case Type::KING: return KING_VALUE;
        default:
            return 0;
    }
}

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
