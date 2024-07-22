#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include "move.h"
#include "position.h"

class Rook : public Piece {
    // keeps track if the rook has moved yet for castling purposes
    bool hasMoved = false;
public:
    // return list of possible moves (does not mean that moves are legal)
    std::vector<Move> getPossibleMove() const override;
    // return list of attacking moves (does not mean that moves are legal)
    std::vector<Move> getPossibleCaptures() const override;
};

#endif
