#include "computerplayer4.h"

ComputerPlayer4::ComputerPlayer4(Colour colour, Board *board) : Player(colour, board) {}

Move ComputerPlayer4::move() {
    // very similar to bot 3 but with enhanced capture move selection
    Move out;
    std::vector<Move> checkMoves = board->getCheckMoves(side);

    // prioritize moves that lead to check
    if (!checkMoves.empty()) {
        out = board->getRandomMove(checkMoves);
    }
    else {
        // prioritize moves that lead to a capture (highest weight)
        std::vector<Move> captureMoves = board->getCaptureMoves(side);
        if (!captureMoves.empty()) {
            int highest_move = -1;
            Move best_move = board->getRandomMove(captureMoves);
            // Find move that captures the highest weight value
            for (auto m : captureMoves) {
                if (m.getCapture() && m.getCapture()->getValue() > highest_move
                    && m.getCapture()->getSide() != side) {
                    highest_move = m.getCapture()->getValue();
                    best_move = m;
                }
            }
            out = best_move;
        }
        else {
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
