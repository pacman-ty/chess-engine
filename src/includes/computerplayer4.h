#ifndef COMPUTERPLAYER4_H
#define COMPUTERPLAYER4_H

#include "player.h"

class ComputerPlayer4 : public Player {
public:
    ComputerPlayer4(Colour, Board *);
    Move move() override;
};

#endif
