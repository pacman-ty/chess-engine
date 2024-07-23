#include "board.h"

Board::Board() {
    std::memset(board, 0, sizeof(board));
}

Board::~Board() {
    for (auto p : whitePieces) {
        delete p;
    }
    for (auto p : blackPieces) {
        delete p;
    }
}

void Board::placePiece(Colour side, Type t, const Position & pos) {
    if (!board[pos.getX()][pos.getY()]) {
        std::cerr << "Invalid placement (Slot taken)" << std::endl;
        return;
    }
    Piece* toAdd;
    switch (t) {
        case Type::KING: toAdd = new King();
        case Type::QUEEN: toAdd = new Queen();
        case Type::ROOK: toAdd = new Rook();
        case Type::BISHOP: toAdd = new Bishop();
        case Type::KNIGHT: toAdd = new King();
        case Type::PAWN: toAdd = new King();
        default:
            std::cerr << "Invalid type" << std::endl;
            return;
    }
    toAdd->setSide(side);
    toAdd->setPos(pos);
    switch (side) {
        case Colour::BLACK: blackPieces.push_back(toAdd);
        case Colour::WHITE: whitePieces.push_back(toAdd);
        default:
            std::cerr << "Invalid Side" << std::endl;
            return;
    }
    // Add to the board
    board[pos.getX()][pos.getY()] = toAdd;
}

void Board::removePiece(Position p) {
    delete board[p.getX()][p.getY()];
    board[p.getX()][p.getY()] = nullptr; 
}

void Board::playMove(const Move & m) {
    if (!isValidMove(m)) {
        std::cerr << "invalid move" << std::endl;
        return;
    }
    int x = m.getOldPosition().getX();
    int y = m.getOldPosition().getY();
    int newX = m.getNewPosition().getX();
    int newY = m.getNewPosition().getY();    
    if (m.getCapture()) { // has a target
        delete board[newX][newY]; // delete captured piece
        board[newX][newY] = board[x][y]; // move target piece
        board[x][y] = nullptr;                    
    } else { // no target
        board[newX][newY] = board[x][y]; // move target piece
        board[x][y] = nullptr;
    }
}

void Board::playMove(Position oldPos, Position newPos) {
    delete board[newPos.getX()][newPos.getY()];
    board[newPos.getX()][newPos.getY()] = board[oldPos.getX()][oldPos.getY()];
}

void Board::cloneBoard(const Board & b) {
    for (int y = BOARD_MIN_HEIGHT; y < BOARD_MAX_HEIGHT; ++y) {
        for (int x = BOARD_MIN_WIDTH; x < BOARD_MAX_WIDTH; ++x) {
            const Piece* curItem = b.getItem(x, y);
            placePiece(curItem->getSide(), curItem->getType(), curItem->getPos());     
        }
    }
}

bool Board::isValidMove(const Move & m) const {
    // check if you can go there
    bool found = false;
    for (auto p : m.getTarget()->getPossibleMoves(board)) {
        if (p.getNewPosition() == m.getNewPosition()) {
            found = true;
            break;
        }
    }
    if (!found) return false;
    // simulate move
    std::unique_ptr<Board> temp_board{new Board};
    temp_board->cloneBoard(*this);
    temp_board->playMove(m);
    // check simulated move is valid
    return temp_board->isCheck(m.getTarget()->getSide());
}

bool Board::isCheck(Colour side) const {
    switch(side) {
        case Colour::BLACK:
            for (auto p : whitePieces) { // check opposing pieces
                for (auto cap : p->getPossibleCaptures(board)) {
                    if (cap.getCapture()->getType() == Type::KING) return false;
                }
            }
        case Colour::WHITE:
            for (auto p : blackPieces) {
                for (auto cap : p->getPossibleCaptures(board)) {
                    if (cap.getCapture()->getType() == Type::KING) return false;
                }
            }
        default:
            std::cerr << "Invalid Colour" << std::endl;
            return false;
    }
    return true;
}

const Board::BoardType& Board::getBoard() const {
    return board;
}

const Piece* Board::getItem(int x, int y) const {
    return board[x][y];
}


