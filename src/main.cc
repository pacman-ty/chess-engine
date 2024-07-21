#include <iostream>
#include <string>

#include "controller.h"
#include "observer.h"
#include "board.h"

using namespace std;

Position readPosition() {
    Position p;
    char rank;
    cin >> rank;
    p.x = rank - 'a'; // Use value difference to translate a-f to 0-7

    cin >> p.y;
    --p.y; // Given position is 1-8, translate to 0-7
    return p;
}

int main() {;
    Board* board = new Board;
    Controller* controller{board};

    // Interpret user commands
    string commmand;
    while (cin >> command) {
        if (controller.inSetup()) {
            if (command == "+") {
                Position p = readPosition();
            }
            else if (command == "-") {
            }
            else if (command == "=") {
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
            Position oldPos = readPosition();
            Position newPos = readPosition();

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
