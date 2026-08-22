#include "../../include/Play/board.hpp"
#include "../../include/ui/buttons.hpp"
#include "../../include/Play/ai.hpp"
#include "../../include/Play/check_win.hpp"

#include <iostream>


Board::Board(int x_pos, int y_pos, int width, int height, int type, SDL_Renderer* renderer) {

this->x_pos = x_pos;
this->y_pos = y_pos;
this->width = width;
this->height = height;
this->game_type = type;
this->renderer = renderer;
this->turn = 'X';
this->player = rand() % 2;




set_player_type();


init();

}


void Board::init() {

    int row = 3, col = 3;

    int x = x_pos;
    int y = y_pos;

    for(int i = 0; i < row; i++) {

        for(int j = 0; j < col; j++) {

            rect[i * col + j] = new Button("",x, y, width, height, 25);
            rect[i * col + j]->setRenderer(renderer);



            x += width;
        }

        x = x_pos;
        y += height;
    }
}


void Board::set_player_type() {

    std::string player_1, player_2;
    if(game_type == 1) {
        char ai_mark;


        if(player == 1) {
            player_1 = "Human(X)";
            player_2 = "AI(O)";
            ai_mark = 'O';

        }
        else {
            player_1 = "AI(X)";
            player_2 = "Human(O)";
            ai_mark = 'X';
        }

        player_ai = new AI(ai_mark);
    }
    else {
        player_1 = "Human(X)";
        player_2 = "Human(O)";
    }

    std::string players = "Player 1 : " + player_1 + "   Player 2 : " + player_2;

    delete player_type;
    player_type = new Text(40, 40, 400, 30, players, 20);
    player_type->initializeText(renderer, {255, 255, 0});
}


void Board::draw() {

    for(int i = 0; i < 3; i++) {

        for(int j = 0; j < 3; j++) {


            rect[i * 3 + j]->drawButton();



        }
    }

    draw_marker();


    this->player_type->displayText();

    eval_board();



}


void Board::move(int x, int y) {

    if(result != 0) return;

    SDL_RenderPresent(renderer);


    // game_type (0) is AI vs Human
    //player 0 is always AI
    //player 1 is always Human
     int r = prev_r, c = prev_c;
     char mark = prev_move;
    if(game_type == 1 && player == 0) {


       if(player_ai) {

        player_ai->get_ai_move(r, c, mark, board);

       }
       SDL_Delay(500);


    }

    else {

        get_player_move(r, c, mark, x, y);


    }

    if(r != -1 && c != -1 && mark != '-') {
        
        prev_move = mark;
        prev_r = r;
        prev_c = c;
        mark_board(r, c, mark);

    }

}

void Board :: get_player_move(int& r, int& c, char& mark, int x, int y) {

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(rect[i * 3 + j]->checkPress(x, y) && board[i * 3 + j] == '-') {

                r = i;
                c = j;
                mark = turn;
                return;

            }
        }
    }

    r = -1;
    c = -1;
    mark = '-';
}

void Board :: mark_board(int r, int c, char mark) {

    board[r * 3 + c] = mark;
    marker[r * 3 + c] = new Text(100, 100, rect[r * 3 + c]->x_pos + 50, rect[r * 3 + c]->y_pos - 10, std::string(1, mark), 150);
    marker[r * 3 + c]->initializeText(renderer,{255, 0, 0, 0});


    if(turn == 'X') turn = 'O';
    else turn = 'X';

    if(player == 0) player = 1;
    else player = 0;


    result = check_win(board);

}

void Board :: draw_marker() {

    for(int i = 0; i < 9; i++) {

        if(board[i] != '-') {
            marker[i]->displayText();
        }
    }

}

void Board :: eval_board() {

    Text* result_render = nullptr;

    int status_x = x_pos;
    int status_y = y_pos + 3 * height + 20;

    if(result == 1) {
        result_render = new Text(3 * width, 40, status_x, status_y, "Player X wins", 50);
     }
    else if(result == 2) {
        result_render = new Text(3 * width, 40, status_x, status_y, "Player O wins", 50);
    }

    else if(result == 3) {
        result_render = new Text(3 * width, 40, status_x, status_y, "Draw", 50);
    }
    else {
        std::string current_status = std::string("Current Turn : ") + turn;
        result_render = new Text(3 * width, 40, status_x, status_y, current_status, 50);
    }

    result_render->initializeText(renderer, {255,0,0,0});
    result_render->displayText();

    delete result_render;
}




void Board :: reset() {

    for(int i = 0; i < 9; i++) {
        if(board[i] != '-') {
            delete marker[i];
            marker[i] = nullptr;
        }
    }

    board = "---------";
    turn = 'X';
    mark_count = 0;
    result = 0;
    player = rand() % 2;
    set_player_type();

}




Board :: ~Board() {

    for(int i = 0; i < 9; i++) {
        delete rect[i];
    }

    delete player_type;

}
