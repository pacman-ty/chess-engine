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
    Piece*** board;
public:
    class Iterator{
        int curIndex;
    protected:
        Iterator(int index);
    public:
        Iterator& operator++();
        Piece& operator*() const;
        bool operator==(Iterator &) const;
    };
    void placePiece(Piece *piece, Pos position);
    std::vector<Move> getLegalMoves() const;
    Piece*** getBoard() const;
    Iterator begin() const;
    Iterator end() const;
};

#endif
