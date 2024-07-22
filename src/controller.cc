#include "controller.h"

void Controller::switchTurn(Colour val = Colour::EMPTY) {
    if (val != Colour::EMPTY) {
        turn = val;
        return;
    }

    if (turn == Colour::BLACK) {
        turn = Colour::WHITE;
    } else {
        turn = Colour::BLACK;
    }
}

bool Controller::isCheckmate() const {
    // TODO
}

bool Controller::isStalemate() const {
    // TODO
}

void Controller::startGame(Player *whitePlayer, Player *blackPlayer) {
    delete whitePlayer;
    delete blackPlayer;

    this->whitePlayer = whitePlayer;
    this->blackPlayer = blackPlayer;
}

void Controller::resign() {
    // TODO
    if (turn == Colour::WHITE) {

    } else {

    }
}

void Controller::move(Move m, Piece *promotion) {
    // TODO
}

bool Controller::isCheckmate() const {
    return setupMode;
}

void Controller::enterSetup() {
    delete board;
    setupMode = true;
}

void Controller::exitSetup() {
    setupMode = true;
}
