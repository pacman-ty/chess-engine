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
public:
    Board() = default;
    ~Board();
    using BoardType = Piece* [BOARD_MAX_WIDTH][BOARD_MAX_HEIGHT];
    void placePiece(Piece & piece, const Position & pos);
    void removePiece(const Piece & p);
    void playMove(const Move & m);
    bool isValidMove(const Move & m) const;
    const BoardType& getBoard() const;
    const Piece& getItem(int x, int y) const;
private:
    BoardType board; // board[x][y]
};

#endif
