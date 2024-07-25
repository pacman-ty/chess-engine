#ifndef PLAYER_H
#define PLAYER_H

#include "controller.h"
#include "board.h"

class Board;
class Piece;

class Player {
protected:
    Colour side;
    Board *board;
public:
    Player(Colour side, Board * b);
    virtual Move move() = 0;
};
#endif
