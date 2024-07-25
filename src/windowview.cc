#include "windowview.h"
#include "board.h"
#include "piece.h"
#include <string>
#include <iostream>
using namespace std;

WindowView::WindowView(Board *board): Observer{board} { }

void WindowView::notify() {
    window.fillRectangle(0, 0, 8, 8, 1);
    for (int y = BOARD_MAX_HEIGHT-1; y >= 0; --y) {
        for (int x = 0; x < BOARD_MAX_WIDTH; ++x) {
            int colour = ((x+y) % 2 == 0) ? Xwindow::White : Xwindow::Black;
            window.fillRectangle(x*64, y*64, 64, 64, colour);
            const Piece *piece = subject->getItem(x, y);
            if (piece == nullptr) {
                continue;
            }
            char out;
            switch (piece->getType())
            {
            case Type::KING:
                out = 'K';
                break;
            case Type::QUEEN:
                out = 'Q';
                break;
            case Type::BISHOP:
                out = 'B';
                break;
            case Type::ROOK:
                out = 'R';
                break;
            case Type::KNIGHT:
                out = 'N';
                break;
            case Type::PAWN:
                out = 'P';
                break;
            default:
                break;
            }
            if (piece->getSide() == Colour::BLACK) {
                out += 'a' - 'A'; // convert to lowercase 
            }
            //window.drawString(x*8, y*8, std::string{out});
        }
    }
}