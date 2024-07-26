#include "computerplayer2.h"

ComputerPlayer2::ComputerPlayer2(Colour side, Board *board) : Player(side, board) {}

Move ComputerPlayer2::move() {
    std::vector<Move> checkMoves = board->getCheckMoves(side);
    
    if (!checkMoves.empty()) return board->getRandomMove(checkMoves);

    std::vector<Move> captureMoves = board->getCaptureMoves(side);

    if (!captureMoves.empty()) return board->getRandomMove(captureMoves);

    std::vector<Move> legalMoves = board->getLegalMoves(side);

    return board->getRandomMove(legalMoves);
}
