#ifndef PIECE_H
#define PIECE_H

#include "board.h"

class Piece {
protected:
    Colour side;
    Position currPosition;
    Type t;
public:
    Piece(Type t);
    virtual ~Piece() = default;
    virtual std::vector<Move> getPossibleMoves(const Board::BoardType & b) const = 0;
    virtual std::vector<Move> getPossibleCaptures(const Board::BoardType & b) const = 0;
    Colour getSide() const;
    Type getType() const;
    Position getPos() const;
    void setSide(Colour c);
    void setPos(Position p);
};

#endif 
