#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

const char ROOK_SYM = 'r';

class Rook : public Piece {
public:
    Rook();
    // return list of possible moves (does not mean that moves are legal)
    virtual std::vector<Move> getPossibleMoves(const Board::BoardType &) const override;
    // return list of attacking moves (does not mean that moves are legal)
    virtual std::vector<Move> getPossibleCaptures(const Board::BoardType &) const override;
};

#endif
