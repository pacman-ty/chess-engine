#ifndef COMPUTERPLAYER5_H
#define COMPUTERPLAYER5_H

#include "player.h"

class ComputerPlayer5 : public Player {
public:
    ComputerPlayer5(Colour, Board *);
    Move move() override;
};

#endif
