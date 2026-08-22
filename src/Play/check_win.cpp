#include "../../include/Play/check_win.hpp"

int check_win(std::string board) {

    int lines[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    for(int i = 0; i < 8; i++) {
        char a = board[lines[i][0]];
        char b = board[lines[i][1]];
        char c = board[lines[i][2]];

        if(a != '-' && a == b && b == c) {
            return (a == 'X') ? 1 : 2;
        }
    }

    for(int i = 0; i < 9; i++) {
        if(board[i] == '-') return 0;
    }

    return 3;
}