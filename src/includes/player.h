#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include "piece.h"

class Player {
protected:
    Colour side;
    Board *board;
public:
    Player(Colour side, Board * b);
    bool isLegalMove(Move m);
    virtual Move move() = 0;
    virtual ~Player() = default;
};
#endif
