#include <iostream>
#include <string>

#include "controller.h"
#include "observer.h"
#include "board.h"

using namespace std;

int main() {;
    std::shared_ptr<Board> board = std::make_shared<Board>();
    Controller controller{board.get()};

    // Interpret user commands
    string command;
    while (cin >> command) {
        if (controller.inSetup()) {
            if (command == "+") {
                char piece;
                Position pos;
                Type t;
                Colour c;
                cin >> piece >> pos;
                switch (piece) {
                    case 'K': t = Type::KING; c = Colour::WHITE;
                    case 'Q': t = Type::QUEEN; c = Colour::WHITE;
                    case 'R': t = Type::ROOK; c = Colour::WHITE;
                    case 'B': t = Type::BISHOP; c = Colour::WHITE;
                    case 'N': t = Type::KNIGHT; c = Colour::WHITE;
                    case 'P': t = Type::PAWN; c = Colour::WHITE;
                    case 'k': t = Type::KING; c = Colour::BLACK;
                    case 'q': t = Type::QUEEN; c = Colour::BLACK;
                    case 'r': t = Type::ROOK; c = Colour::BLACK;
                    case 'b': t = Type::BISHOP; c = Colour::BLACK;
                    case 'n': t = Type::KNIGHT; c = Colour::BLACK;
                    case 'p': t = Type::PAWN; c = Colour::BLACK;
                }
                board->placePiece(c, t, pos);
            }
            else if (command == "-") {
                Position p;
                cin >> p;
                board->removePiece(p);
            }
            else if (command == "=") {
                string side;
                cin >> side;
                if (side == "white") {
                    controller.switchTurn(Colour::WHITE);
                }
                else if (side == "black") {
                    controller.switchTurn(Colour::BLACK);
                }
            }
            else if (command == "done") {
                controller.exitSetup();
            }
            continue;
        }
        if (command == "game") {
            Player* white;
            Player* black;

            controller.startGame(white, black);
        }
        else if (command == "resign") {
            controller.resign();
        }
        else if (command == "move") { 
            Position oldPos, newPos;
            cin >> oldPos >> newPos;
            board->playMove(oldPos, newPos);
        }
        else if (command == "setup") {
            controller.enterSetup();
        }
        else if (command == "done") {
            return 0;
        }
    }
}
