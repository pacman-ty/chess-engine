#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include "observer.h"

class Board;

class TextView : public Observer {
public:
    virtual void notify();
    TextView(Board*);
};

#endif
