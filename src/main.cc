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
                char type;
                Position p;
                cin >> type >> p;
                board->placePiece(type, p);
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
            Position oldPos;
            Position newPos;
            cin >> oldPos >> newPos;

            controller.move(Move{oldPos, newPos});
        }
        else if (command == "setup") {
            controller.enterSetup();
        }
        else if (command == "done") {
            return 0;
        }
    }
}
