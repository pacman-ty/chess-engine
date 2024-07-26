#include "computerplayer2.h"

ComputerPlayer2::ComputerPlayer2(Colour side, Board *board) : Player(side, board) {}

Move ComputerPlayer2::move() {
    Move out;
    std::vector<Move> checkMoves = board->getCheckMoves(side);

    // prioritize moves that lead to check
    if (!checkMoves.empty()) {
        out = board->getRandomMove(checkMoves);
    } else {
        std::vector<Move> captureMoves = board->getCaptureMoves(side);
        // then prioritize move that lead to capture
        if (!captureMoves.empty()) {
            out = board->getRandomMove(captureMoves);
        } else {
            // random move
            std::vector<Move> legalMoves = board->getLegalMoves(side);
            out = board->getRandomMove(legalMoves);
        }
    }

    if (!isLegalMove(out)) {
        return move();
    }
    return out;
}
