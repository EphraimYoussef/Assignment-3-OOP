#ifndef ASS3_GAME1_PYRAMID_TICTACTOE_H
#define ASS3_GAME1_PYRAMID_TICTACTOE_H

#include <bits/stdc++.h>

using namespace std;


class Board {
protected:
    int n_rows, n_cols;
    char** board;
    int  n_moves = 0;

public:
    virtual bool update_board (int x, int y, char symbol) = 0;

    virtual bool is_winner() = 0;

    virtual bool is_draw() = 0;

    virtual void display_board() = 0;

    virtual bool game_is_over() = 0;

    virtual int minimax(int &x, int &y, bool isMaximizing, bool firstTime) = 0;
};

///////////////////////////////////////////

class Player {
protected:
    string name;
    char symbol;
public:
    // Two constructors to initiate player
    // Give player a symbol to use in playing
    // It can be X or O or others
    // Optionally, you can give him ID or order
    // Like Player 1 and Player 2
    Player (char symbol); // Needed for computer players
    Player (int order, char symbol);
    Player();

    // Get desired move: x y (each between 0 and 2)
    // Virtual (can change for other player types)
    virtual void get_move(int& x, int& y);

    // Give player info as a string
    string to_string();

    // Get symbol used by player
    char get_symbol();
};

///////////////////////////////////////////

class Pyramid_TicTacToe : public Board {
public:
    Pyramid_TicTacToe();
    bool update_board (int x, int y, char mark);
    void display_board();
    bool is_winner();
    bool is_draw();
    bool game_is_over();
    int minimax(int &x, int &y, bool isMaximizing, bool firstTime);
    int checkStatus();
};

///////////////////////////////////////////

class RandomPlayer: public Player {
protected:
    int dimensionX , dimensionY;
public:
    // Take a symbol and pass it to parent
    RandomPlayer (char symbol, int dimension1 , int dimension2);
    // Generate a random move
    void get_move(int& x, int& y);
};

///////////////////////////////////////////

class GameManager {
private:
    Board* boardPtr;
    Player* players[2];
public:
    GameManager(Board*, Player* playerPtr[2]);
    void run();
};

///////////////////////////////////////////

class AIPlayer : public Player {
private:
    Board* board;
public:
    AIPlayer(char symbol , Board *board);
    void get_move(int& x , int& y);
};

#endif

