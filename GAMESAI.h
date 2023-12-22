// File name: A3_Task2_3_S24_20221023_20221054_20221098
// Purpose: Games App
// Author(s): افرايم يوسف خميس دميان & رامز رجائي مكرم زكي & عبدالرحمن قدري محمد زينهم احمد
// ID(s): 20221023 & 20221054 & 20221098
// Section: S24
// Date: 17/12/2023

#ifndef ASS3_TASK3_GAMESAI_H
#define ASS3_TASK3_GAMESAI_H

#include <bits/stdc++.h>

using namespace std;

class Board {
protected:
    int n_rows, n_cols;
    char** board;
    int  n_moves = 0;
    int last_move_x, last_move_y;

public:
    virtual bool update_board (int x, int y, char symbol) = 0;

    virtual bool is_winner() = 0;

    virtual bool is_draw() = 0;

    virtual void display_board() = 0;

    virtual bool game_is_over() = 0;

    int getX();

    int getY();

    void setX(int x);

    void setY(int y);

    friend class AiPlayer;

    virtual int minimax(int &x, int &y, bool isMaximizing, bool firstTime , int depth = 0) = 0;

    virtual ~Board() = default;
};

/*================================================================*/

class Player {
protected:
    string name;
    char symbol;
public:
    Player (char symbol);
    Player (int order, char symbol);
    virtual void get_move(int& x, int& y);
    string to_string();
    char get_symbol();
};

/*================================================================*/

class Pyramid_TicTacToe : public Board {
public:
    Pyramid_TicTacToe();
    bool update_board (int x, int y, char mark);
    void display_board();
    bool is_winner();
    bool is_draw();
    bool game_is_over();
    int minimax(int &x, int &y, bool isMaximizing, bool firstTime , int depth = 0);
    int checkStatus();
};

/*================================================================*/

class X_O_Board:public Board {
public:
    X_O_Board ();
    bool update_board (int x, int y, char mark);
    void display_board();
    bool is_winner();
    bool is_draw();
    bool game_is_over();
    int minimax(int &x, int &y, bool isMaximizing, bool firstTime , int depth = 0);
    int checkStatus();
};

/*================================================================*/

class RandomPlayer: public Player {
protected:
    int dimensionX , dimensionY;
public:
    RandomPlayer (char symbol, int dimension1 , int dimension2);
    void get_move(int& x, int& y);
};

/*================================================================*/

class GameManager {
private:
    Board* boardPtr;
    Player* players[2];
public:
    GameManager(Board*, Player* playerPtr[2]);
    void run();
    ~GameManager();
};

/*================================================================*/

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
    bool check_valid(int x , int y );
    int minimax(int &x, int &y, bool isMaximizing, bool firstTime , int depth = 0);
    int checkWinner();
    ~Tic_Tec_Toe();
};

/*================================================================*/

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
    int minimax(int &x, int &y, bool isMaximizing, bool firstTime , int depth = 0);
    int checkStatus();
    ~connect_four_Board();
};

/*================================================================*/

class AIPlayer : public Player {
private:
    Board* board;
public:
    AIPlayer(char symbol , Board *board);
    void get_move(int& x , int& y);
};

#endif
