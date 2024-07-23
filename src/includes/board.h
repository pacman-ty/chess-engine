#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "subject.h"
#include "piece.h"
#include "position.h"
#include "move.h"
#include "type.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "pawn.h"

const int BOARD_MIN_HEIGHT = 0;
const int BOARD_MIN_WIDTH = 0;
const int BOARD_MAX_HEIGHT = 8;
const int BOARD_MAX_WIDTH = 8;

class Board : public Subject {
public:
    using BoardType = Piece* [BOARD_MAX_WIDTH][BOARD_MAX_HEIGHT];
private:
    std::vector<Piece *> whitePieces;
    std::vector<Piece *> blackPieces;
    BoardType board; // board[x][y]
public:
    Board();
    ~Board();
    void cloneBoard(const Board &);
    void placePiece(Colour side, Type t, const Position & pos);
    void removePiece(Position p);
    void playMove(const Move & m);
    void playMove(Position oldPos, Position newPos);
    bool isValidMove(const Move & m) const;
    bool isCheck(Colour c) const;
    const BoardType& getBoard() const;
    const Piece* getItem(int x, int y) const;
};

#endif
