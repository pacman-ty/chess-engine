#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "subject.h"
#include "piece.h"
#include "position.h"
#include "move.h"

const int BOARD_MIN_HEIGHT = 0;
const int BOARD_MIN_WIDTH = 0;
const int BOARD_MAX_HEIGHT = 8;
const int BOARD_MAX_WIDTH = 8;

class Board : public Subject {
    std::vector<Piece> whitePieces;
    std::vector<Piece> blackPieces;
    std::vector<Move> moveHistory;
    Piece* board[BOARD_MAX_WIDTH][BOARD_MAX_HEIGHT]; // board[x][y]
public:
    void placePiece(Move & m);
    void removePiece(Piece & p);
    std::vector<Move> getLegalMoves() const;
    const Piece*& getBoard() const;
    void clear();
    ~Board();
};

#endif
