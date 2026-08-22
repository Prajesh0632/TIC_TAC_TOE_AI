#include "../../include/ui/menu.hpp"
#include <iostream>

Menu::Menu(SDL_Renderer *renderer)
{

   this->mainRenderer = renderer;
   this->image = IMG_Load("assets/menuBackground.jpg");
   if (this->image)
   {
      this->texture = SDL_CreateTextureFromSurface(renderer, image);
      SDL_FreeSurface(this->image);
   }
   else
   {
      this->texture = nullptr;
   }

   for (auto i = butns.begin(); i != butns.end(); i++)
   {
      i->setRenderer(this->mainRenderer);
   }
}

void Menu::display()
{

   if (this->texture)
   {

      SDL_RenderCopy(this->mainRenderer, this->texture, NULL, NULL);
   }

   for (auto i = butns.begin(); i != butns.end(); i++)
   {
      i->drawButton();
   }
}

int Menu::checkStateChange()
{

   int count = 0;
   for (auto i = butns.begin(); i != butns.end(); i++)
   {
      if (i->checkPress())
      {

         std::cout << "Button " << count + 1 << " is pressed" << std::endl;

         return (count + 1);
      }

      count++;
   }

   return 0;
}
