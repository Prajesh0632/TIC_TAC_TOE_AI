#include <string>
#include <vector>

#define inf 10e7

struct Node{
    
    int prevRow;
    int prevCol;
    char prevMove;
    int type;
    std::string _board;
    std::vector<Node*> children;
    

};

struct BestMove {
    int row, col;
    char mark;
    int score;
};

Node* add_nodes(Node*, int, int, char, char, std::string&, int);
BestMove minimax(Node*, int, char, bool);

class AI {

    public:

    char symbol;

    Node* root = nullptr;

    AI(char);


    void get_ai_move(int&, int&, char&, std::string);


};