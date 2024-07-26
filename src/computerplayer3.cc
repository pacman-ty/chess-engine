#include "computerplayer3.h"

ComputerPlayer3::ComputerPlayer3(Colour colour, Board *board) : Player(colour, board) {}

Move ComputerPlayer3::move() {
    // very similar to bot2 except this bot avoids capture before it gets captured
    // whether that means actually better performance...
    std::vector<Move> checkMoves = board->getCheckMoves(side);

    if (!checkMoves.empty()) return board->getRandomMove(checkMoves);

    std::vector<Move> avoidCaptureMoves = board->getAvoidCaptureMoves(side);

    if (!avoidCaptureMoves.empty()) return board->getRandomMove(avoidCaptureMoves);

    std::vector<Move> captureMoves = board->getCaptureMoves(side);

    if (!captureMoves.empty()) return board->getRandomMove(captureMoves);

    std::vector<Move> legalMoves = board->getLegalMoves(side);

    return board->getRandomMove(legalMoves);
}