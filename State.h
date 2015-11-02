#ifndef ____State__
#define ____State__
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class State {
    
private:
    // F, G, H
    int priority, moves, manhatten;
    
    // Current Board State
    vector< vector<string> > board;
    
    // Function: Calculates Manhatten Distance of current board
    int CalculateManhattenDistance(vector< vector<string> > &board);
    
public:
    
    State( vector< vector<string> > board );
    
};




#endif /* defined(____State__) */
