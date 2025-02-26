#include "textview.h"
#include "board.h"
#include "piece.h"

TextView::TextView(Board *b): Observer(b) {}

void TextView::notify() {
    for (int y = BOARD_MAX_HEIGHT-1; y >= 0; --y) {
        std::cout << y + 1 << " ";
        for (int x = 0; x < BOARD_MAX_WIDTH; ++x) {
            const Piece *piece = subject->getItem(x, y);
            if (piece == nullptr) {
                std::cout << (((x+y)%2 == 0) ? '_' : ' ');
            } else {
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
                std::cout << out;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "  abcdefgh" << std::endl;
}