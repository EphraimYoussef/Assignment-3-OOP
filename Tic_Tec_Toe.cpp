// Header
//Implement

#include <bits/stdc++.h>
#include"../include/BoardGame_Classes.hpp"
using namespace std;
Tic_Tec_Toe::Tic_Tec_Toe () {
    n_rows = n_cols = 5;
    board = new char*[n_rows];
    for (int i = 0; i < n_rows; i++) {
        board[i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++) {

            board[i][j] = 0;

        }
    }
}



bool Tic_Tec_Toe::update_board (int x, int y, char mark){
    // Only update if move is valid
    if (check_valid(x, y) && (board[x][y] == 0)) {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    }
    else
        return false;
}


void Tic_Tec_Toe::display_board() {
    cout << "\n\n+---------+---------+---------+---------+---------+";

    for (int i = 0; i < 5 ; ++i) {
        cout << "\n| ";
        for (int j = 0; j < 5 ; ++j) {

cout << "     " ;
cout << setw(2) << board[i][j] << " | ";
        }
        cout << "\n+---------+---------+---------+---------+---------+";

    }
    cout << endl << endl;
}


bool Tic_Tec_Toe::is_draw() {
    return (n_moves == 24 && player1Counter == player2Counter);
}


bool Tic_Tec_Toe::game_is_over () {
    return n_moves >= 24;
}


bool Tic_Tec_Toe::is_winner() {

    if (n_moves == 24) {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (board[i][j] == 'X') {
                    if (check_valid(i, j + 1) && check_valid(i, j + 2)) { // row
                        if (board[i][j + 1] == 'X' && board[i][j + 2] == 'X') {
                            player1Counter++;
                        }
                    }
                    if (check_valid(i + 1, j + 1) && check_valid(i + 2, j + 2)) { // principal diag
                        if (board[i + 1][j + 1] == 'X' && board[i + 2][j + 2] == 'X') {
                            player1Counter++;
                        }
                    }
                    if (check_valid(i + 1, j) && check_valid(i + 2, j)) { // vertical
                        if (board[i + 1][j] == 'X' && board[i + 2][j] == 'X') {
                            player1Counter++;
                        }
                    }
                    if (check_valid(i - 1, j - 1) && check_valid(i - 2, j - 2)) { // opposite diag
                        if (board[i - 1][j - 1] == 'X' && board[i - 2][j - 2] == 'X') {
                            player1Counter++;
                        }
                    }

                } else if (board[i][j] == 'O') {
                    if (check_valid(i, j + 1) && check_valid(i, j + 2)) { // row
                        if (board[i][j + 1] == 'O' && board[i][j + 2] == 'O') {
                            player2Counter++;
                        }
                    }
                    if (check_valid(i + 1, j + 1) && check_valid(i + 2, j + 2)) { // principal diag
                        if (board[i + 1][j + 1] == 'O' && board[i + 2][j + 2] == 'O') {
                            player2Counter++;
                        }
                    }
                    if (check_valid(i + 1, j) && check_valid(i + 2, j)) { // vertical
                        if (board[i + 1][j] == 'O' && board[i + 2][j] == 'O') {
                            player2Counter++;
                        }
                    }
                    if (check_valid(i - 1, j - 1) && check_valid(i - 2, j - 2)) { // opposite diag
                        if (board[i - 1][j - 1] == 'O' && board[i - 2][j - 2] == 'O') {
                            player2Counter++;
                        }
                    }
                }
            }
        }
        if (player1Counter > player2Counter){
//            cout << player1Sign << " made " << player1Counter << " in_a_row\n" ;
//            cout << player2Sign << " made " << player2Counter << " in_a_row\n" ;
            cout << player1Sign << " wins\n";
        }
        else if (player2Counter > player1Counter){
//            cout << player1Sign << " made " << player1Counter << " in_a_row\n" ;
//            cout << player2Sign << " made " << player2Counter << " in_a_row\n" ;
            cout << player2Sign << " wins\n";
        }
    }

    return false ;

}


bool Tic_Tec_Toe::check_valid(int x, int y) {
    return  (x >= 0 && x < 5 && y >= 0 && y < 5) ;
}

int Tic_Tec_Toe::minimax(int &a, int &b, bool isMaximizing, bool firstTime  , int depth   ) {
    if (n_moves <= 12) {
        a = (int) (rand() / (RAND_MAX + 1.0) * 5);
        b = (int) (rand() / (RAND_MAX + 1.0) * 5);
        return 0;
    }

    int count = 1;
    int result = checkWinner();
    if (depth <= 0 || result != 1) {
        return result;
    }

    int mxScore = -1000, mnScore = 1000;
    int finalX = -1, finalY = -1;  // Initialize to invalid values

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (board[i][j] == 0) {

                if (isMaximizing) {

                    board[i][j] = 'X';
                    n_moves++;
                    int newScore = minimax(a, b, false, false, depth - 1);
                    board[i][j] = 0;
                    n_moves--;

                    if (newScore > mxScore) {
                        mxScore = newScore;
                        finalX = i;
                        finalY = j;
                    }

                } else {
                    board[i][j] = 'O';
                    n_moves++;
                    int newScore = minimax(a, b, true, false, depth - 1);
                    board[i][j] = 0;
                    n_moves--;

                    if (newScore < mnScore) {
                        mnScore = newScore;
                        finalX = i;
                        finalY = j;
                    }

                }
            }
        }
    }

    if (firstTime) {
        a = finalX, b = finalY;
    }

    return isMaximizing ? mxScore : mnScore;
}

int Tic_Tec_Toe::checkWinner()  {
    if (n_moves < 24 ) {
            return 1;
    }
        int playc1 = 0 , playerc2 = 0  ;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {

                if (board[i][j] == 'X') {
                    if (check_valid(i, j + 1) && check_valid(i, j + 2)) { // row
                        if (board[i][j + 1] == 'X' && board[i][j + 2] == 'X') {
                            playc1++;
                        }
                    }
                    if (check_valid(i + 1, j + 1) && check_valid(i + 2, j + 2)) { // principal diag
                        if (board[i + 1][j + 1] == 'X' && board[i + 2][j + 2] == 'X') {
                            playc1++;
                        }
                    }
                    if (check_valid(i + 1, j) && check_valid(i + 2, j)) { // vertical
                        if (board[i + 1][j] == 'X' && board[i + 2][j] == 'X') {
                            playc1++;
                        }
                    }
                    if (check_valid(i - 1, j - 1) && check_valid(i - 2, j - 2)) { // opposite diag
                        if (board[i - 1][j - 1] == 'X' && board[i - 2][j - 2] == 'X') {
                            playc1++;
                        }
                    }

                }

                else if (board[i][j] == 'O') {
                    if (check_valid(i, j + 1) && check_valid(i, j + 2)) { // row
                        if (board[i][j + 1] == 'O' && board[i][j + 2] == 'O') {
                            playerc2++;
                        }
                    }
                    if (check_valid(i + 1, j + 1) && check_valid(i + 2, j + 2)) { // principal diag
                        if (board[i + 1][j + 1] == 'O' && board[i + 2][j + 2] == 'O') {
                            playerc2++;
                        }
                    }
                    if (check_valid(i + 1, j) && check_valid(i + 2, j)) { // vertical
                        if (board[i + 1][j] == 'O' && board[i + 2][j] == 'O') {
                            playerc2++;
                        }
                    }
                    if (check_valid(i - 1, j - 1) && check_valid(i - 2, j - 2)) { // opposite diag
                        if (board[i - 1][j - 1] == 'O' && board[i - 2][j - 2] == 'O') {
                            playerc2++;
                        }
                    }
                }
            }
        }
        if (playc1 > playerc2 && n_moves == 24 ){
            return 2;
        }
        else if (playerc2 > playc1 && n_moves == 24){
            return -2 ;
        }
        else if (playc1 == playerc2 && n_moves == 24) {
            return 0 ;
        }
}
