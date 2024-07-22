#ifndef PIECE_H
#define PIECE_H
#include <vector>
#include "position.h"
#include "move.h"
#include "colour.h"
#include "board.h"
#include "type.h"

class Piece {
protected:
    Colour side;
    Position currPosition;
    Board* board;
    Type t;
public:
    virtual std::vector<Move> getPossibleMove() const = 0;
    virtual std::vector<Move> getPossibleCaptures() const = 0;
    Colour getSide() const;
    Type getType() const;
    Position getPos() const;
};

#endif 
