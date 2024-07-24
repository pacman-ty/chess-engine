#ifndef COMPUTERPLAYER1_H
#define COMPUTERPLAYER1_H
#include "player.h"

class ComputerPlayer1 : public Player {
public:
    ComputerPlayer1(Colour, Board *);
    Move move() override;
};

#endif
