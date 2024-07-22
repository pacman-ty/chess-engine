#ifndef POSITION_H
#define POSITION_H

#include <iostream>

class Position {
private: 
    int x = 0, y = 0;
public:
    Position();
    Position(int x, int y);
    int getX() const;
    int getY() const;
    void setX(int val);
    void setY(int val);
    bool operator==(const Position rhs) const;
};

std::istream& operator>>(std::istream& cin, Position& rhs);

#endif
