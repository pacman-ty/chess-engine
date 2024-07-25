#include "computerplayer1.h"

ComputerPlayer1::ComputerPlayer1(Colour colour, Board *board) : Player(colour, board) {}

Move ComputerPlayer1::move() {
    Piece* randPiece = board->getRandomPiece(side);
    
    // Theoretically this should be fine 
    // The board should never be in a state where it doesnt have a legal move (stalemate)
    while(board->getLegalMoves(*randPiece).empty()) {
        randPiece = board->getRandomPiece(side);
    }
    
    // should i be destroying randPiece?? no? i think
    return board->getRandomMove(*randPiece);
}
