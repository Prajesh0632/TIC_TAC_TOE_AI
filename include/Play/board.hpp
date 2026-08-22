#pragma once

#include <SDL2/SDL.h>
#include <string>

class Button;
class Text;
class AI;

class Board{

    public:
      int x_pos, y_pos, width, height, game_type, mark_count = 0;
      char turn = 'X'; //O and X
      int player;
      int result = 0; // 0 = ongoing, 1 = X wins, 2 = O wins, 3 = draw


      SDL_Renderer* renderer;

      AI* player_ai;

      char prev_move = '-';
      int prev_r = -1, prev_c = -1;



      std::string board = "---------";
      Button* rect[9];
      Text* marker[9];

      Text* player_type = nullptr;



      Board(int, int, int, int, int, SDL_Renderer*);

      void init();

      void set_player_type();

      void draw();

      void move(int x = -1, int y = -1);

      void mark_board(int, int, char);

      void draw_marker();

      void get_player_move(int&, int&, char&, int, int);

      void eval_board();


      void reset();

      ~Board();




};
