#include "../../include/ui/dialogBox.hpp"

Dialog::Dialog(int w, int h, int x, int y)
{

   this->width = w;
   this->height = h;
   this->x_pos = x;
   this->y_pos = y;
   this->txt = new Text(this->width, this->height / 4, this->x_pos + 20, this->y_pos + (height / 3), " Do you want to exit the game?", 20);

   this->rect = {this->x_pos, this->y_pos, this->width, this->height};

   this->btn1 = new Button("YES", this->x_pos + 80, this->y_pos + (height / 2) + 20, 100, 50, 25);
   this->btn2 = new Button("NO", this->x_pos + 240, this->y_pos + (height / 2) + 20, 100, 50, 25);

   this->onDisplay = 0;
}

Dialog::~Dialog()
{
   delete btn1;
   delete btn2;
}

void Dialog::displayDialog(SDL_Renderer *renderer)
{

   SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
   SDL_RenderFillRect(renderer, &this->rect);

   this->txt->initializeText(renderer, {255, 255, 255, 255});

   this->txt->displayText();

   this->btn1->setRenderer(renderer);
   this->btn2->setRenderer(renderer);
   this->btn1->drawButton();
   this->btn2->drawButton();
}

int Dialog::checkClick()
{

   if (this->btn1->checkPress() && this->onDisplay == 1)
   {

      return 1;
   }

   if (this->btn2->checkPress() && this->onDisplay == 1)
   {

      return 2;
   }

   return 0;
}
