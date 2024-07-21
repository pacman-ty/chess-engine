#ifndef PIECE_H
#define PIECE_H
#include <vector>
#include "position.h"
#include "move.h"
#include "colour.h"

class Piece : public Board {
protected:
    char name;
    Colour side;
    Pos currPosition;
public:
    virtual std::vector<Move> getPossibleMove() = 0;
    virtual std::vector<Move> getPossibleCaptures() = 0;
};

#endif 
