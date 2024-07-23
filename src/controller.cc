#include "controller.h"
#include "pawn.h"

Controller::Controller(Board *b): board(b) {}

void Controller::initBoard() {
    // Pawn Placement
    for (int i = BOARD_MIN_WIDTH; i < BOARD_MAX_HEIGHT; ++i) {
        board->placePiece(Colour::WHITE, Type::PAWN, Position{i, WHITE_PAWN_START});
        board->placePiece(Colour::BLACK, Type::PAWN, Position{i, BLACK_PAWN_START});
    }
    // Rook Placement
    board->placePiece(Colour::WHITE, Type::ROOK, Position{0, BOARD_MIN_HEIGHT});
    board->placePiece(Colour::WHITE, Type::ROOK, Position{7, BOARD_MIN_HEIGHT});
    board->placePiece(Colour::BLACK, Type::ROOK, Position{0, BOARD_MAX_HEIGHT - 1});
    board->placePiece(Colour::BLACK, Type::ROOK, Position{7, BOARD_MAX_HEIGHT - 1});
    // Knight Placement
    board->placePiece(Colour::WHITE, Type::KNIGHT, Position{1, BOARD_MIN_HEIGHT});
    board->placePiece(Colour::WHITE, Type::KNIGHT, Position{6, BOARD_MIN_HEIGHT});
    board->placePiece(Colour::BLACK, Type::KNIGHT, Position{1, BOARD_MAX_HEIGHT - 1});
    board->placePiece(Colour::BLACK, Type::KNIGHT, Position{6, BOARD_MAX_HEIGHT - 1});
    // Bishop Placement
    board->placePiece(Colour::WHITE, Type::BISHOP, Position{2, BOARD_MIN_HEIGHT});
    board->placePiece(Colour::WHITE, Type::BISHOP, Position{5, BOARD_MIN_HEIGHT});
    board->placePiece(Colour::BLACK, Type::BISHOP, Position{2, BOARD_MAX_HEIGHT - 1});
    board->placePiece(Colour::BLACK, Type::BISHOP, Position{5, BOARD_MAX_HEIGHT - 1});
    // Queen Placement
    board->placePiece(Colour::WHITE, Type::QUEEN, Position{3, BOARD_MIN_HEIGHT});
    board->placePiece(Colour::BLACK, Type::QUEEN, Position{3, BOARD_MAX_HEIGHT - 1});
    // King Placement
    board->placePiece(Colour::WHITE, Type::KING, Position{4, BOARD_MIN_HEIGHT});
    board->placePiece(Colour::BLACK, Type::KING, Position{4, BOARD_MAX_HEIGHT - 1});
}

void Controller::switchTurn(Colour val) {
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

bool Controller::isStalemate() const {
    // TODO
}

void Controller::startGame(Player *whitePlayer, Player *blackPlayer) {
    delete whitePlayer;
    delete blackPlayer;

    this->whitePlayer = whitePlayer;
    this->blackPlayer = blackPlayer;
    
    initBoard();
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

bool Controller::inSetup() const {
    return setupMode;
}

void Controller::exitSetup() {
    setupMode = true;
}
