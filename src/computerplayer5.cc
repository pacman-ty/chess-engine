#include "computerplayer5.h"

ComputerPlayer5::ComputerPlayer5(Colour colour, Board *board) : Player(colour, board) {}

Move ComputerPlayer5::move() {
    // very similar to bot 3 but with enhanced capture and avoid move selection
    Move out;
    std::vector<Move> checkMoves = board->getCheckMoves(side);

    // prioritize moves that lead to check
    if (!checkMoves.empty()) {
        out = board->getRandomMove(checkMoves);
    }
    else {
        // prioritize capturing enemy with highest weight
        std::vector<Move> captureMoves = board->getCaptureMoves(side);
        if (!captureMoves.empty()) {
            int highest_move = -1;
            Move bestCaptureMove = board->getRandomMove(captureMoves);
            // Find move that captures the highest weight value
            for (auto m : captureMoves) {
                if (m.getCapture() && m.getCapture()->getValue() > highest_move) {
                    bestCaptureMove = m;
                }
            }
            out = bestCaptureMove;
        }
        else {
            // prioritize avoiding capture
            std::vector<Move> avoidCaptureMoves = board->getAvoidCaptureMoves(side);
            if (!avoidCaptureMoves.empty()) {
                out = board->getRandomMove(avoidCaptureMoves);
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