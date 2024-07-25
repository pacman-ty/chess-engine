#include "computerplayer2.h"

ComputerPlayer2::ComputerPlayer2(Colour side, Board *board) : Player(side, board) {}

Move ComputerPlayer2::move() {
    std::vector<Piece *> pieces = board->getPieces(side);
}
