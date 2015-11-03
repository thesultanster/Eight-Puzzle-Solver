#include "State.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Constructor
State::State(vector< vector<string> > board, int moves) {
    
    // Copy Board
    this->board = board;
    
    // Calculate Manhatten Distance
    this->manhatten = CalculateManhattenDistance(board);
    
    this->moves = moves;
    
    // Calculate Priority
    this->priority = this->moves + this->manhatten;
}

// Constructor
State::State(State* state) {
    
    // Copy Board
    this->board = state->board;
    // Recalculate so we can get the blankX and blankY values
    this->manhatten = CalculateManhattenDistance(this->board);
    this->moves = state->moves;
    this->priority = state->priority;
}

vector<State> State::GenerateAllPossibleMoves(){
    
    vector<State> states;
    vector< vector<string> > newBoard;
    
    // Move Left, if possible
    if((blankY - 1) >= 0){
        newBoard = this->board;
        iter_swap(newBoard[blankX].begin() + blankY, newBoard[blankX].begin() + (blankY-1));
        State newState( newBoard, this->moves+1 );
        states.push_back(newState);
        newState.printBoard();
        newState.printStateInfo();
    }
    
    // Move Right, if possible
    if((blankY + 1) >= 0){
        newBoard = this->board;
        iter_swap(newBoard[blankX].begin() + blankY, newBoard[blankX].begin() + (blankY+1));
        State newState( newBoard, this->moves+1 );
        states.push_back(newState);
        newState.printBoard();
        newState.printStateInfo();
    }
    
    // Move Top, if possible
    if((blankX + 1) >= 0){
        newBoard = this->board;
        iter_swap(newBoard[blankX].begin() + blankY, newBoard[blankX+1].begin() + (blankY));
        State newState( newBoard, this->moves+1 );
        states.push_back(newState);
        newState.printBoard();
        newState.printStateInfo();
    }
    
    // Move Bottom, if possible
    if((blankX - 1) >= 0){
        newBoard = this->board;
        iter_swap(newBoard[blankX].begin() + blankY, newBoard[blankX-1].begin() + (blankY));
        State newState( newBoard, this->moves+1 );
        states.push_back(newState);
        newState.printBoard();
        newState.printStateInfo();
    }
    
    return states;

}

// Calculates Distance of current tile to goal tile
int State::DistanceToGoal( int x, int y){
    
    int distance = 0;
    int goalX;
    int goalY;
    
    // Calculate Goal Tile Location
    int currentValue = atoi(board[x][y].c_str());
    goalY = (currentValue-1)%3;
    goalX = (currentValue-1)/3;
    
    // Calculate Manhatten Distance
    distance = abs(x-goalX) + abs(y-goalY);
    
    // TODO: Delete This
    //cout << x << " " << y << " : " << goalX << " " << goalY << " :: " << distance << endl;

    return distance;
}

// Calculates Manhatten Distance
int State::CalculateManhattenDistance(vector< vector<string> > &board){
    
    int distance = 0;
    
    // For every tile
    for (int x = 0; x < board.size(); x++){
        for (int y = 0; y < board[x].size(); y++){
            
            // Calculate distance of every tile except blank tile
            if( board[x][y] != "0"){
                
                // Sum up all manhatten distances to generate total heuristic value
                distance += DistanceToGoal(x,y);
            }
            // Save Location of blank tile for later usage
            else {
                
                this->blankX = x;
                this->blankY = y;
            }
        }
    }
    
    // TODO: Delete This
    //cout << endl << distance << endl;
    return distance;

}

// Prints the full board
const int State::getPriority() const{
    return this->priority;
}

bool operator==(const State& lhs, const State& rhs){
    
    for (int i = 0; i < lhs.board.size(); i++)
        for (int j = 0; j < lhs.board[i].size(); j++)
            if(lhs.board[i][j] != rhs.board[i][j])
                return false;
    
    return true;
}


bool operator!=(const State& lhs, const State& rhs)
{
    return !operator==(lhs,rhs);
}

// Prints the full board
void State::printBoard(){
    for (int i = 0; i < this->board.size(); i++){
        for (int j = 0; j < this->board[i].size(); j++){
            cout << this->board[i][j] << " ";
        }
        cout << endl;
    }
}

// Prints State Information
void State::printStateInfo(){
    cout << "Manhatten Distance: "  << this->manhatten  << endl;
    cout << "Moves: "               << this->moves      << endl;
    cout << "Priority : "           << this->priority   << endl << endl;
}
