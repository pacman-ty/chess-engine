#include "player.h"

Player::Player(Colour colour, Board *board) : side(colour), board(board) {}

bool Player::isLegalMove(Move m) {
    bool isLegal = false;
    try {
        board->isValidMove(m);
        isLegal = true;
    } catch (std::logic_error &e) {
        isLegal = false;
    } catch (std::invalid_argument &e) {
        isLegal = false;
    }
    return isLegal;
}
