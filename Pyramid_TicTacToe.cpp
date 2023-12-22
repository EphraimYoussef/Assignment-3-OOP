#include <bits/stdc++.h>
#include "Pyramid_TicTacToe.h"
using namespace std;

GameManager::GameManager(Board* bPtr, Player* playerPtr[2] ) {
    boardPtr = bPtr;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];
}

void GameManager::run() {
    int x, y;

    boardPtr->display_board();

    while ( !boardPtr->game_is_over() ) {
        for (int i:{0,1}) {
            players[i]->get_move(x, y);
            while (!boardPtr->update_board (x, y, players[i]->get_symbol())){
                players[i]->get_move(x, y);
            }
            boardPtr -> display_board();
            if (boardPtr->is_winner()){
                cout  << players[i] -> to_string() << " wins\n";
                return;
            }
            if (boardPtr->is_draw()){
                cout << "Draw!\n";
                return;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////

// Give player a symbol to use in playing
// It can be X or O or others
// This is needed for computer players
// as it does not ask for a name
Player::Player(char symbol) {
    this->symbol = symbol;
}

// Optionally, you can give him ID or order
// Like Player 1 and Player 2
Player::Player (int order, char symbol) {
    cout << "Welcome player " << order << '\n';
    cout << "Please enter your name:";
    cin >> name;
    this->symbol = symbol;
}

// Get desired move: x y (each between 0 and 2)
// Virtual (can change for other player types)
void Player::get_move (int& x, int& y) {
    cout << "\nPlease enter your move (x , y) from the board separated by spaces:";
    cin >> x >> y;
}

// Give player info as a string
string Player::to_string(){
    return "Player: " + name ;
}

// Get symbol used by player
char Player::get_symbol() {
    return symbol;
}

Player::Player() {

}

//////////////////////////////////////////////////////////////////////////////////

// Set player symbol and name as Random Computer Player
RandomPlayer::RandomPlayer (char symbol, int dimensionX ,int dimensionY):Player(symbol)
{
    this -> dimensionX = dimensionX;
    this -> dimensionY = dimensionY;
    this -> name = "Random Computer Player";
    cout << "My names is " << name << endl;
}

// Generate a random move
void RandomPlayer::get_move (int& x, int& y) {
    x = (int) (rand()/(RAND_MAX + 1.0) * dimensionX);
    y = (int) (rand()/(RAND_MAX + 1.0) * dimensionY);
}

//////////////////////////////////////////////////////////////////////////////////


Pyramid_TicTacToe::Pyramid_TicTacToe() {
    n_rows = 3;
    n_cols = 5;
    board = new char*[n_rows];
    for (int i = 0; i < n_rows; i++) {
        board [i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++)
            board[i][j] = 0;
    }
}

bool Pyramid_TicTacToe::update_board(int x, int y, char mark) {
    // Only update if move is valid
    if ( (x+y>=2 && abs(x-y)<=2) && (board[x][y] == 0) ) {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    }
    else {
        return false;
    }
}

void Pyramid_TicTacToe::display_board() {
    bool firstInLine = true , firstLine = true;
    cout << endl << "                +-------+\n";
    for (int i: {0,1,2}) {
        for (int j: {0,1,2,3,4}) {
            if (i+j>=2 && abs(i-j)<=2){
                if (firstInLine){cout<<"| ";firstInLine= false;}
                if (board[i][j]==0){
                    cout << "(" << i << "," << j << ")" << " | ";
                }
                else{
                    cout << setw(3) << board [i][j] << "   | " ;
                }
            } else {
                cout<<"        ";
            }
        }
        firstInLine= true;
        if (firstLine){
            cout << "\n        +-------+-------+-------+\n"; firstLine= false;
        }
        else {
            cout << "\n+-------+-------+-------+-------+-------+\n";
        }
    }
    cout << endl;
}

bool Pyramid_TicTacToe::is_winner() {
    if ( board[0][2]==board[1][2] && board[1][2]==board[2][2] && board[2][2]!=0){
        return true;
    }
    else if( board[0][2]==board[1][3] && board[1][3]==board[2][4] && board[2][4]!=0 ) {
        return true;
    }
    else if( board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[2][0]!=0 ){
        return true;
    }
    else if( board[1][1]==board[1][2] && board[1][2]==board[1][3] && board[1][3]!=0 ){
        return true;
    }
    else{
        for (int i = 0; i < 3; ++i) {
            if ( board[2][i]==board[2][i+1] && board[2][i+1]==board[2][i+2] && board[2][i+2]!=0 ){
                return true;
            }
        }
    }
    return false;
}

bool Pyramid_TicTacToe::is_draw() {
    return (n_moves == 9 && !is_winner());
}

bool Pyramid_TicTacToe::game_is_over() {
    return n_moves >= 9;
}

int Pyramid_TicTacToe::minimax(int &x, int &y, bool isMaximizing, bool firstTime) {
    int result = checkStatus();
    int maxScore = -10 , minScore = 10;
    int bestI , bestJ;
    if (result != 1){
        return result;
    }
    for (int i = 0; i < n_rows; ++i) {
        for (int j = 0; j < n_cols; ++j) {
            if( (i+j>=2 && abs(i-j)<=2) && (board[i][j] == 0) ){
                if (isMaximizing) {
                    n_moves++;
                    board[i][j]='X';
                    int newScore = minimax(x, y, false, false);
                    board[i][j]=0;
                    n_moves--;
                    if (newScore > maxScore) {
                        maxScore = newScore;
                        bestI = i;
                        bestJ = j;
                    }
                    if (firstTime){
                        cout << "max in" << '[' << i << ',' << j << " ]  " << newScore <<
                        (newScore == 2 ? " X wins\n" : (newScore == -2) ? " O wins\n" : " Draw\n");
                    }
                }
                else {
                    n_moves++;
                    board[i][j]='O';
                    int newScore = minimax(x, y, true, false);
                    board[i][j]=0;
                    n_moves--;
                    if (newScore < minScore) {
                        minScore = newScore;
                        bestI = i;
                        bestJ = j;
                    }
                    if (firstTime){
                        cout << "mini in" << '[' << i << ',' << j << "]  " << newScore <<
                        (newScore == -2 ? " O wins\n" : (newScore == 2) ? " X wins\n" : " Draw\n");
                    }
                }
            }
        }
    }
    if (firstTime){
        x = bestI;
        y = bestJ;
    }
    return ( isMaximizing ? maxScore :minScore);
}

int Pyramid_TicTacToe::checkStatus() {
    if ( ( board[0][2]==board[1][2] && board[1][2]==board[2][2] && board[2][2]=='X' ) ||
         ( board[0][2]==board[1][3] && board[1][3]==board[2][4] && board[2][4]=='X' ) ||
         ( board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[2][0]=='X' ) ||
         ( board[1][1]==board[1][2] && board[1][2]==board[1][3] && board[1][3]=='X' ) ){
         return 2;
    }
    else {
        for (int i = 0; i < 3; ++i) {
            if ( board[2][i]==board[2][i+1] && board[2][i+1]==board[2][i+2] && board[2][i+2]=='X' ){
                return 2;
            }
        }
    }

    if ( (board[0][2]==board[1][2] && board[1][2]==board[2][2] && board[2][2]=='O') ||
         (board[0][2]==board[1][3] && board[1][3]==board[2][4] && board[2][4]=='O') ||
         (board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[2][0]=='O') ||
         (board[1][1]==board[1][2] && board[1][2]==board[1][3] && board[1][3]=='O') ){
        return -2;
    }
    else {
        for (int i = 0; i < 3; ++i) {
            if ( board[2][i]==board[2][i+1] && board[2][i+1]==board[2][i+2] && board[2][i+2]=='O' ){
                return -2;
            }
        }
    }

    if (n_moves == 9){
        return 0;
    }

    return 1;
}


////////////////////////////////////////////////////////////////////////////////////////

AIPlayer::AIPlayer(char symbol, Board *board) : Player(symbol), board(board) {
    this -> name = "AI Player";
    cout << "My names is " << name << endl;
}

void AIPlayer::get_move(int &x, int &y) {
    board -> minimax(x,y, false,true);
}

