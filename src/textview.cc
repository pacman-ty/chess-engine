#include "textview.h"
#include "board.h" // for constants
#include "type.h" // for constants
#include <iostream>

void TextView::notify() {
    bool dark = false;
    for (int y = BOARD_MAX_HEIGHT-1; y >= 0; --y) {
        std::cout << y << " " << std::endl;
        for (int x = 0; x < BOARD_MAX_WIDTH; ++x) {
            const Piece *piece = subject->getItem(x, y);
            if (piece == nullptr) {
                std::cout << (dark ? "_" : " ") << std::endl;
            } else {
                std::cout << *piece << std::endl;
            }
            dark = !dark; // next square will be the opposite of current
        }
    }
}