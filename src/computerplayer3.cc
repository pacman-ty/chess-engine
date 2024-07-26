#include "computerplayer3.h"

ComputerPlayer3::ComputerPlayer3(Colour colour, Board *board) : Player(colour, board) {}

Move ComputerPlayer3::move() {
    // very similar to bot2 except this bot avoids capture before it gets captured
    // whether that means actually better performance...
    Move out;
    std::vector<Move> checkMoves = board->getCheckMoves(side);

    // prioritize moves that lead to check
    if (!checkMoves.empty()) {
        out = board->getRandomMove(checkMoves);
    }
    else {
        // prioritize avoiding capturing by enemy
        std::vector<Move> avoidCaptureMoves = board->getAvoidCaptureMoves(side);
        if (!avoidCaptureMoves.empty()) {
            out = board->getRandomMove(avoidCaptureMoves);
        }
        else {
            // prioritize move that lead to capture
            std::vector<Move> captureMoves = board->getCaptureMoves(side);
            if (!captureMoves.empty()) {
                out = board->getRandomMove(captureMoves);
            }
            else {
                // random move
                std::vector<Move> legalMoves = board->getLegalMoves(side);
                out = board->getRandomMove(legalMoves);
            }
        }
    }
    if (!isLegalMove(out)) {
        return move();
    }
    return out;
}