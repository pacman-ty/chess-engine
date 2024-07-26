#include "controller.h"
#include "pawn.h"
// Implementation of Controller class

Controller::Controller(Board *b): setupMode{false},
    done{false}, turn{Colour::WHITE}, board{b} {}

void Controller::initBoard() {

    try {
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
    } catch (std::logic_error & e) {
        std::cerr << "Error during init: " << e.what() << std::endl;
    }
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
    std::cout << "===============" << std::endl;
    std::cout << getTurn() << "'s turn:" << std::endl;
}

bool Controller::isStalemate() const {
    return board->isStalemate(turn);
}

void Controller::startGame(Player *whitePlayer, Player *blackPlayer) {
    done = false;
    board->clear();
    this->whitePlayer = whitePlayer;
    this->blackPlayer = blackPlayer;
    switchTurn(Colour::WHITE);
    initBoard();
}

void Controller::resign() {
    switch (turn) {
        case Colour::BLACK:
            std::cout << "White wins!" << std::endl;
            addScore(Colour::WHITE);
            break;
        case Colour::WHITE:
            std::cout << "Black wins!" << std::endl;
            addScore(Colour::BLACK);
            break;  
        default:
            throw std::invalid_argument("Invalid Colour");      
    }
}

void Controller::restartGame() {
    board->notifyAll();
    board->clear();
    switchTurn(Colour::WHITE);
    startGame(whitePlayer, blackPlayer);
}

void Controller::move(Position oldPos, Position newPos) {
    board->playMove(oldPos, newPos, turn);
    board->notifyAll(); // Display board
    if (board->checkPawnPromotion(newPos.getX(), newPos.getY())) {
        if (turn == Colour::WHITE) {
            if (whitePlayer) { // if AI
                board->promote(newPos.getX(), newPos.getY(), Type::QUEEN);
            } else { // if player
                board->promptPawnPromotion(newPos.getX(), newPos.getY());
            }
        } else if (turn == Colour::BLACK) {
            if (blackPlayer) { // if AI
                board->promote(newPos.getX(), newPos.getY(), Type::QUEEN);
            } else { // if player
                board->promptPawnPromotion(newPos.getX(), newPos.getY());
            }
        }
        board->notifyAll();
    }
    switchTurn();
    if (isCheck()) { // in check but not checkmate
        std::cout << getTurn() << " is in check." << std::endl;
    }
    if (isStalemate()) { // Stalemate
        std::cout << "Stalemate!" << std::endl;
        restartGame(); // Restart Game   
        done = true; 
    }
    else if (isCheckmate()) { // Checkmate
        switchTurn();
        std::cout << "Checkmate! " << getTurn() << " wins!" << std::endl;
        addScore(getTurn());
        restartGame(); // Restart Game
        done = true;
    }
    else if (board->isInsufficientMaterial()) {
        std::cout << "Insufficient Material!" << std::endl;
        restartGame();
        done = true;
    }
}

bool Controller::isCheckmate() const {
    return board->isCheckmate(turn);
}

void Controller::setBoard(Board * b) {
    board = b;
}

void Controller::enterSetup() {
    setupMode = true;
}

bool Controller::getGameState() const {
    return done;
}

bool Controller::inSetup() const {
    return setupMode;
}

void Controller::exitSetup() {
    setupMode = false;
}

Colour Controller::getTurn() const {
    return turn;
}

bool Controller::isCheck() const {
    return board->isCheck(turn);
}

void Controller::addScore(Colour c) {
    scoreboard.addWin(c);
}

void Controller::printScore() const {
    std::cout << scoreboard;
}