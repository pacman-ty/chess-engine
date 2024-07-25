#ifndef BOARD_H
#define BOARD_H

#include "colour.h"
#include "type.h"
#include "move.h"
#include "subject.h"

class Piece;

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
    void playMove(Position oldPos, Position newPos, Colour turn);
    void forcePlayMove(const Move & m);
    bool isValidMove(const Move & m) const;
    void capture(Piece * p);
    bool isCheck(Colour side) const;
    bool isCheckmate(Colour side) const;
    const BoardType& getBoard() const;
    const Piece* getItem(int x, int y) const;
    void clear();
    std::vector<Piece *> getPieces(Colour side);
    Piece* getRandomPiece(Colour side);
    Move getRandomMove(const Piece & p);
    std::vector<Move> getLegalMoves(const Piece & p);
};

#endif
