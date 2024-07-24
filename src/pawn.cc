#include "pawn.h"

Pawn::Pawn() : Piece{Type::PAWN} {}

// checks each direction the pawn can move not including captures and return a vector contain the moves
std::vector<Move> Pawn::getPossibleMoves(const Board::BoardType & b) const {
    std::vector<Move> out;
    int curX = currPosition.getX();
    int curY = currPosition.getY();
    int moveTo = 0;

    switch(side) {
        case Colour::BLACK:
            if (curY != BLACK_PAWN_START) hasMoved = true;

            if (!hasMoved && b[curX][curY - INITIAL_DASH] == nullptr){ // dbl. move
                out.emplace_back(currPosition, Position{curX, curY - INITIAL_DASH},
                                 this, nullptr);
            }

            moveTo = curY - 1;
            if (moveTo >= BOARD_MIN_HEIGHT && moveTo < BOARD_MAX_HEIGHT) {
                if (b[curX][moveTo] == nullptr) {
                    out.emplace_back(currPosition, Position{curX, moveTo}, this, nullptr);
                }
            }
            break;
        case Colour::WHITE:
            if (curY != WHITE_PAWN_START) hasMoved = true;

            if (!hasMoved && b[curX][curY + INITIAL_DASH] == nullptr){ // dbl. move
                out.emplace_back(currPosition, Position{curX, curY + INITIAL_DASH},
                                 this, nullptr);
            }

            moveTo = curY + 1;
            if (moveTo >= BOARD_MIN_HEIGHT && moveTo < BOARD_MAX_HEIGHT) {
                if (b[curX][moveTo] == nullptr) {
                    out.emplace_back(currPosition, Position{curX, moveTo}, this, nullptr);
                }
            }
            break;
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

    auto checkAndAddCapture = [&](int targetX, int targetY, Colour enemyColour) {
        if (targetX >= BOARD_MIN_WIDTH && targetX < BOARD_MAX_WIDTH && 
            targetY >= BOARD_MIN_HEIGHT && targetY < BOARD_MAX_HEIGHT && // Ensure targetY is within bounds
            b[targetX][targetY] != nullptr && 
            b[targetX][targetY]->getSide() == enemyColour) {
            out.emplace_back(currPosition, Position{targetX, targetY}, this, b[targetX][targetY]);
        }
    };

    switch (side) {
        case Colour::BLACK:
            checkAndAddCapture(leftCaptureX, curY - 1, Colour::WHITE);
            checkAndAddCapture(rightCaptureX, curY - 1, Colour::WHITE);
            break;
        case Colour::WHITE:
            checkAndAddCapture(leftCaptureX, curY + 1, Colour::BLACK);
            checkAndAddCapture(rightCaptureX, curY + 1, Colour::BLACK);
            break;
        default:
            std::cerr << "Invalid side (error initializing pawn)" << std::endl;
    }

    return out;
}
