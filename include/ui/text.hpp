#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Text
{

private:
   TTF_Font *font;
   SDL_Surface *textSurface;
   SDL_Texture *textTexture;
   int width, height, x_pos, y_pos, fontSize;
   SDL_Rect textRect;
   std::string text;
   char cText[100];
   SDL_Renderer *mainRenderer;

public:
   Text(int w, int h, int x, int y, std::string txt, int size);

   void initializeText(SDL_Renderer *renderer, SDL_Color color);

   void displayText();
};
