#ifndef TEXTVIEW_H
#define TEXTVIEW_H



class TextView : public Observer {
public:
    virtual void notify();
    TextView(Board*);
};

#endif
