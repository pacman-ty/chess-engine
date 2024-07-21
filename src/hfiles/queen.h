#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "move.h"
#include "position.h"

class Queen : public Piece {
public:
    // return list of possible moves (does not mean that moves are legal)
    std::vector<Move> getPossibleMove() const override;
    // return list of attacking moves (does not mean that moves are legal)
    std::vector<Move> getPossibleCaptures() const override;
};

#endif
