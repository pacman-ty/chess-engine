#include "computerplayer1.h"

ComputerPlayer1::ComputerPlayer1(Colour colour, Board *board) : Player(colour, board) {}

Move ComputerPlayer1::move() {
    std::vector<Move> legalMoves = board->getLegalMoves(side);
    // generate random move
    Move out = board->getRandomMove(legalMoves);
    if (!isLegalMove(out)) return move();
    return out;
}
