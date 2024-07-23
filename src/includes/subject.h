#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "observer.h"

class Subject {
    std::vector<Observer*> observers;
protected:
    void notifyAll();
public:
    void subscribe(Observer*);
    void unsubscribe(Observer*);
};

#endif