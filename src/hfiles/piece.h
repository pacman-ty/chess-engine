#ifndef PIECE_H
#define PIECE_H
#include <vector>
#include "position.h"
#include "move.h"
#include "colour.h"
#include "board.h"

class Piece : public Board {
protected:
    char name;
    Colour side;
    Pos currPosition;
    Board* board;
public:
    Piece(Board * b);
    virtual std::vector<Move> getPossibleMove() = 0;
    virtual std::vector<Move> getPossibleCaptures() = 0;
};

#endif 
