#include <iostream>
#include <memory>
#include <string>
#include <map>

#include "controller.h"
#include "textview.h"
#include "windowview.h"
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


int main(int argc, char* argv[]) {
    std::shared_ptr<Board> board = std::make_shared<Board>();
    Controller controller{board.get()};
    Player *whitePlayer;
    Player *blackPlayer;
    vector<Observer *> obs;

    bool nogui = false;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-nogui") nogui = true;
    }
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

            // Game loop for computer players
            if (!whitePlayer && !blackPlayer) continue;
            while (true) {
                if (controller.getTurn() == Colour::WHITE) {
                    if (whitePlayer != nullptr) {
                        Move m = whitePlayer->move();
                        controller.move(m.getOldPosition(), m.getNewPosition(), nullptr);
                    }
                } else if (controller.getTurn() == Colour::BLACK) {
                    if (blackPlayer != nullptr) {
                        Move m = blackPlayer->move();
                        controller.move(m.getOldPosition(), m.getNewPosition(), nullptr);
                    }
                }
                if (controller.isStalemate()) { // Stalemate
                    cout << "Stalemate!" << endl;
                    controller.restartGame(); // Restart Game 
                    break;
                }
                else if (controller.isCheckmate()) {
                    controller.switchTurn();
                    cout << "Checkmate! " << controller.getTurn() << " wins!" << endl;
                    controller.addScore(controller.getTurn());
                    controller.restartGame();
                    break;
                }
                board->notifyAll();
                controller.switchTurn();
            }
        }
        else if (command == "resign") {
            controller.resign();
        }
        else if (command == "move") {
            Position oldPos, newPos;
            try { // Read in move from user
                cin >> oldPos >> newPos;
            } catch (std::invalid_argument & e) {
                cerr << "Move Error: " << e.what() << std::endl;
                continue;
            }
            try { // Attempts move
                controller.move(oldPos, newPos, nullptr);
            } catch (std::logic_error & e) {
                cerr << "Move Error: " << e.what() << std::endl;
                continue;
            }
            if (controller.isStalemate()) { // Stalemate
                cout << "Stalemate!" << endl;
                controller.restartGame(); // Restart Game 
                continue;    
            }
            else if (controller.isCheckmate()) { // Checkmate
                controller.switchTurn();
                cout << "Checkmate! " << controller.getTurn() << " wins!" << endl;
                controller.addScore(controller.getTurn());
                controller.restartGame(); // Restart Game
                continue;
            }
            board->notifyAll();
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
        } else if (command == "print") {
            board->notifyAll();
        } else {
            cerr << "Invalid command" << endl;
        }
    }

    controller.printScore();

    for (auto it : obs) {
        delete it;
    }

    delete whitePlayer;
    delete blackPlayer;
}
