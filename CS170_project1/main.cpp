
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
    
    // Total possible moves are 4
    
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
    
    
}



// A utility function to count inversions in given array 'arr[]'
int getInvCount(int arr[])
{
    int inv_count = 0;
    for (int i = 0; i < 9 - 1; i++)
        for (int j = i+1; j < 9; j++) {
            cout << arr[i] << ", " << arr[j] ;
            // Value 0 is used for empty space
            if (arr[j] && arr[i] && arr[i] > arr[j]) {
                inv_count++;
                cout << ", " << "inv";
            }
            cout << endl;
        }
    return inv_count;
}


// This function returns true if given 8 puzzle is solvable.
bool isSolvable(int puzzle[3][3])
{
    // Count inversions in given 8 puzzle
    int invCount = getInvCount((int *)puzzle);
    
    // return true if inversion count is even.
    return (invCount%2 == 0);
}


int main(){
    
    int max=1;
    int expanded=0;
    
    string row;
    vector<string> tempVec;
    vector< vector<string> > board;
    priority_queue<State,vector<State>, CompareState > activeQueue;
    map< string , bool> visitedMap;
    
    
    cout << "Enter your puzzle, use a zero to represent the blank" << endl;
    cout << "Enter the first row,   use space or tabs between numbers\t";
    getline(cin, row);
    tempVec = split( row , ' ');
    board.push_back(tempVec);
    
    cout << "Enter the second row,  use space or tabs between numbers\t";
    getline(cin, row);
    tempVec = split( row , ' ');
    board.push_back(tempVec);
    
    cout << "Enter the third row,   use space or tabs between numbers\t";
    getline(cin, row);
    tempVec = split( row , ' ');
    board.push_back(tempVec);
    
    cout << "0. Uniform Cost Search\n1. Manhatten Heuristic\n2. Misplaced Tile Heuristic\n";
    int algo;
    cin >> algo;
    
    
    
    State state(board, 0, algo);
    //state.printBoard();

    // Push roote state
    activeQueue.push(state);

    while (true) {
        
        // If queue is empty
        if (activeQueue.empty()) {
            cout << "Active Queue is Empty" << endl;
            break;
        }
        
        // Top off best state from queue
        State state = activeQueue.top();
        cout << "State Popped:" << endl;
        state.printStateInfo();
        state.printBoard();
        visitedMap[state.getString()] = true;
        cout << "*********************" << endl << endl;

        // If this new state is the goal state, then exit
        if(state.isGoalState()){
            
            cout << "Goal State Found!!!" << endl;
            cout << endl << "To solve this problem the search algorithm expanded a total of " << expanded << " Nodes." << endl;
            cout << "The maximum number of nodes in the queue at any one time was " << max << endl;
            
            break;
        }
        
        // Remove new state form active list
        activeQueue.pop();
        expanded++;
        
        // Calculate All possible next states
        GenerateAllPossibleMoves(state,activeQueue, visitedMap, algo, max);
        

    }
    
    
    return 0;
    
}
