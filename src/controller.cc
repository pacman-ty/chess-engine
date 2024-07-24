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
    board->placePiece(Colour::WHITE, Type::ROOK, Position{L_ROOK, WHITE_Y});
    board->placePiece(Colour::WHITE, Type::ROOK, Position{R_ROOK, WHITE_Y});
    board->placePiece(Colour::BLACK, Type::ROOK, Position{L_ROOK, BLACK_Y});
    board->placePiece(Colour::BLACK, Type::ROOK, Position{R_ROOK, BLACK_Y});
    // Knight Placement
    board->placePiece(Colour::WHITE, Type::KNIGHT, Position{L_KNIGHT, WHITE_Y});
    board->placePiece(Colour::WHITE, Type::KNIGHT, Position{R_KNIGHT, WHITE_Y});
    board->placePiece(Colour::BLACK, Type::KNIGHT, Position{L_KNIGHT, BLACK_Y});
    board->placePiece(Colour::BLACK, Type::KNIGHT, Position{R_KNIGHT, BLACK_Y});
    // Bishop Placement
    board->placePiece(Colour::WHITE, Type::BISHOP, Position{L_BISHOP, WHITE_Y});
    board->placePiece(Colour::WHITE, Type::BISHOP, Position{R_BISHOP, WHITE_Y});
    board->placePiece(Colour::BLACK, Type::BISHOP, Position{L_BISHOP, BLACK_Y});
    board->placePiece(Colour::BLACK, Type::BISHOP, Position{R_BISHOP, BLACK_Y});
    // Queen Placement
    board->placePiece(Colour::WHITE, Type::QUEEN, Position{QUEEN_X, WHITE_Y});
    board->placePiece(Colour::BLACK, Type::QUEEN, Position{QUEEN_X, BLACK_Y});
    // King Placement
    board->placePiece(Colour::WHITE, Type::KING, Position{KING_X, WHITE_Y});
    board->placePiece(Colour::BLACK, Type::KING, Position{KING_X, BLACK_Y});
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
    setupMode = true;
}

bool Controller::inSetup() const {
    return setupMode;
}

void Controller::exitSetup() {
    setupMode = false;
}
