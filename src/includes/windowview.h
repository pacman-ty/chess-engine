#ifndef WINDOWVIEW_H
#define WINDOWVIEW_H

#include "observer.h"
#include "window.h"

class Board;

class WindowView : public Observer {
    Xwindow window;
public:
    virtual void notify();
    WindowView(Board*);
};

#endif