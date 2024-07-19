#ifndef PIECE_H
#define PIECE_H
#include "position.h"
#include "move.h"

enum Colour = {white, black, empty}

class Piece : public Board {
protected:
    char name;
    Colour side;
    Pos currPosition;
public:
    getPossibleMove();
    getPossibleAttack();
};

#endif 
