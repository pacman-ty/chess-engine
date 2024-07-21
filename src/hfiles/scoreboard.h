#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <map>
#include "player.h"

class Scoreboard {
    std::map<Player *, int> tracker;
public:
    void addWin(Player * p);
};
#endif
