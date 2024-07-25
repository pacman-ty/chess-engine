#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <map>
#include <ostream>
#include "colour.h"

class Scoreboard {
    std::map<Colour, int> scoreboard;
public:
    Scoreboard();
    void addWin(Colour c);
    int getWin(Colour c) const;
};

std::ostream& operator<<(std::ostream& out, const Scoreboard& s);
#endif
