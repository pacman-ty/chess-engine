#ifndef OBSERVER_H
#define OBSERVER_H

class Board;

class Observer {
protected:
    Board* subject;
    Observer(Board*);
public:
    virtual void notify() = 0;
};

#endif
