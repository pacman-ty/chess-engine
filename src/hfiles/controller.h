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

    bool isCheckmate() const;
    bool isStalemate() const;

public:
    Controller(Board*);
    void startGame(Player *whitePlayer, Player *blackPlayer);
    void resign();
    void move(Move m, Piece *promotion);
    void switchTurn(Colour val = Colour::EMPTY);
    bool inSetup() const;
    void enterSetup();
    void exitSetup();
};

#endif

