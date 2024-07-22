#include "position.h"

Position::Position(): x(0), y(0) {}
Position::Position(int x, int y): x(x), y(y) {}

int Position::getX() const {
    return x;
}

int Position::getY() const {
    return y;
}

istream& Position::operator>>(istream& in, Position rhs) {
    char rank;
    in >> rank;
    rhs.x = rank - 'a'; // Use value difference to translate a-f to 0-7

    int file = 0;
    in >> file;
    --file; // Given position is 1-8, translate to 0-7
    rhs.y = file;
    return in;
}