#include "../../include/ui/text.hpp"
#include <cstring>

Text::Text(int w, int h, int x, int y, std::string txt, int size)
{

   this->width = w;
   this->height = h;
   this->x_pos = x;
   this->y_pos = y + (this->height) / 4;
   this->text = txt;
   this->fontSize = size;
   this->font = TTF_OpenFont("assets/font.ttf", this->fontSize);

   std::strcpy(this->cText, this->text.c_str());
}

void Text::initializeText(SDL_Renderer *renderer, SDL_Color color)
{

   this->mainRenderer = renderer;
   this->textSurface = TTF_RenderText_Blended(this->font, this->cText, color);
   this->textTexture = SDL_CreateTextureFromSurface(this->mainRenderer, this->textSurface);
   SDL_FreeSurface(this->textSurface);

   SDL_QueryTexture(this->textTexture, NULL, NULL, &this->width, &this->height);
   this->textRect = {this->x_pos, this->y_pos, this->width, this->height};
}

void Text::displayText()
{

   SDL_RenderCopy(this->mainRenderer, this->textTexture, NULL, &this->textRect);
}
