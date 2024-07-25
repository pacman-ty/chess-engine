#ifndef COLOUR_H
#define COLOUR_H
#include <ostream>

enum class Colour {
    WHITE, BLACK, EMPTY
};
#endif

std::ostream& operator<<(std::ostream& out, const Colour& c);
