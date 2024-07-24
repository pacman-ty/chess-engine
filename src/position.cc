#include "position.h"
#include "board.h"

Position::Position(int x, int y): x(x), y(y) {}

int Position::getX() const {
    return x;
}

int Position::getY() const {
    return y;
}

void Position::setX(int val) {
    x = val;
}

void Position::setY(int val) {
    y = val;
}

bool Position::operator==(const Position rhs) const {
    return x == rhs.x && y == rhs.y;
}


std::istream& operator>>(std::istream& in, Position& rhs) {
    char rank;
    in >> rank;
    int file = 0;
    in >> file;
    --file; // Given position is 1-8, translate to 0-7
    rank -= 'a'; // Translate 'a'-'h' to 0-7
    if (rank < BOARD_MIN_WIDTH || rank >= BOARD_MAX_WIDTH) {
        throw std::invalid_argument("Invalid rank");
    }
    if (file < BOARD_MIN_HEIGHT || file >= BOARD_MAX_HEIGHT) {
        throw std::invalid_argument("Invalid file");
    }

    rhs.setX(rank); 
    rhs.setY(file);
    return in;
}
