#include <iostream>
#include <memory>
#include <string>

#include "controller.h"
#include "textview.h"
#include "windowview.h"
#include "position.h"
#include "computerplayer1.h"
#include "computerplayer2.h"
#include "computerplayer3.h"
#include "computerplayer4.h"
#include "computerplayer5.h"

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
    else if (name == "computer5") {
        return new ComputerPlayer5(c, b);
    }
    else {
        throw std::invalid_argument("Invalid player type");
    }
}


int main(int argc, char* argv[]) {
    std::shared_ptr<Board> board = std::make_shared<Board>();
    Controller controller{board.get()};
    Player *whitePlayer = nullptr;
    Player *blackPlayer = nullptr;
    vector<Observer *> obs;

    bool nogui = false;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-nogui") nogui = true;
    }

    /* Display Observers */
    Observer* text = new TextView(board.get());
    obs.push_back(text);
    board.get()->subscribe(text);
    if (!nogui) {
        Observer* window = new WindowView(board.get());
        obs.push_back(window);
        board.get()->subscribe(window);
    }

    board->notifyAll();

    // Interpret user commands
    string command;
    while (cin >> command) {
        // - Setup Mode Start -
        if (controller.inSetup()) {
            if (command == "+") { // + <Piece> <Location>
                char piece;
                Position pos;
                Type t;
                Colour c;

                try { // Read in piece and position
                    cin >> piece >> pos;
                } catch (std::invalid_argument & e) {
                    std::cerr << "Setup Error: " << e.what() << std::endl;
                    continue;
                }

                switch (piece) { // piece selection decider
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

                try { // Attempt to place piece on board
                    board->placePiece(c, t, pos);
                } catch (std::invalid_argument & e) {
                    std::cerr << "Setup Error: " << e.what() << std::endl;
                    continue;
                } catch (std::logic_error & e) {
                    std::cerr << "Setup Error: " << e.what() << std::endl;
                    continue;
                }
                board->notifyAll(); // Display board to user
            }
            else if (command == "-") { // - <Location>
                Position p;
                cin >> p; // Read in location
                try { // Attempt to remove piece from board
                    board->removePiece(p);
                } catch (std::invalid_argument & e) {
                    std::cerr << "Setup Error: " << e.what() << std::endl;
                    continue;
                } catch (std::logic_error & e) {
                    std::cerr << "Setup Error: " << e.what() << std::endl;
                    continue;
                }
                board->notifyAll(); // Display Board to user
            }
            else if (command == "=") { // = <Colour>
                string side;
                cin >> side; // Read in side
                if (side == "white" || side == "WHITE") {
                    controller.switchTurn(Colour::WHITE);
                }
                else if (side == "black" || side == "BLACK") {
                    controller.switchTurn(Colour::BLACK);
                } else {
                    cerr << "Invalid side" << endl;
                    continue;
                }
                cout << "Side switched to " << controller.getTurn() << endl;
            }
            else if (command == "done") {
                cout << "Exiting setup mode" << endl;
                controller.exitSetup();
            } else {
                cerr << "Invalid setup command" << endl;
            }
            continue;
        } // - Setup Mode End -
        if (command == "game") {
            if (whitePlayer) delete whitePlayer;
            if (blackPlayer) delete blackPlayer;
            string white, black;
            cin >> white >> black; // read in types of players

            try { // attempt to create whitePlayer
                whitePlayer = createPlayer(white, Colour::WHITE, board.get());
            } catch (std::invalid_argument & e) {
                std::cerr << "White Player Error: " << e.what() << std::endl;
                continue;
            }

            try { // attempt to create blackPlayer
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
            Player *currPlayer = controller.getTurn() == Colour::WHITE ? whitePlayer : blackPlayer;
            if (currPlayer) { // if current player is AI
                Move m = currPlayer->move();
                oldPos = m.getOldPosition();
                newPos = m.getNewPosition();
            } else {
                try { // Read in move from user
                    cin >> oldPos >> newPos;
                } catch (std::invalid_argument & e) {
                    cerr << "Move Error: " << e.what() << std::endl;
                    continue;
                }
            }
            try { // Attempts move
                controller.move(oldPos, newPos);
            } catch (std::logic_error & e) {
                cerr << "Move Error: " << e.what() << std::endl;
                continue;
            }
        }
        else if (command == "setup") {
            /* Available Commands */
            cout << "Entering setup mode:" << endl;
            cout << "Available Commands:" << endl;
            cout << "+ <Piece> <Location> [Insert Piece]" << endl;
            cout << "- <Location> [Remove Piece]" << endl;
            cout << "= <Colour> [Swap Sides]" << endl;
            cout << "done [Exit Setup]" << endl;
            controller.enterSetup();
        }
        else if (command == "done") {
            return 0;
        }
        else if (command == "print") {
            board->notifyAll();
        }
        else if (command == "cvc") {
            // Computer VS Computer
            if (whitePlayer && blackPlayer) {
                while (true) {
                    if (controller.getGameState()) break; // toggles game done state and escapes loop
                    if (controller.getTurn() == Colour::WHITE) {
                        if (whitePlayer != nullptr) {
                            Move m = whitePlayer->move();
                            // create move from AI
                            controller.move(m.getOldPosition(), m.getNewPosition());
                        }
                    } else if (controller.getTurn() == Colour::BLACK) {
                        if (blackPlayer != nullptr) {
                            Move m = blackPlayer->move();
                            // create move from AI
                            controller.move(m.getOldPosition(), m.getNewPosition());
                        }
                    }
                }
            }
            else {
                cout << "Both players aren't computer" << endl;
            }
        }
        else {
            cerr << "Invalid command" << endl;
        }
    }

    // Print scoreboard when reaching EOF
    controller.printScore();

    // Freeing used heap memory
    for (auto it : obs) {
        delete it;
    }

    delete whitePlayer;
    delete blackPlayer;
}
