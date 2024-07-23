#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

const char ROOK_SYM = 'r';

class Rook : public Piece {
    // keeps track if the rook has moved yet for castling purposes
    bool hasMoved = false;
public:
    Rook();
    // return list of possible moves (does not mean that moves are legal)
    virtual std::vector<Move> getPossibleMoves(const Board::BoardType &) const override;
    // return list of attacking moves (does not mean that moves are legal)
    virtual std::vector<Move> getPossibleCaptures(const Board::BoardType &) const override;
};

std::ostream& operator<<(std::ostream& out, Rook & r);

#endif
