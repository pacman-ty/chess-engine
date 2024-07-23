#ifndef PIECE_H
#define PIECE_H
#include <vector>
#include "position.h"
#include "move.h"
#include "colour.h"
#include "board.h"
#include "type.h"

class Piece {
    Colour side;
    Position currPosition;
    Type t;
public:
    Piece(Type t);
    virtual std::vector<Move> getPossibleMoves(const Board::BoardType & b) const = 0;
    virtual std::vector<Move> getPossibleCaptures(const Board::BoardType & b) const = 0;
    Colour getSide() const;
    Type getType() const;
    Position getPos() const;
    void setSide(Colour c);
    void setPos(Position p);
};

#endif 
