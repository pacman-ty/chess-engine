#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"
#include "move.h"
#include "position.h"

class Knight : public Piece {
public:
    // return list of possible moves (does not mean that moves are legal)
    std::vector<Move> getPossibleMove() override;
    // return list of attacking moves (does not mean that moves are legal)
    std::vector<Move> getPossibleCaptures() override;
}

#endif
