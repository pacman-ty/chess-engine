#ifndef POSITION_H
#define POSITION_H

class Position {
private: 
    int x, y;
public:
    Position(int x, int y);
    int getX() const;
    int getY() const;
};

#endif
