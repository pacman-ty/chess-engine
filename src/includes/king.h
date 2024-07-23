#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
protected:
    // keeps track if the king has moved yet for castling purposes
    bool hasMoved = false;
public:
    King();
    // return list of possible moves (does not mean that moves are legal)
    virtual std::vector<Move> getPossibleMoves(const Board::BoardType &) const override;
    // return list of attacking moves (does not mean that moves are legal)
    virtual std::vector<Move> getPossibleCaptures(const Board::BoardType &) const override;
};

#endif