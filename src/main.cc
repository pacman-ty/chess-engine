#include <iostream>
#include <memory>
#include <string>
#include <map>

#include "controller.h"
#include "textview.h"
#include "position.h"
#include "computerplayer1.h"
#include "computerplayer2.h"
#include "computerplayer3.h"
#include "computerplayer4.h"

using namespace std;


Player* createPlayer(string name, Colour c, Board * b) {
    if (name == "human") { 
        return nullptr;
    }
    else if (name == "computer1") {
        return new ComputerPlayer1(c, b);
    }
    else if (name == "computer2") {
        return new ComputerPlayer2(c, b);
    }
    else if (name == "computer3") {
        return new ComputerPlayer3(c, b);
    }
    else if (name == "computer4") {
        return new ComputerPlayer4(c, b);
    }
    else {
        throw std::invalid_argument("Invalid player type");
    }
}

int main() {
    std::shared_ptr<Board> board = std::make_shared<Board>();
    Controller controller{board.get()};
    Player *whitePlayer;
    Player *blackPlayer;
    map<Colour, int> scoreboard;

    board.get()->subscribe(new TextView(board.get()));

    // Interpret user commands
    string command;
    while (cin >> command) {
        if (controller.inSetup()) {
            if (command == "+") {
                char piece;
                Position pos;
                Type t;
                Colour c;
                try {
                    cin >> piece >> pos;
                } catch (std::invalid_argument & e) {
                    std::cerr << "Setup Error: " << e.what() << std::endl;
                    continue;
                }
                switch (piece) {
                    case 'K': t = Type::KING; c = Colour::WHITE; break;
                    case 'Q': t = Type::QUEEN; c = Colour::WHITE; break;
                    case 'R': t = Type::ROOK; c = Colour::WHITE; break;
                    case 'B': t = Type::BISHOP; c = Colour::WHITE; break;
                    case 'N': t = Type::KNIGHT; c = Colour::WHITE; break;
                    case 'P': t = Type::PAWN; c = Colour::WHITE; break;
                    case 'k': t = Type::KING; c = Colour::BLACK; break;
                    case 'q': t = Type::QUEEN; c = Colour::BLACK; break;
                    case 'r': t = Type::ROOK; c = Colour::BLACK; break;
                    case 'b': t = Type::BISHOP; c = Colour::BLACK; break;
                    case 'n': t = Type::KNIGHT; c = Colour::BLACK; break;
                    case 'p': t = Type::PAWN; c = Colour::BLACK; break;
                }
                try {
                    board->placePiece(c, t, pos);
                } catch (std::invalid_argument & e) {
                    std::cerr << "Setup Error: " << e.what() << std::endl;
                    continue;
                }
                
            }
            else if (command == "-") {
                Position p;
                cin >> p;
                try {
                    board->removePiece(p);
                } catch (std::invalid_argument & e) {
                    std::cerr << "Setup Error: " << e.what() << std::endl;
                    continue;
                }
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
            } else {
                cerr << "Invalid setup command" << endl;
            }
            continue;
        }
        if (command == "game") {

            string white, black;
            cin >> white >> black;

            try {
                whitePlayer = createPlayer(white, Colour::WHITE, board.get());
            } catch (std::invalid_argument & e) {
                std::cerr << "White Player Error: " << e.what() << std::endl;
                continue;
            }

            try {
                blackPlayer = createPlayer(black, Colour::BLACK, board.get());
            } catch (std::invalid_argument & e) {
                std::cerr << "Black Player Error: " << e.what() << std::endl;
                continue;
            }

            controller.startGame(whitePlayer, blackPlayer);
            board->notifyAll();
        }
        else if (command == "resign") {
            controller.resign();
        }
        else if (command == "move") {
            Position oldPos, newPos;
            try {
                cin >> oldPos >> newPos;
            } catch (std::invalid_argument & e) {
                cerr << "Move Error: " << e.what() << std::endl;
                continue;
            }
            try { 
                controller.move(oldPos, newPos, nullptr);
            } catch (std::logic_error & e) {
                cerr << "Move Error: " << e.what() << std::endl;
                continue;
            }
            if (controller.isCheckmate()) { // checkmate
                cout << controller.colourToString(controller.getTurn()) << " is in checkmate." << endl;
                cout << "Restarting Game ..." << endl;
                controller.switchTurn();
                scoreboard[controller.getTurn()]++; // increment score
                controller.restartGame(); // restart game
                continue;
            }
            board->notifyAll();
        }
        else if (command == "setup") {
            controller.enterSetup();
        }
        else if (command == "done") {
            return 0;
        } else if (command == "print") {
            board->notifyAll();
        } else {
            cerr << "Invalid command" << endl;
        }
    }

    cout << "Final Score:" << endl;
    cout << "White: " << scoreboard[Colour::WHITE] << endl;
    cout << "Black: " << scoreboard[Colour::BLACK] << endl;

    delete whitePlayer;
    delete blackPlayer;
}
