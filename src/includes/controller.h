#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "board.h"
#include "scoreboard.h"

class Player;

const int WHITE_Y = BOARD_MIN_HEIGHT;
const int BLACK_Y = BOARD_MAX_HEIGHT - 1;
const int L_ROOK = 0;
const int L_KNIGHT = 1;
const int L_BISHOP = 2;
const int QUEEN_X = 3;
const int KING_X = 4;
const int R_BISHOP = 5;
const int R_KNIGHT = 6;
const int R_ROOK = 7;

class Controller {
    bool setupMode;
    Colour turn;
    Board* board;
    Scoreboard *scoreboard;
    Player *whitePlayer;
    Player *blackPlayer;

    // initBoard() places all pieces in standard order on board
    void initBoard();

public:
    Controller(Board *);
    void startGame(Player *whitePlayer, Player *blackPlayer);
    void resign();
    void move(Position oP, Position nP, Piece *promotion);
    void switchTurn(Colour val = Colour::EMPTY);
    bool inSetup() const;
    void enterSetup();
    void exitSetup();
    Colour getTurn() const;
    bool isCheckmate() const;
    bool isStalemate() const;
    bool isCheck() const;
};

#endif

