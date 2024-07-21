#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "board.h"
#include "scoreboard.h"

class Controller {
    bool setupMode;
    Colour turn;
    Board* board;
    Scoreboard *scoreboard;
    Player *whitePlayer;
    Player *blackPlayer;

    void switchTurn();
    bool isCheckmate();
    bool isStalemate();

public:
<<<<<<< HEAD
    void startGame(Player *whitePlayer, Player *blackPlayer);
    void resign();
    void move(Move m, Piece *promotion);
    void enterSetup();
    void exitSetup();
=======
	void startGame(Player *whitePlayer, Player *blackPlayer);
	void resign();
	void move(Move m, Piece *promotion);
	void enterSetup();
	void exitSetup();
>>>>>>> 0f19ad2 (Added more methods to various classes and wrote rook.cc)
};

#endif

