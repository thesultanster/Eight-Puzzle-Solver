#include "State.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Constructor
State::State(vector< vector<string> > board, int moves, int algo) {
    
    this->parent = NULL;
    
    this->algo = algo;
    
    
    // Copy Board
    this->board = board;
    
    // Calculate Manhatten Distance
    this->manhatten = CalculateManhattenDistance(board);
    
    // Number of moves
    this->moves = moves;
    
    // Calculate Priority
    switch (algo) {
        case 0:
            this->priority = this->moves;
            break;
        case 1:
            this->priority = this->moves + this->manhatten;
            break;
        case 2:
            this->misplaced = CalculateMisplacedTile(board);
            this->priority = this->moves + this->misplaced;
            break;
        default:
            break;
    }}

// Constructor
State::State(State* parent, vector< vector<string> > board, int moves, int algo) {
    
    this->parent = parent;
    
    this->algo = algo;
    
    // Copy Board
    this->board = board;
    
    
    // Calculate Manhatten Distance
    // Calculates blank X and Y
    this->manhatten = CalculateManhattenDistance(board);
    
    // Number of moves
    this->moves = moves;
    
    // Calculate Priority
    switch (algo) {
        case 0:
            this->priority = this->moves;
            break;
        case 1:
            this->priority = this->moves + this->manhatten;
            break;
        case 2:
            this->misplaced = CalculateMisplacedTile(board);
            this->priority = this->moves + this->misplaced;
            break;
        default:
            break;
    }
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

// Calculates Misplaced Tile
int State::CalculateMisplacedTile(vector< vector<string> > &board){
    
    int number = 0;
    
    vector<int> tempVec;
    vector< vector<int> > tempBoard;

    tempVec.push_back(1);
    tempVec.push_back(2);
    tempVec.push_back(3);
    tempBoard.push_back(tempVec);
    
    tempVec.clear();
    tempVec.push_back(4);
    tempVec.push_back(5);
    tempVec.push_back(6);
    tempBoard.push_back(tempVec);
    
    tempVec.clear();
    tempVec.push_back(7);
    tempVec.push_back(8);
    tempVec.push_back(0);
    tempBoard.push_back(tempVec);
    
    // For every tile
    for (int x = 0; x < board.size(); x++){
        for (int y = 0; y < board[x].size(); y++){
            int currentValue = atoi(board[x][y].c_str());
            if(tempBoard[x][y] != currentValue)
                number++;
        }
    }
    
    // TODO: Delete This
    //cout << endl << number << endl;
    
    return number;
    
}

// Prints the full board
const int State::getPriority() const{
    return this->priority;
}

State* State::getParent() {
    return this;
}

bool State::isGoalState() {
    
    int sum = 1;
    for (int i = 0; i < this->board.size(); i++){
        for (int j = 0; j < this->board[i].size(); j++){
            
            int currentValue = atoi(board[i][j].c_str());
            
            if( i == 2 && j == 2 && currentValue == 0 && sum == 9){
                cout << "last tile" << endl;
                return true;
            } else if( sum != currentValue){
                return false;
            }
            
            sum++;
        }
    }
    
    //cout << "outside check loop" << endl;
    return true;

}

int State::getBlankX(){
    return this->blankX;
}

int State::getBlankY(){
    return this->blankY;
}

int State::getMoves(){
    return this->moves;
}

vector< vector<string> > State::getBoard(){
    return this->board;
}

string State::getString(){
    
    string temp;
    
    for (int i = 0; i < this->board.size(); i++){
        for (int j = 0; j < this->board[i].size(); j++){
            temp += this->board[i][j] + " ";
        }
    }
    
    return temp;

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
    
    
    // Calculate Priority
    switch (algo) {
        case 0:
            cout << "Uniform Cost No Heuristic: " << endl;
            break;
        case 1:
            cout << "Manhatten Distance: "  << this->manhatten  << endl;
            break;
        case 2:
            cout << "Misplaced Tiles: "  << this->misplaced  << endl;
            break;
        default:
            break;
    }
    
    
    
    cout << "Moves: "               << this->moves      << endl;
    cout << "Priority : "           << this->priority   << endl << endl;
}

// Friend Overload Function
bool operator==(const State& lhs, const State& rhs){
    
    for (int i = 0; i < lhs.board.size(); i++)
        for (int j = 0; j < lhs.board[i].size(); j++)
            if(lhs.board[i][j] != rhs.board[i][j])
                return false;
    
    return true;
}

// Friend Overload Function

bool operator!=(const State& lhs, const State& rhs)
{
    return !operator==(lhs,rhs);
}

State& State::operator=(State rhs){
    

    
    for (int i = 0; i < this->board.size(); i++)
        for (int j = 0; j < this->board[i].size(); j++)
            this->board[i][j] = rhs.board[i][j];
            
    
    this->parent = rhs.parent;
    this->moves = rhs.moves;
    this->manhatten = rhs.manhatten;
    this->misplaced = rhs.misplaced;
    this->priority = rhs.priority;
    this->blankX = rhs.blankX;
    this->blankY = rhs.blankY;
    this->algo = rhs.algo;
    
    return *this;
    
    
}

