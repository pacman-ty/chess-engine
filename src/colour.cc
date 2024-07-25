#include "colour.h"

std::ostream& operator<<(std::ostream& out, const Colour& c) {
    switch(c) {
        case Colour::WHITE:
            out << "White";
            break;
        case Colour::BLACK:
            out << "Black";
            break;
        case Colour::EMPTY:
            out << "Empty";
            break;
    }
    return out;
}