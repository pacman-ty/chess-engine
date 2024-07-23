#ifndef PLAYER_H
#define PLAYER_H

#include "controller.h"

class Board;
class Piece;

class Player {
    Colour side;
    Board *board;
public:
    virtual void move(Move m, Piece *promotion) = 0;
};
#endif
