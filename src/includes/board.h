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
    bool checkCastling(const Move & m);
    bool tryCastling(const Move & m, Piece* k, Piece* besideKing, Piece* r, Position newKingPosn, Position newRookPosn);
    void forcePlayMove(const Move & m);
    bool isValidMove(const Move & m) const;
    void capture(Piece * p);
    bool isCheck(Colour side);
    bool isStalemate(Colour side);
    bool isCheckmate(Colour side);
    bool isInsufficientMaterial() const;
    bool checkPawnPromotion(int newX, int newY);
    void promptPawnPromotion(int newX, int newY);
    void promote(int newX, int newY, Type t);
    const BoardType& getBoard() const;
    const Piece* getItem(int x, int y) const;
    void clear();
    std::vector<Move> getLegalMoves(Colour side);
    std::vector<Move> getCheckMoves(Colour side);
    std::vector<Move> getCaptureMoves(Colour side);
    std::vector<Move> getAvoidCaptureMoves(Colour side);
    Move getRandomMove(const std::vector<Move> m);
    std::vector<Piece *> getPieces(const Colour & side);
};

#endif
