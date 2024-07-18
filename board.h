#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "subject.h"
#include "piece.h"
#include "position.h"
#include "move.h"

class Board : public Subject {
    std::vector<Piece> pieces;
    std::vector<Move> moveHistory;
public:
    void placePiece(Piece *piece, Position position);
    std::vector<Move> getLegalMoves();
};

#endif
