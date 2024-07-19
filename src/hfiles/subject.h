#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

class Observer;

class Subject {
    std::vector<Observer*> observers;
protected:
    void notify();
public:
    void subscribe(Observer*);
    void unsubscribe(Observer*);
};

#endif
