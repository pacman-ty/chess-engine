#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include "type.h"
#include "colour.h"

class Xwindow {
  Display *d;
  Window w;
  int s, width, height;
  GC gc;
  unsigned long colours[5];

 public:
  Xwindow(int width=512, int height=512);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.

  enum {White=0, Black, Red, Green, Blue}; // Available colours.

  int getWidth() const;
  int getHeight() const;

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg);

  void drawPiece(int x, int y, Type type, Colour color);

};

#endif
