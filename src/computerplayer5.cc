#include "computerplayer5.h"

ComputerPlayer5::ComputerPlayer5(Colour colour, Board *board) : Player(colour, board) {}

Move ComputerPlayer5::move() {
    // very similar to bot 3 but with enhanced capture and avoid move selection
    std::vector<Move> checkMoves = board->getCheckMoves(side);

    if (!checkMoves.empty()) return board->getRandomMove(checkMoves);

    std::vector<Move> captureMoves = board->getCaptureMoves(side);

    if (!captureMoves.empty()) {
        int highest_move = -1;
        Move bestCaptureMove = board->getRandomMove(captureMoves);
        // Find move that captures the highest weight value
        for (auto m : captureMoves) {
            if (m.getCapture() && m.getCapture()->getValue() > highest_move
                && m.getCapture()->getSide() != side) {
                highest_move = m.getCapture()->getValue();
                bestCaptureMove = m;
            }
        }
        return bestCaptureMove;
    }

    std::vector<Move> avoidCaptureMoves = board->getAvoidCaptureMoves(side);

    if (!avoidCaptureMoves.empty()) return board->getRandomMove(avoidCaptureMoves);

    std::vector<Move> legalMoves = board->getLegalMoves(side);

    return board->getRandomMove(legalMoves);
}