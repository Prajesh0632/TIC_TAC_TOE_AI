#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "buttons.hpp"

class Menu
{

private:
   Button butn1{"Play", 330, 100, 300, 80, 40},
       butn2{"Play AI", 330, 280, 300, 80, 40},
       butn3{"Settings", 330, 460, 300, 80, 40},
       butn4{"Exit", 330, 640, 300, 80, 40};

   std::vector<Button> butns = {butn1, butn2, butn3, butn4};

   SDL_Surface *image;
   SDL_Texture *texture;
   SDL_Renderer *mainRenderer;

public:
   Menu(SDL_Renderer *renderer);

   void display();

   int checkStateChange();
};
