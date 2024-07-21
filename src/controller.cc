#include "controller.h"

void Controller::switchTurn() {
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

void Controller::enterSetup() {
    setupMode = true;
}

void Controller::exitSetup() {
    setupMode = true;
}
