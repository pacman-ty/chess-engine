#include "controller.h"

void Controller::switchTurn() {
	if (turn == Color::White) {
		turn = Color::Black;
	} else {
		turn = Color::White;
	}
}

bool Controller::isCheckmate() {
	// TODO
}

bool Controller::isStalemate() {
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
	if (turn == Color::White) {

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
