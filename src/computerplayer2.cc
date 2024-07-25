#include "computerplayer2.h"

ComputerPlayer2::ComputerPlayer2(Colour side, Board *board) : Player(side, board) {}

Move ComputerPlayer2::move() {
    std::vector<Move> checkMoves = ;
    std::vector<Move> captureMoves;
    std::vector<Move> legalMoves = board->getLegalMoves(side);

    if (!checkMoves.empty()) return board->getRandomMove(checkMoves);

    return board->getRandomMove(legalMoves);
}
