    #include <iostream>
    #include "../../include/Play/ai.hpp"
    #include "../../include/Play/check_win.hpp"

    AI :: AI(char symbol) {
        
        this->symbol = symbol;
    } 



    void AI :: get_ai_move(int& r, int& c, char& mark, std::string board) {
    
    root = new Node();
    add_nodes(root, r, c, mark, symbol, board, 8);


    BestMove move = minimax(root, 8, symbol, true);
    r = move.row;
    c = move.col;
    mark = move.mark;

    }




    void make_move(int row, int col, char move, std::string& board) {

        board[row * 3 + col] = move;
    }

    void unmake_move(int row, int col, std::string& board) {

        board[row * 3 + col] = '-';

    }

    bool is_board_full(std::string& board) {


        int count = 0;
        for(int i = 0; i < 9; i++) {
            if(board[i] != '-')count++;
        }

        return (count == 9);

    }

Node* add_nodes(Node* node, int prev_r, int prev_col, char prev_move, char ai_move, std::string& board, int depth){




            node->prevMove = prev_move;
            node->prevRow = prev_r;
            node->prevCol = prev_col;
            node->_board = board;

        if (depth == 0 || is_board_full(board)) return node;
            



        for(int i = 0; i < 9; i++) {
            
            if(board[i] == '-') {

                int new_row = i / 3;
                int new_col = i % 3;
                char new_move;
                if (prev_move == '-') {
                new_move = ai_move; 
            }
            
            else {
                new_move = (prev_move == 'X') ? 'O' : 'X'; 
                
            }

             Node* child = new Node();

                make_move(new_row, new_col, new_move, board);
                add_nodes(child, new_row, new_col, new_move, ai_move, board, depth - 1);
                unmake_move(new_row, new_col, board);


                node->children.push_back(child);
        }
    }

        return node;
    
}

        

    
        



    
BestMove min(BestMove x, BestMove y) {

    return (x.score < y.score) ? x : y;
}    

BestMove max(BestMove x, BestMove y) {

    return (x.score > y.score) ? x : y;
}


int evaluate(int result, char ai_mark, int depth) {

    if((result == 1 && ai_mark == 'X') || (result == 2 && ai_mark == 'O')) return 100 + depth;
    if((result == 2 && ai_mark == 'X') || (result == 1 && ai_mark == 'O')) return -100 - depth;
    if((result == 3 && ai_mark == 'O') || (result == 3 && ai_mark == 'X')) return 0;
    return 0;
}


BestMove minimax(Node* root, int depth, char ai_mark, bool maximize) {


    if(depth == 0 || is_board_full(root->_board)) {
            
        int result = check_win(root->_board);
        BestMove best;
        best.score = evaluate(result, ai_mark, depth);
        best.row = root->prevRow;
        best.col = root->prevCol;
        best.mark = root->prevMove;


        return best;
        
        
        
        
    }

    
    if(maximize) {

        BestMove bestMax;
        bestMax.score = -inf;
        for(Node* node : root->children) {
            

            BestMove candidate = minimax(node, depth -1, ai_mark, false);
            candidate.row = node->prevRow;
            candidate.col = node->prevCol;
            candidate.mark = node->prevMove;

            bestMax = max(bestMax, candidate);


        }

        return bestMax;

    }


    else {

        BestMove bestMin;
        bestMin.score = inf;
        for(Node* node : root->children) {



            BestMove candidate = minimax(node, depth -1, ai_mark, true);
            candidate.row = node->prevRow;
            candidate.col = node->prevCol;
            candidate.mark = node->prevMove;

            bestMin = min(bestMin, candidate);

        }

        return bestMin;


    }


}  