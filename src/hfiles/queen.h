#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "move.h"
#include "position.h"

class Queen : public Piece {
public:
    // return list of possible moves (does not mean that moves are legal)
    virtual std::vector<Move> getPossibleMoves(Board::BoardType &) const override;
    // return list of attacking moves (does not mean that moves are legal)
    virtual std::vector<Move> getPossibleCaptures(Board::BoardType &) const override;
};

#endif
