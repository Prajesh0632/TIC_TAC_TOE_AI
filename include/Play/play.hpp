#pragma once

#include <SDL2/SDL.h>

class Dialog;
class Button;
class Board;
class Text;


class Play
{

public:
  Dialog *dialog;
  Button *btn;
  Board* board;

  SDL_Renderer *mainRenderer;
  int type;

public:
  Play(SDL_Renderer *renderer, int typ);

  ~Play();

  void display();

  int checkClick(int x, int y);
};
