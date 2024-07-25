#include "computerplayer1.h"

ComputerPlayer1::ComputerPlayer1(Colour colour, Board *board) : Player(colour, board) {}

Move ComputerPlayer1::move() {
    return Move(Position{0,0},Position{0,0},nullptr, nullptr);
}
