#ifndef PIECE_H
#define PIECE_H
#include "position.h"
#include "move.h"

enum Colour = {white, black, empty}
class Piece {
protected:
    char name;
    Colour side;
    Pos square;
public:
    getPossibleMove();
    getPossibleAttack();
}

#endif 
