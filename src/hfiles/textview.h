#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include "observer.h"

class TextView : public Observer {
    virtual void update();
};

#endif
