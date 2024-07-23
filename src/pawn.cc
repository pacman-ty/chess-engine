#include "pawn.h"

Pawn::Pawn() : Piece{Type::PAWN} {}

// checks each direction the pawn can move not including captures and return a vector contain the moves
std::vector<Move> Pawn::getPossibleMoves(const Board::BoardType & b) const {
    std::vector<Move> out;
    int curX = currPosition.getX();
    int curY = currPosition.getY();

    switch(side) {
        case Colour::BLACK:
            if (curY != BLACK_PAWN_START) hasMoved = true;

            if (!hasMoved && b[curX][curY - INITIAL_DASH] == nullptr){ // dbl. move
                out.emplace_back(currPosition, Position{curX, curY - INITIAL_DASH},
                                 this, nullptr);
            }

            for (int i = curY; i >= BOARD_MIN_HEIGHT; --i) {
                if (b[curX][i] != nullptr) break;
                out.emplace_back(currPosition, Position{curX, i}, this, nullptr);
            }
        case Colour::WHITE:
            if (curY != WHITE_PAWN_START) hasMoved = true;

            if (!hasMoved && b[curX][curY + INITIAL_DASH] == nullptr){ // dbl. move
                out.emplace_back(currPosition, Position{curX, curY + INITIAL_DASH},
                                 this, nullptr);
            }

            for (int i = curY; i < BOARD_MAX_HEIGHT; ++i) {
                if (b[curX][i] != nullptr) break;
                out.emplace_back(currPosition, Position{curX, i}, this, nullptr);
            }
        default:
            std::cerr << "Invalid side (error initializing pawn)" << std::endl;
    }

    return out;
}

// checks each direction the pawn can move in and sees if it captures anything and returns a vector containing the captures
std::vector<Move> Pawn::getPossibleCaptures(const Board::BoardType & b) const {
    std::vector<Move> out;
    int curX = currPosition.getX();
    int curY = currPosition.getY();
    int leftCaptureX = curX - 1;
    int rightCaptureX = curX + 1;   

    switch(side) {
        case Colour::BLACK:
            if (leftCaptureX >= BOARD_MIN_HEIGHT && leftCaptureX < BOARD_MAX_HEIGHT) {
                if (b[leftCaptureX][curY - 1] != nullptr &&
                    b[leftCaptureX][curY - 1]->getSide() == Colour::WHITE) {
                        out.emplace_back(currPosition, Position{leftCaptureX, curY - 1},
                                            this, b[leftCaptureX][curY - 1]);
                    }
            }

            if (rightCaptureX >= BOARD_MIN_HEIGHT && rightCaptureX < BOARD_MAX_HEIGHT) {
                if (b[rightCaptureX][curY - 1] != nullptr &&
                    b[rightCaptureX][curY - 1]->getSide() == Colour::WHITE) {
                        out.emplace_back(currPosition, Position{rightCaptureX, curY - 1},
                                            this, b[rightCaptureX][curY - 1]);
                    }
            }
        case Colour::WHITE:
            if (leftCaptureX >= BOARD_MIN_HEIGHT && leftCaptureX < BOARD_MAX_HEIGHT) {
                if (b[leftCaptureX][curY + 1] != nullptr &&
                    b[leftCaptureX][curY + 1]->getSide() == Colour::WHITE) {
                        out.emplace_back(currPosition, Position{leftCaptureX, curY - 1},
                                            this, b[leftCaptureX][curY - 1]);
                    }
            }
            
            if (rightCaptureX >= BOARD_MIN_HEIGHT && rightCaptureX < BOARD_MAX_HEIGHT) {
                if (b[rightCaptureX][curY + 1] != nullptr &&
                    b[rightCaptureX][curY + 1]->getSide() == Colour::WHITE) {
                        out.emplace_back(currPosition, Position{rightCaptureX, curY - 1},
                                            this, b[rightCaptureX][curY - 1]);
                    }
            }
        default:
            std::cerr << "Invalid side (error initializing pawn)" << std::endl;
    }

    return out;
}
