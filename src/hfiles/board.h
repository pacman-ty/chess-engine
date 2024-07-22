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
        friend class Board;
        int curIndex;
        Iterator(int index);
    public:
        Iterator& operator++();
        Piece& operator*() const;
        bool operator==(const Iterator &) const;
    };
    void placePiece(char type, Position position);
    void removePiece(Position position);
    std::vector<Move> getLegalMoves() const;
    Piece*** getBoard() const;
    Iterator begin() const;
    Iterator end() const;
    void clear();
};

#endif
