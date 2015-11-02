#ifndef ____State__
#define ____State__
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class State {
    
private:
    // Variable: F, G, H
    int priority, moves, manhatten;
    
    // Variable: Current Board State
    vector< vector<string> > board;
    
    // Function: Calculates Manhatten Distance of current board
    int CalculateManhattenDistance(vector< vector<string> > &board);
    
    // Function: Calculates current tile position distance from goal tile position
    int DistanceToGoal(int x, int y);
    
public:
    
    // Constructor
    State( vector< vector<string> > board, int moves );
    
    // Prints the full board
    void printBoard();
    
    // Prints state info
    void printStateInfo();
    
};




#endif /* defined(____State__) */
