#ifndef COMPUTERPLAYER2_H
#define COMPUTERPLAYER2_H
#include "player.h"

class ComputerPlayer2 : public Player {
public:
    ComputerPlayer2(Colour, Board *);
    Move move() override;
};

#endif
