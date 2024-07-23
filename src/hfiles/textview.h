#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include "observer.h"

class TextView : public Observer {
public:
    virtual void notify();
    TextView(Board*);
};

#endif
