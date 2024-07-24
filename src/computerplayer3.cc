#include "computerplayer3.h"

ComputerPlayer3::ComputerPlayer3(Colour colour, Board *board) : Player(colour, board) {}

Move ComputerPlayer3::move() {
    return Move(Position{0,0},Position{0,0},nullptr, nullptr);
}