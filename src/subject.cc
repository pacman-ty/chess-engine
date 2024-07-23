#include "subject.h"

void Subject::notifyAll() {
    for (auto o: observers) {
        o->notify();
    }
}

void Subject::subscribe(Observer* observer) {
    observers.push_back(observer);
}
void Subject::unsubscribe(Observer* observer) {
    for (auto it = observers.begin(); it != observers.end();) {
        if (observer == *it) {
            it = observers.erase(it);
        }
        else {
            ++it;
        }
    }
}