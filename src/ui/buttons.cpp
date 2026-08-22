#include "../../include/ui/buttons.hpp"

Button::Button(std::string text, int x_pos, int y_pos, int width, int height, int size)
{
   this->text = text;
   this->x_pos = x_pos;
   this->y_pos = y_pos;
   this->height = height;
   this->width = width;
   this->fontSize = size;
   this->rect = {this->x_pos, this->y_pos, this->width, this->height};
   this->txt = new Text(this->width, this->height, this->x_pos, this->y_pos, this->text, this->fontSize);
}

void Button::setRenderer(SDL_Renderer *renderer)
{
   this->mainRenderer = renderer;
   this->txt->initializeText(renderer, {255, 255, 255, 255});
}

void Button::drawButton()
{

   SDL_SetRenderDrawColor(this->mainRenderer, 255, 255, 255, 0);
   SDL_RenderDrawRect(this->mainRenderer, &this->rect);

   this->txt->displayText();

   if (isOnHover())
   {
      this->txt->initializeText(this->mainRenderer, {0, 255, 0, 255});
   }
   else
   {
      this->txt->initializeText(this->mainRenderer, {255, 255, 255, 255});
   }
}

bool Button::isOnHover()
{

   int x, y;
   SDL_GetMouseState(&x, &y);

   if ((x >= this->x_pos && x <= this->x_pos + this->width) && (y >= this->y_pos && y <= this->y_pos + this->height))
   {
      return true;
   }
   return false;
}

bool Button::checkPress()
{

   if (this->isOnHover())
   {

      return true;
   }

   return false;
}

bool Button::checkPress(int x, int y)
{

   if ((x >= this->x_pos && x <= this->x_pos + this->width) && (y >= this->y_pos && y <= this->y_pos + this->height))
   {
      return true;
   }

   return false;
}
