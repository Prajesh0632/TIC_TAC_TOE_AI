#include "../../include/ui/buttons.hpp"
#include "../../include/ui/dialogBox.hpp"
#include "../../include/ui/text.hpp"
#include "../../include/Play/play.hpp"
#include "../../include/Play/board.hpp"

#include <iostream>

Play::Play(SDL_Renderer *renderer, int typ)
{

  std::cout << typ << " type " << std::endl;

  this->type = typ;

  this->dialog = new Dialog(400, 200, 300, 300);
  this->btn = new Button("Back", 20, 20, 100, 50, 25);
   
  this->board = new Board(100, 100, 200, 200, type, renderer);

  this->mainRenderer = renderer;


  this->btn->setRenderer(this->mainRenderer);
}

Play::~Play()
{
  delete dialog;
  delete btn;
  delete board;
  std::cout << "destrucot" << std::endl;
}

void Play::display()
{


  this->btn->drawButton();

  this->board->draw();

  if(type == 1 && this->board->player == 0) this->board->move();



  if (this->dialog->onDisplay)
  {
    this->dialog->displayDialog(this->mainRenderer);
  }
}

int Play::checkClick(int x, int y)
{

  if (this->btn->checkPress(x, y))
  {
    std::cout << "Pressed";
    this->dialog->onDisplay = 1;
  }

  if(type == 0 || this->board->player == 1) this->board->move(x, y);


  int a = this->dialog->checkClick();

  if (a != 0)
  {
    this->dialog->onDisplay = 0;
  }

  if (a == 1)
  {
    board->reset();
    return 0;

  }

  else
  {
    return type + 1;
  }
}
