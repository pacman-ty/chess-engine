#ifndef PLAYER_H
#define PLAYER_H

#include "colour.h"
#include "board.h"
class Player {
    Colour side;
    Board board;
public:
    virtual void move(Move m, Piece promotion) = 0;
};
#endif
