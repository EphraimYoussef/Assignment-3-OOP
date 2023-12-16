// Header

class Tic_Tec_Toe : public Board {

public:
    char player1Sign  = 'X', player2Sign = 'O' ;
    int  player1Counter = 0 , player2Counter = 0 ;


    Tic_Tec_Toe();
    bool update_board (int x, int y, char mark);
    void display_board();
    bool is_winner();
    bool is_draw();
    bool game_is_over();
    bool chcek_valid(int x , int y );

};



//Implement

#include <bits/stdc++.h>
#include"../include/BoardGame_Classes.hpp"
using namespace std;

// Set the board
Tic_Tec_Toe::Tic_Tec_Toe () {
    n_rows = n_cols = 5;
    board = new char*[n_rows];
    for (int i = 0; i < n_rows; i++) {
        board [i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++)
            board[i][j] = 0;
    }
}



// Return true  if move is valid and put it on board
// within board boundaries in empty cell
// Return false otherwise
bool Tic_Tec_Toe::update_board (int x, int y, char mark){
    // Only update if move is valid
    if (chcek_valid(x,y) && (board[x][y] == 0)) {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    }
    else
        return false;
}

// Display the board and the pieces on it
void Tic_Tec_Toe::display_board() {
    for (int i = 0; i < 5 ; ++i) {
        cout << "\n| ";
        for (int j = 0; j < 5 ; ++j) {
            cout << "(" << i << "," << j << ")";
            cout << setw(5) << board[i][j] << " |";
        }
        cout << "\n---------------------------------------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
// either X or O
bool Tic_Tec_Toe::is_winner() {

    if (n_moves == 24) {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (board[i][j] == player1Sign) {
                    if (chcek_valid(i, j + 1) && chcek_valid(i, j + 2)) { // row
                        if (board[i][j + 1] == player1Sign && board[i][j + 2] == player1Sign) {
                            player1Counter++;
                        }
                    }
                    if (chcek_valid(i + 1, j + 1) && chcek_valid(i + 2, j + 2)) { // principal diag
                        if (board[i + 1][j + 1] == player1Sign && board[i + 2][j + 2] == player1Sign) {
                            player1Counter++;
                        }
                    }
                    if (chcek_valid(i + 1, j) && chcek_valid(i + 2, j)) { // vertical
                        if (board[i + 1][j] == player1Sign && board[i + 2][j] == player1Sign) {
                            player1Counter++;
                        }
                    }
                    if (chcek_valid(i - 1, j - 1) && chcek_valid(i - 2, j - 2)) { // opposite diag
                        if (board[i - 1][j - 1] == player1Sign && board[i - 1][j - 2] == player1Sign) {
                            player1Counter++;
                        }
                    }

                } else if (board[i][j] == player2Sign) {
                    if (chcek_valid(i, j + 1) && chcek_valid(i, j + 2)) { // row
                        if (board[i][j + 1] == player2Sign && board[i][j + 2] == player2Sign) {
                            player2Counter++;
                        }
                    }
                    if (chcek_valid(i + 1, j + 1) && chcek_valid(i + 2, j + 2)) { // principal diag
                        if (board[i + 1][j + 1] == player2Sign && board[i + 2][j + 2] == player2Sign) {
                            player2Counter++;
                        }
                    }
                    if (chcek_valid(i + 1, j) && chcek_valid(i + 2, j)) { // vertical
                        if (board[i + 1][j] == player2Sign && board[i + 2][j] == player2Sign) {
                            player2Counter++;
                        }
                    }
                    if (chcek_valid(i - 1, j - 1) && chcek_valid(i - 2, j - 2)) { // opposite diag
                        if (board[i - 1][j - 1] == player2Sign && board[i - 1][j - 2] == player2Sign) {
                            player2Counter++;
                        }
                    }
                }
            }
        }
        if (player1Counter > player2Counter){
            cout << player1Sign << " wins\n";
        }
        else if (player2Counter > player1Counter){
            cout << player2Sign << " wins\n";
        }
    }

    return false ;

}

// Return true if 24 moves are done and no winner
bool Tic_Tec_Toe::is_draw() {
    return (n_moves == 24 && player1Counter == player2Counter);
}

bool Tic_Tec_Toe::game_is_over () {
    return n_moves >= 24;
}

bool Tic_Tec_Toe::chcek_valid(int x, int y) {
    return  (x >= 0 && x < 5 && y >= 0 && y < 5) ;
}


