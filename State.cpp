#include "State.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;


State::State(vector< vector<string> > board) {
    this->board = board;
    this->manhatten = CalculateManhattenDistance(board);
}


int State::CalculateManhattenDistance(vector< vector<string> > &board){
    
    for (int i = 0; i < board.size(); i++){
        for (int j = 0; j < board[i].size(); j++){
            
        }
    }
    
    return 1;
    
}
