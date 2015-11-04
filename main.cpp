
#include <iostream>
#include <queue>
#include <map>
#include "State.h"


// Helper Function to put split results in a premade vector
vector<string> &split(const string &s, char delim, vector<string> &myVec) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        myVec.push_back(item);
    }
    return myVec;
}

// Helper Function to return results as a new vector
vector<string> split(const string &s, char delim) {
    vector<string> myVec;
    split(s, delim, myVec);
    return myVec;
}

// Compare State Struct to create Minimum Priority Que
struct CompareState : public binary_function<State, State, bool>
{
    bool operator()( const State lhs, const State rhs) const
    {
        return lhs.getPriority() > rhs.getPriority();
    }
};


void GenerateAllPossibleMoves( State state, priority_queue<State,vector<State>, CompareState > &activeQueue,map< string , bool> &visitedMap, int algo, int &max){
    
    int blankX = state.getBlankX();
    int blankY = state.getBlankY();
    vector<State*> states;
    
    
    //cout << "Children ===========" << endl;
    
    // Move Left, if possible
    if((blankY - 1) >= 0){
        vector< vector<string> > newBoard = state.getBoard();
        iter_swap(newBoard[blankX].begin() + blankY, newBoard[blankX].begin() + (blankY-1));
        State newState( &state, newBoard, state.getMoves()+1 , algo);
        
        if( visitedMap[newState.getString()] == false){
            activeQueue.push(newState);
            //newState.printBoard();
            //newState.printStateInfo();
        }
        
    }
    
    // Move Right, if possible
    if((blankY + 1) < 3){
        vector< vector<string> > newBoard = state.getBoard();
        iter_swap(newBoard[blankX].begin() + blankY, newBoard[blankX].begin() + (blankY+1));
        State newState ( &state, newBoard, state.getMoves()+1, algo );
        if( visitedMap[newState.getString()] == false){
            activeQueue.push(newState);
            //newState.printBoard();
            //newState.printStateInfo();
        }

    }
    
    // Move Top, if possible
    if((blankX - 1) >= 0){
        vector< vector<string> > newBoard = state.getBoard();
        iter_swap(newBoard[blankX].begin() + blankY, newBoard[blankX-1].begin() + (blankY));
        State newState( &state, newBoard, state.getMoves()+1, algo );
        if( visitedMap[newState.getString()] == false){
            activeQueue.push(newState);
            //newState.printBoard();
            //newState.printStateInfo();
        }

    }
    
    // Move Bottom, if possible
    if((blankX + 1) < 3){
       
        vector< vector<string> > newBoard = state.getBoard();
        iter_swap(newBoard[blankX].begin() + blankY, newBoard[blankX+1].begin() + (blankY));
        State newState( &state, newBoard, state.getMoves()+1, algo );
        if( visitedMap[newState.getString()] == false){
            activeQueue.push(newState);
            //newState.printBoard();
            //newState.printStateInfo();
        }
        
        if(activeQueue.size() >= max)
            max = activeQueue.size();
    }
    
    //cout << "====================" << endl;
    
    
}

int main(){
    
    int max=1;
    
    string row;
    vector<string> tempVec;
    vector< vector<string> > board;
    priority_queue<State,vector<State>, CompareState > activeQueue;
    map< string , bool> visitedMap;
    
    
    tempVec.push_back("0");
    tempVec.push_back("1");
    tempVec.push_back("3");
    board.push_back(tempVec);
    
    tempVec.clear();
    tempVec.push_back("4");
    tempVec.push_back("2");
    tempVec.push_back("5");
    board.push_back(tempVec);
    
    tempVec.clear();
    tempVec.push_back("7");
    tempVec.push_back("8");
    tempVec.push_back("6");
    board.push_back(tempVec);
    
    
    /*
    cout << "Enter your puzzle, use a zero to represent the blank" << endl;
    cout << "Enter the first row,   use space or tabs between numbers\t";
    getline(cin, row);
    tempVec =  split( row , ' ');
    board.push_back(tempVec);
    
    cout << "Enter the second row,  use space or tabs between numbers\t";
    getline(cin, row);
    tempVec = split( row , ' ');
    board.push_back(tempVec);
    
    cout << "Enter the third row,   use space or tabs between numbers\t";
    getline(cin, row);
    tempVec =  split( row , ' ');
    board.push_back(tempVec);
    */
    cout << "0. Uniform Cost Search\n1. Manhatten Heuristic\n2. Misplaced Tile Heuristic\n";
    int algo;
    cin >> algo;
    
    
    State state(board, 0, algo);

    activeQueue.push(state);

    while (true) {
        
        if (activeQueue.empty()) {
            cout << "Active Queue is Empty" << endl;
            break;
        }
        
        // Top off best state from queue
        State state = activeQueue.top();
        cout << "State Popped:" << endl;
        state.printBoard();
        state.printStateInfo();
        visitedMap[state.getString()] = true;
        cout << "*********************" << endl << endl;

        // If this new state is the goal state, then exit
        //cout << "Check If Goal State" << endl;
        if(state.isGoalState()){
            
            cout << "Goal State Found!!!" << endl;
            state.printBoard();
            state.printStateInfo();
            
            cout << endl << "Max Queue Size: " << max << endl;
            break;
        }
        
        // Remove new state form active list
        activeQueue.pop();
        
        // Calculate All possible next states
        //cout << "Generate Children" << endl;
        GenerateAllPossibleMoves(state,activeQueue, visitedMap, algo, max);
        
    
            // Pick Lowest new priority compared previous removed state, and add to queue
    }
    
    
    return 0;
    
}
