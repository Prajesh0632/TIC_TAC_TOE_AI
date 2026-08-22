#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "text.hpp"

class Button
{

public:
   std::string text;
   int x_pos, y_pos, width, height, fontSize;
   SDL_Rect rect;
   SDL_Renderer *mainRenderer;
   Text *txt;


   Button(std::string text, int x_pos, int y_pos, int width, int height, int size);

   void setRenderer(SDL_Renderer *renderer);

   void drawButton();

   bool isOnHover();

   bool checkPress();

   bool checkPress(int x, int y);
};
