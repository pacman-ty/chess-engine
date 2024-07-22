#ifndef POSITION_H
#define POSITION_H

#include <iostream>

class Position {
private: 
    int x, y;
public:
    Position();
    Position(int x, int y);
    int getX() const;
    int getY() const;

    friend istream& operator>>(istream& cin, Position rhs);
};

#endif
