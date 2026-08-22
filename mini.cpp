#include<iostream>
#include<vector>
#include<map>
#include<climits>

using namespace std;

#include <random>

random_device rd;
mt19937 gen(rd());





/*
After each move go through all the possible moves.
these paths for all possible moves will each be assigned a number.
+10 for win
0 for draw
-10 for loss
and if win is after d moves the evaluation of 
that path will be +10 - d

if loss is there after d moves the evaluation of 
that path will be -10 + d

if draw then it is just 0

so required functions:
is_boards_full()
is_current_state_of_this_path_win()
is_current_state_of_this_path_loss()
evaluate_score for a path()

required structures 
a matrix to indicate the positions of the players
a tree to store the path for different choices of users.

after user makes each choice then for path lengths greater
than or equal to 3 we will check if the state of this path
is any of the termination states and if yes then we will 
not search further along the possibilites for that path

*/

map<int, vector<char>> paths;

map<int, char> boards = {
    {1, '1'},
    {2, '2'},
    {3, '3'},
    {4, '4'},
    {5, '5'},
    {6, '6'},
    {7, '7'},
    {8, '8'},
    {9, '9'}

};

void print_board(map<int, char> boards) {
    int count = 0;
    for (auto it: boards) {
        cout<<it.second<<"  ";
        count ++;
        if(count == 3) {
            count =0;
            cout<<endl;
        }
    }
}

vector<vector<int>> win = {
    {1, 2, 3},  // top row
    {4, 5, 6},  // middle row
    {7, 8, 9},  // bottom row

    {1, 4, 7},  // left column
    {2, 5, 8},  // middle column
    {3, 6, 9},  // right column

    {1, 5, 9},  // diagonal
    {3, 5, 7}   // diagonal
};

void player_x(int x) {
    for ( int i =1 ; i<=boards.size(); i++) {
       if(i == x ) {
            boards[i] ='x';
       }
    }
}

void player_o(int x) {
    for ( int i =1 ; i<=boards.size(); i++) {
       if(i == x ) {
            boards[i] ='o';
       }
    }
}

char is_win(map<int,char>& boards) {

    int count = 0;
    for (int i = 0; i < 8; i++) {
        int a = win[i][0];
        int b = win[i][1];
        int c = win[i][2];

        if (boards[a] == boards[b] &&
            boards[b] == boards[c] &&
            (boards[a] == 'x' || boards[a] == 'o'))
        {
            return boards[a];   // 'X' or 'O'
        }

        
    }

    for(int i = 1; i<=boards.size(); i++) {
        if(boards[i]=='x'|| boards[i]=='o') {
            count++;
        }
    }

    if(count==9) {
        return 'd';  
    } else {
        return '\0';
    }

    
}

vector<int> remaining(map<int, char>&boards) {
    vector<int> path;
    for (int i = 1 ; i <= boards.size(); i++) {
        if (boards[i] != 'x' && boards[i] != 'o') {
            path.push_back(i);
        }
    }

    return path;
}

struct result {
    int score;
    int index;
};



result minimax(map<int, char> boards, char player,int level) {

    char c = is_win(boards);
    if(c) {
        
        int score;
        if(c =='x') {
            score = -10 + level;
        } else if(c =='o') {
            score = 10 - level;
        } else {
            score = 0;
        }

        result r;
        r.score = score;
        r.index = -1;
        
        return r;
    }

    map<int, int> scores;

    for (int i : remaining(boards)) {
        boards[i] = player;

        char other_player = player == 'x' ? 'o' : 'x';

        result r = minimax(boards, other_player, level + 1);

        scores[i] = r.score;

        boards[i] = i + '0';

    }

// minimize the score for the player
    int score;
    int index;
    vector<int>bestMoves;

    if (player == 'x') {
        score = INT_MAX;
        index = -1;
        for(auto it : scores) {
            if(it.second < score) {
                score = it.second;
                index = it.first;
            }
        }

        for(auto it : scores) {
            if(it.second == score) {
                bestMoves.push_back(it.first);
            }
        }

        uniform_int_distribution<int> randomIndex(0, bestMoves.size() - 1);

        index = bestMoves[randomIndex(gen)];
    }

// maximize the score for the computer

    if (player == 'o') {
            score = INT_MIN;
            index = -1;
            for(auto it : scores) {
                if(it.second > score) {
                    score = it.second;
                    index = it.first;
                }
            }

            for(auto it : scores) {
                if(it.second == score) {
                    bestMoves.push_back(it.first);
                }
            }

            uniform_int_distribution<int> randomIndex(0, bestMoves.size() - 1);

            index = bestMoves[randomIndex(gen)];
        }

    result s;
    s.score = score;
    s.index = index;
    return s;

}

char play(char start, int pos) {

    char prev_move='x';
    if(start == 'c' || start == 'C') {
        player_o(pos);
    }

    if(start == 'p' || start == 'P') {
        player_x(pos);
    }

    if(start == 'c' || start == 'C') {
        prev_move = 'o';
    } else {
        prev_move = 'x';
    }

    int turn = 1;
    int level = 0;

    result best_score;

    for(int i = 1 ; i<9 ; i++) {

        vector<int> scores;

        if(is_win(boards)) {
            print_board(boards);
            return is_win(boards);
            
        }
        


        if(prev_move == 'x') {
            
            best_score = minimax(boards, 'o', level+1);
            player_o(best_score.index);

            cout<<"Computer turn : "<<best_score.index<<endl;
            


            level = level+1;
            prev_move = 'o';

        } else if(prev_move == 'o') {

            print_board(boards);
            cout<<"Your turn : "<<endl;
            cin>>turn;

            
            
            while(turn <1 || turn > 9 || boards[turn] == 'x' || boards[turn] =='o') {
                cout<<"Enter the position correctly."<<endl;
                cin>>turn;
            }
            player_x(turn);

            print_board(boards);
            level = level+1;
            prev_move ='x';
        }

        
    }

    return is_win(boards);
}







int main() {

    uniform_int_distribution<int> randomStart(1, 9);
    int firstMove = randomStart(gen);

    char winner = play('c', firstMove);

    if(winner == 'x') {
        cout<<"Players won";
    } else if(winner == 'o') {
        cout<<"Computer won";
    } else {
        cout<<"Draw happened";
    }

    
    return 0;
};

