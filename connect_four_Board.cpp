// Header

// This class represents a 6 x 7 board
// used in 4-in-row game
class connect_four_Board : public Board {
public:
    connect_four_Board();

    bool update_board (int x,int y, char mark);
    void display_board();
    bool is_winner();
    bool toRightUp(int x,int y);
    bool toLeftDown(int x,int y);
    bool toLeftUp(int x,int y);
    bool toRightDown(int x,int y);
    bool toUp(int x, int y);
    bool toDown(int x, int y);
    bool toLeft(int x, int y);
    bool toRight(int x, int y);
    bool is_draw();
    bool game_is_over();
    friend class AiPlayer;
    friend class Player;
};
//////////////////////////////////////////////////



// Class definition for connect_four_Board class
// Author: Ramez Ragaay Makram Zaki
// Date: 12/15/2023
// Version: 1


#include <iostream>
#include <random>
#include <iomanip>
#include <algorithm>
#include "../include/BoardGame_Classes.hpp"
using namespace std;

// Set the board
connect_four_Board::connect_four_Board() {
    n_rows = 6;
    n_cols = 7;
    board = new char*[n_rows];
    for (int i = 0; i < n_rows; ++i) {
        board [i] = new char[n_cols];
        for (int j = 0; j < n_cols; ++j) {
            board[i][j] = 0;
        }
    }
}
bool valid(int x, int y){
    if(x >= 0 && x <= 5 && y >= 0 && y <= 6)
        return true;
    else
        return false;
}
// Return true  if the choosen column has empty cell/s
// within board boundaries in empty cell
// Return false otherwise
bool connect_four_Board::update_board(int x,int y, char mark) {
    if(y >= 0 && y <= 6){
        x = 5;
        while(valid(x,y) && board[x][y]){
            x--;
        }
        if(x >= 0){
            board[x][y] = mark;
            last_move_x = x;
            last_move_y = y;
            n_moves++;
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

// Display the board and the pieces on it
void connect_four_Board::display_board() {
    for (int i: {0,1,2,3,4,5}) {
        cout << "\n| ";
        for (int j: {0,1,2,3,4,5,6}) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << board [i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}


// Returns true if there is any winner
// either X or O

bool connect_four_Board::toUp(int x, int y) {
    int ux;
    for (int i = 1; i < 4; ++i) {
        ux = x - i;
        if(valid(ux,y) ){
            char c1 = board[ux][y], c2 = board[x][y];
            if(c1 != c2)
                return false;
        }
        else
            return false;
    }
    return true;
}
bool connect_four_Board::toDown(int x, int y) {
    int ux;
    for (int i = 1; i < 4; ++i) {
        ux = x + i;
        if(valid(ux,y) ){
            char c1 = board[ux][y], c2 = board[x][y];
            if(c1 != c2)
                return false;
        }
        else
            return false;
    }
    return true;
}
bool connect_four_Board::toLeft(int x, int y) {
    int ny;
    for (int i = 1; i < 4; ++i) {
        ny = y - i;
        if(valid(x,ny) ){
            char c1 = board[x][ny], c2 = board[x][y];
            if(c1 != c2)
                return false;
        }
        else
            return false;
    }
    return true;
}
bool connect_four_Board::toRight(int x, int y) {
    int ny;
    for (int i = 1; i < 4; ++i) {
        ny = y + i;
        if(valid(x,ny) ){
            char c1 = board[x][ny], c2 = board[x][y];
            if(c1 != c2)
                return false;
        }
        else
            return false;
    }
    return true;
}
bool connect_four_Board::toLeftUp(int x, int y) {
    int nx = x, ny = y;
    for(int i = 1; i < 4; i++){
        nx = x - i;
        ny = y - i;
        if(valid(nx,ny)) {
            if (board[x][y] != board[nx][ny])
                return false;
        }
        else
            return false;
    }
    return true;
}
bool connect_four_Board::toLeftDown(int x, int y) {
    int nx = x, ny = y;
    for(int i = 1; i < 4; i++){
        nx = x + i;
        ny = y - i;
        if(valid(nx,ny)) {
            if (board[x][y] != board[nx][ny])
                return false;
        }
        else
            return false;
    }
    return true;
}
bool connect_four_Board::toRightDown(int x, int y) {
    int nx = x, ny = y;
    for(int i = 1; i < 4; i++){
        nx = x + i;
        ny = y + i;
        if(valid(nx,ny)) {
            if (board[x][y] != board[nx][ny])
                return false;
        }
        else
            return false;
    }
    return true;
}
bool connect_four_Board::toRightUp(int x, int y) {
    int nx = x, ny = y;
    for(int i = 1; i < 4; i++){
        nx = x - i;
        ny = y + i;
        if(valid(nx,ny)) {
            if (board[x][y] != board[nx][ny])
                return false;
        }
        else
            return false;
    }
    return true;
}

bool connect_four_Board::is_winner() {
    int x = getX(); int y = getY();
    if(toLeftUp(x,y) || toRightDown(x,y) ||
       toLeftDown(x,y) || toRightUp(x,y) ||
       toUp(x,y) || toDown(x,y)||
       toLeft(x,y) || toRight(x,y))
        return true;

    return false;
}
// Return true if all moves are done and no winner
bool connect_four_Board::is_draw() {
    return (n_moves == 6*7 && !is_winner());
}
bool connect_four_Board::game_is_over() {
    return n_moves >= 6*7;
}
