
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
struct CompareState : public binary_function<State*, State*, bool>
{
    bool operator()( const State* lhs, const State* rhs) const
    {
        return lhs->getPriority() > rhs->getPriority();
    }
};


int main(){
    
    string row;
    vector<string> tempVec;
    vector< vector<string> > board;
    priority_queue<State*,vector<State*>, CompareState > activeQueue;
    map< pair<int,int> , bool> visitedMap;
    
    tempVec.clear();
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
    
    
    State state(board, 0);
    state.printBoard();
    state.printStateInfo();
    
    activeQueue.push(&state);
    
    
    
    while (true) {
        if (activeQueue.empty()) {
            cout << "Active Queue is now Empty" << endl;
            break;
        }
        
        // Top off best state from queue
        State* state(activeQueue.top());
        cout << "State Topped: *******" << endl;
        state->printBoard();
        cout << "*********************" << endl;

        // If this new state is the goal state, then exit
        cout << "Check If Goal State" << endl;
        if(state->isGoalState()){
            cout << "Goal State Found!!!" << endl;
            state->printBoard();
            state->printStateInfo();
            break;
        }
        
        // Remove new state form active list
        activeQueue.pop();
        
        // Calculate All possible next states
        cout << "Generate Children" << endl;
        vector<State*> moves = state->GenerateAllPossibleMoves();
        
        for (int i = 0; i < moves.size(); i++) {
            cout << "Checking Parent " << i << endl;
            
            if(state->getParent() != NULL){
                // Check new state is not the previous one
                cout << "Checking Child " << i << endl;
                if(moves[i] != state->getParent()){
            
                    cout << "Going to Push: " << endl;
                    moves[i]->printBoard();
                    activeQueue.push((moves[i]));
                    cout << "Push Succussfull: " << endl;
                    State* state(activeQueue.top());
                    cout << "State Pushed: #######" << endl;
                    state->printBoard();
                    state->printStateInfo();
                    cout << "#####################" << endl;
                
                }
            }
            
        }
            // Pick Lowest new priority compared previous removed state, and add to queue


    }
        
        
    
    
    
    
    /*
    board.clear();
    tempVec.clear();
    tempVec.push_back("4");
    tempVec.push_back("1");
    tempVec.push_back("3");
    board.push_back(tempVec);
    
    tempVec.clear();
    tempVec.push_back("0");
    tempVec.push_back("2");
    tempVec.push_back("5");
    board.push_back(tempVec);
    
    tempVec.clear();
    tempVec.push_back("7");
    tempVec.push_back("8");
    tempVec.push_back("6");
    board.push_back(tempVec);
    
    
    State state2(board, 1);
    state2.printBoard();
    state2.printStateInfo();
    activeQueue.push(&state2);
    */
    
    
    
    return 0;
    
}
