#ifndef PIECE_H
#define PIECE_H
#include "position.h"
#include "move.h"
#include "colour.h"

class Piece : public Board {
protected:
    char name;
    Colour side;
    Pos currPosition;
public:
    virtual vector<Move> getPossibleMove() = 0;
    virtual vector<Move> getPossibleAttack() = 0;
};

#endif 
