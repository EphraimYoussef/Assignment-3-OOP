// File name:A3_SheetPb6_20221098
// Purpose: Game of Life
// Author(s): Abdelrahman Kadry Mohamed
// ID(s): 20221098
// Section:S24
// Date: 11/12/2023
#include <bits/stdc++.h>
using namespace std ;
#define ll long long
#define el '\n'
#define sp ' '
#define END return 0 ;

class Universe {

private:
    int rows;
    int columns;
    vector<vector<int>> grid;

public:
    Universe(int row , int column);
    void initialize(); //generates a starting layout
    void reset () ;//sets all the cells as dead.
    int count_neighbors(int row, int col);// returns the number of alive neighbors.
    void next_generation();// produces a new state of the game based on the transition rules
    void display();//shows the game status on the console
    void run(int num_generations); //to start the game for a certain number of runs
    ~Universe();

};



Universe::Universe(int row , int column): rows (row) , columns (column) { // a constructor to set the rows and columns and the grid size
    grid.resize(rows, vector<int>(columns, 0));}


void Universe::initialize() {
    reset(); // to reset the grid at the first

    int counter = 0 ; // to print at the screen the cell number to allow the player to choose the alive cells

    string  maxGridSize = ""+ to_string(rows * columns ) ; // to know the size of the number cell to help me at the printing

    for (int i = 0; i < rows ; ++i) { // loop for printing the cells numbers at the screen
        for (int j = 0 ;  j < columns; ++j) {
            cout << counter ;
            for (int k = 0; k < maxGridSize.size() - to_string(counter).size(); ++k) {
                cout << sp ;
            }
            cout << '|' ;
            counter++;
        }
        cout << el ;
    }

    // from here I started to take the cells that the player want to be alive
    cout << "Enter the cells numbers that you want to be alive \n* Note enter (-1) if you are finished *\n";
    int num = 0;
    vector <int> aliveCells ; // vector to set the alive cells

    bool check = true ;
    while (check){
        cin >> num ;
        if (num == -1) {
            check = false;
            break;
        }
        else { // handling player's error at choosing the cells
            if (std::count(aliveCells.begin(), aliveCells.end(), num)) {
                cout << "A repeated number try another \n";
            }
            else if (num > stoi (maxGridSize) - 1 ){
                cout << "An out of range number try another \n";

            }
            else
                aliveCells.push_back(num);
        }
    }

    for (int i = 0; i < aliveCells.size() ; ++i) { // assign the grid with the player values
        int newi = (aliveCells[i]/rows) , newj = (aliveCells[i]%columns) ;
        grid [newi][newj] = 1 ;
    }

}


void Universe::reset() { // make the grid all dead to start a new generation

    for (int i = 0; i < rows ; ++i) {
        for (int j = 0 ;  j < columns; ++j) {
            grid[i][j] = 0 ;
        }
    }
}


int Universe:: count_neighbors(int row, int col) { // looping at each cell to know the alive cells which are around it
    int count = 0;
    for (int i = row - 1; i <= row + 1; ++i) {
        for (int j = col - 1; j <= col + 1; ++j) {
            if (i >= 0 && i < rows && j >= 0 && j < columns && !(i == row && j == col)) { // checking the boundary
                count += grid[i][j];
            }
        }
    }
    return count;
}


void Universe::next_generation() { // the only 4 transactions occurring on every step
    vector< vector<int>> new_grid(rows, vector<int>(columns, 0));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            int neighbors = count_neighbors(i, j);
            if (grid[i][j] == 1) {
                if (neighbors < 2 || neighbors > 3) {
                    new_grid[i][j] = 0;
                } else {
                    new_grid[i][j] = 1;
                }
            } else {
                if (neighbors == 3) {
                    new_grid[i][j] = 1;
                }
            }
        }
    }
    grid = new_grid;
}


void Universe::display() { // printing a grid of each generation
    string  maxGridSize = ""+ to_string(rows * columns ) ;
    for (int i = 0; i < rows ; ++i) {
        for (int j = 0 ;  j < columns; ++j) {
            if (grid[i][j]){
                cout <<" * "<< '|' ;
            }
            else {
                cout <<"   "<< '|' ;

            }
        }
        cout << el ;
    }
    cout << "-----------------------------------------------------------------" << el ;
}


void Universe :: run(int num_generations) { // running the game with the times that the player need
    for (int i = 0; i < num_generations; ++i) {
        display();
        next_generation();
        if (i == num_generations - 1 ){
            cout << "If you want to run another generations Enter (y) else enter (n)\n" ;
            char c ; cin >> c ;
            if (c == 'y'){
                cout << "Enter how many generation that you need : \n" ;

                int times ; cin >> times;
                run(times) ;
            }
        }
    }
}


Universe::~Universe() {
 cout << "Thanks for playing my game I hope you enjoyed it ^_^ \n";
}


int main(){
    cout << "         * Welcome to 'Game of Life' * \nFirstly we need to set the grid size that you want.\n";
    cout << "a small recommendation 10 * 10 will be great and enjoyable \n\n" ;
    cout << "The rows size :";
    int player_needed_Rows ; cin >> player_needed_Rows ;

    cout << "The columns size :";
    int player_needed_columns  ; cin >> player_needed_columns ;
    Universe Game(player_needed_Rows, player_needed_columns) ;
    cout << el ;

    Game.initialize();

    cout << "Enter how many generation that you need : \n" ;

    int times ; cin >> times;
    Game.run(times) ;

    END
}
