#ifndef MOVE_H
#define MOVE_H

#include "position.h"
#include "piece.h"

class Move {
private:
    Pos oldPos;
    Pos newPos;
    Piece target;
    Piece caputre; 
public:
    getOldPosition();
    getNewPosition();
};

#endif
