#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "subject.h"
#include "piece.h"
#include "position.h"
#include "move.h"

const int BOARD_HEIGHT = 8;
const int BOARD_WIDTH = 8;

class Board : public Subject {
    std::vector<Piece> pieces;
    std::vector<Move> moveHistory;
    Piece** board;
public:
    void placePiece(Piece *piece, Position position);
    std::vector<Move> getLegalMoves();
    Piece*** getBoard();
};

#endif
