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
    int priority, moves, manhatten, misplaced;

    // Locatoin of blank space
    int blankX, blankY;
    
    // Type of algorithm 0 Uniform, 1 Manhatten, 2 Misplaced
    int algo;
    
    // Parent State
    State* parent;
    
    // Variable: Current Board State
    vector< vector<string> > board;
    
    // Function: Calculates Manhatten Distance of current board
    int CalculateManhattenDistance(vector< vector<string> > &board);
    
    // Function: Calculates Misplaced Tile of current board
    int CalculateMisplacedTile(vector< vector<string> > &board);
    
    // Function: Calculates current tile position distance from goal tile position
    int DistanceToGoal(int x, int y);
    
    // Function: Initializes variables
    void initialize(int algo, int moves);
    
public:
    
    // Constructor
    State(State* parent, vector< vector<string> > board, int moves, int algo);
    
    // Constructor
    State( vector< vector<string> > board, int moves, int algo );
    
    vector<State*> GenerateAllPossibleMoves();
    
    // Checks if we reached goal state
    bool isGoalState();
    
    // Returns Priority value
    const int getPriority() const;
    
    // Returns Parent State value
    State* getParent();
    
    int getBlankX();
    
    int getBlankY();
    
    int getMoves();
    
    vector< vector<string> > getBoard();
    
    string getString();
    
    // Prints the full board
    void printBoard();
    
    // Prints state info
    void printStateInfo();
    
    friend bool operator==(const State& lhs, const State& rhs);
    friend bool operator!=(const State& lhs, const State& rhs);
    State& operator=(State rhs);

};




#endif /* defined(____State__) */
