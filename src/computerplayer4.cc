#include "computerplayer4.h"

ComputerPlayer4::ComputerPlayer4(Colour colour, Board *board) : Player(colour, board) {}

Move ComputerPlayer4::move() {
    // very similar to bot 3 but with enhanced capture move selection
    std::vector<Move> checkMoves = board->getCheckMoves(side);

    if (!checkMoves.empty()) return board->getRandomMove(checkMoves);

    std::vector<Move> avoidCaptureMoves = board->getAvoidCaptureMoves(side);

    if (!avoidCaptureMoves.empty()) return board->getRandomMove(avoidCaptureMoves);

    std::vector<Move> captureMoves = board->getCaptureMoves(side);

    if (!captureMoves.empty()) return board->getRandomMove(captureMoves);
    
    int highest_move = -1;

    std::vector<Move> legalMoves = board->getLegalMoves(side);
    Move best_move = board->getRandomMove(legalMoves);

    // Find move that captures the highest weight value
    for (auto m : legalMoves) {
        if (m.getCapture() && m.getCapture()->getValue() > highest_move) {
            highest_move = m.getCapture()->getValue();
            best_move = m;
        }
    }

    return best_move;
}
