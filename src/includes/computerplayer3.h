#ifndef COMPUTERPLAYER3_H
#define COMPUTERPLAYER3_H
#include "player.h"

class ComputerPlayer3 : public Player {
public:
    ComputerPlayer3(Colour, Board *);
    Move move() override;
};

#endif
