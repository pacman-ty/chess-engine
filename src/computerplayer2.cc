#include "computerplayer2.h"

ComputerPlayer2::ComputerPlayer2(Colour colour, Board *board) : Player(colour, board) {}

Move ComputerPlayer2::move() {
    return Move(Position{0,0},Position{0,0},nullptr, nullptr);
}
