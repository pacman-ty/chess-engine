#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;

class Observer {
    Subject* subject;
public:
    virtual void update() = 0;
};

#endif
