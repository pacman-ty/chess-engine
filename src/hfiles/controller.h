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
    bool isCheckmate() const;
    bool isStalemate() const;

public:
    void startGame(Player *whitePlayer, Player *blackPlayer);
    void resign();
    void move(Move m, Piece *promotion);
    void enterSetup();
    void exitSetup();
};

#endif

