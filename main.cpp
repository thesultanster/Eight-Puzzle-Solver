
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

int main(){
    
    string row;
    vector<string> tempVec;
    vector< vector<string> > board;
    
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
    
    
    
    return 0;
    
}
