#include "computerplayer4.h"

ComputerPlayer4::ComputerPlayer4(Colour colour, Board *board) : Player(colour, board) {}

Move ComputerPlayer4::move() {
    return Move(Position{0,0},Position{0,0},nullptr, nullptr);
}