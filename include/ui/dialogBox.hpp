#pragma once

#include <SDL2/SDL.h>
#include "buttons.hpp"
#include "text.hpp"

class Dialog
{

private:
   int width, height, x_pos, y_pos;
   Text *txt;
   Button *btn1, *btn2;
   SDL_Rect rect, rect1, rect2;

public:
   int onDisplay;

   Dialog(int w, int h, int x, int y);

   ~Dialog();

   void displayDialog(SDL_Renderer *renderer);

   int checkClick();
};
