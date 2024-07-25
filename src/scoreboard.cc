#include "scoreboard.h"

Scoreboard::Scoreboard() {
    scoreboard[Colour::WHITE] = 0;
    scoreboard[Colour::BLACK] = 0;
}

void Scoreboard::addWin(Colour c) {
    scoreboard[c]++;
}

int Scoreboard::getWin(Colour c) const {
    auto find = scoreboard.find(c);
    if (find != scoreboard.end()) {
        return find->second;
    }
    return 0;
}

std::ostream& operator<<(std::ostream& out, const Scoreboard& s) {
    out << "Final Score:" << std::endl;
    out << "White: " << s.getWin(Colour::WHITE) << std::endl;
    out << "Black: " << s.getWin(Colour::BLACK) << std::endl;
    return out;
}
