#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "subject.h"

//temporary declarations:
class Piece;
class Position;
class Move;

class Board : public Subject {
    Piece *pieces[8][8];
    std::vector<Move> moveHistory;
public:
    void placePiece(Piece *piece, Position position);
    std::vector<Move> getLegalMoves();
};

#endif
