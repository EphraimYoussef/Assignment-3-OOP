// File name: A3_Task2_3_S24_20221023_20221054_20221098
// Purpose: Games App
// Author(s): افرايم يوسف خميس دميان & رامز رجائي مكرم زكي & عبدالرحمن قدري محمد زينهم احمد
// ID(s): 20221023 & 20221054 & 20221098
// Section: S24
// Date: 17/12/2023

#include <bits/stdc++.h>
#include "gamesApp.h"

using namespace std;

bool is4InRow ;

int Board::getX() {
    return last_move_x;
}

int Board::getY() {
    return last_move_y;
}

void Board::setX(int x) {
    last_move_x = x;
}

void Board::setY(int y) {
    last_move_y = y;
}

/*====================================================================================*/

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

/*====================================================================================*/

Player::Player(char symbol) {
    this->symbol = symbol;
}

Player::Player (int order, char symbol) {
    cout << "\nWelcome player " << order << '\n';
    cout << "Please enter your name:";
    cin >> name;
    this->symbol = symbol;
}

void Player::get_move (int& x, int& y) {
    if (is4InRow){
        cout << "\nPlease enter the column you want to put in: ";
        cin >> y;
        x = 0;
    }
    else {
        cout << "\nPlease enter your move (x , y) from the board separated by spaces:";
        cin >> x >> y;
    }
}

string Player::to_string(){
    return "Player:" + name ;
}

char Player::get_symbol() {
    return symbol;
}

/*====================================================================================*/

RandomPlayer::RandomPlayer (char symbol, int dimensionX ,int dimensionY):Player(symbol)
{
    this -> dimensionX = dimensionX;
    this -> dimensionY = dimensionY;
    this -> name = "Random Computer Player";
    cout << "\nHello, I am " << name << endl << endl;
}

void RandomPlayer::get_move (int& x, int& y) {
    x = (int) (rand()/(RAND_MAX + 1.0) * dimensionX);
    y = (int) (rand()/(RAND_MAX + 1.0) * dimensionY);
}

/*====================================================================================*/

X_O_Board::X_O_Board () {
    n_rows = n_cols = 3;
    board = new char*[n_rows];
    for (int i = 0; i < n_rows; i++) {
        board [i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++)
            board[i][j] = 0;
    }
}

bool X_O_Board::update_board (int x, int y, char mark){
    if (!(x < 0 || x > 2 || y < 0 || y > 2) && (board[x][y] == 0)) {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    }
    else
        return false;
}

void X_O_Board::display_board() {
    cout << "\n\n+---------+---------+---------+";

    for (int i: {0,1,2}) {
        cout << "\n| ";
        for (int j: {0,1,2}) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << board [i][j] << " | ";
        }
        cout << "\n+---------+---------+---------+";
    }
    cout << endl << endl;
}

bool X_O_Board::is_winner() {
    char row_win[3], col_win[3], diag_win[2];
    for (int i:{0,1,2}) {
        row_win[i] = board[i][0] & board[i][1] & board[i][2];
        col_win[i] = board[0][i] & board[1][i] & board[2][i];
    }
    diag_win[0] = board[0][0] & board[1][1] & board[2][2];
    diag_win[1] = board[2][0] & board[1][1] & board[0][2];

    for (int i:{0,1,2}) {
        if ( (row_win[i] && (row_win[i] == board[i][0])) ||
             (col_win[i] && (col_win[i] == board[0][i])) )
        {return true;}
    }
    if ((diag_win[0] && diag_win[0] == board[1][1]) ||
        (diag_win[1] && diag_win[1] == board[1][1]))
    {return true;}
    return false;
}

bool X_O_Board::is_draw() {
    return (n_moves == 9 && !is_winner());
}

bool X_O_Board::game_is_over () {
    return n_moves >= 9;
}

/*====================================================================================*/

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
    cout << endl << "                    +---------+\n";
    for (int i: {0,1,2}) {
        for (int j: {0,1,2,3,4}) {
            if (i+j>=2 && abs(i-j)<=2){
                if (firstInLine){cout<<'|';firstInLine= false;}
                cout << " (" << i << "," << j << ")";
                cout << setw(2) << board [i][j] << " |";
            } else {
                cout<<"          ";
            }
        }
        firstInLine= true;
        if (firstLine){
            cout << "\n          +---------+---------+---------+\n"; firstLine= false;
        }
        else {
            cout << "\n+---------+---------+---------+---------+---------+\n";
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

/*====================================================================================*/

Tic_Tec_Toe::Tic_Tec_Toe () {
    n_rows = n_cols = 5;
    board = new char*[n_rows];
    for (int i = 0; i < n_rows; i++) {
        board [i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++)
            board[i][j] = 0;
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
    cout << "\n+---------+---------+---------+---------+---------+";

    for (int i = 0; i < 5 ; ++i) {
        cout << "\n| ";
        for (int j = 0; j < 5 ; ++j) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << board[i][j] << " | ";
        }
        cout << "\n+---------+---------+---------+---------+---------+";

    }
    cout << endl;
}

bool Tic_Tec_Toe::is_winner() {

    if (n_moves == 24) {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (board[i][j] == player1Sign) {
                    if (check_valid(i, j + 1) && check_valid(i, j + 2)) { // row
                        if (board[i][j + 1] == player1Sign && board[i][j + 2] == player1Sign) {
                            player1Counter++;
                        }
                    }
                    if (check_valid(i + 1, j + 1) && check_valid(i + 2, j + 2)) { // principal diag
                        if (board[i + 1][j + 1] == player1Sign && board[i + 2][j + 2] == player1Sign) {
                            player1Counter++;
                        }
                    }
                    if (check_valid(i + 1, j) && check_valid(i + 2, j)) { // vertical
                        if (board[i + 1][j] == player1Sign && board[i + 2][j] == player1Sign) {
                            player1Counter++;
                        }
                    }
                    if (check_valid(i - 1, j - 1) && check_valid(i - 2, j - 2)) { // opposite diag
                        if (board[i - 1][j - 1] == player1Sign && board[i - 1][j - 2] == player1Sign) {
                            player1Counter++;
                        }
                    }

                } else if (board[i][j] == player2Sign) {
                    if (check_valid(i, j + 1) && check_valid(i, j + 2)) { // row
                        if (board[i][j + 1] == player2Sign && board[i][j + 2] == player2Sign) {
                            player2Counter++;
                        }
                    }
                    if (check_valid(i + 1, j + 1) && check_valid(i + 2, j + 2)) { // principal diag
                        if (board[i + 1][j + 1] == player2Sign && board[i + 2][j + 2] == player2Sign) {
                            player2Counter++;
                        }
                    }
                    if (check_valid(i + 1, j) && check_valid(i + 2, j)) { // vertical
                        if (board[i + 1][j] == player2Sign && board[i + 2][j] == player2Sign) {
                            player2Counter++;
                        }
                    }
                    if (check_valid(i - 1, j - 1) && check_valid(i - 2, j - 2)) { // opposite diag
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

bool Tic_Tec_Toe::is_draw() {
    return (n_moves == 24 && player1Counter == player2Counter);
}

bool Tic_Tec_Toe::game_is_over () {
    return n_moves >= 24;
}

bool Tic_Tec_Toe::check_valid(int x, int y) {
    return  (x >= 0 && x < 5 && y >= 0 && y < 5) ;
}

/*====================================================================================*/

connect_four_Board::connect_four_Board() {
    n_rows = 6;
    n_cols = 7;
    is4InRow = true;
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

bool connect_four_Board::update_board(int x,int y, char mark) {
    if(y >= 0 && y <= 6){
        x = 5;
        while(valid(x,y) && board[x][y]){
            x--;
        }
        if(x >= 0){
            board[x][y] = toupper(mark);
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

void connect_four_Board::display_board() {
    cout << "\n     0         1         2         3         4         5         6\n";
    cout << "\n+---------+---------+---------+---------+---------+---------+---------+";
    for (int i: {0,1,2,3,4,5}) {
        cout << "\n| ";
        for (int j: {0,1,2,3,4,5,6}) {
            cout << setw(4) << board [i][j] << "    | ";
        }
        cout << "\n+---------+---------+---------+---------+---------+---------+---------+";
    }
    cout << endl;
}

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

bool connect_four_Board::is_draw() {
    return (n_moves == 6*7 && !is_winner());
}

bool connect_four_Board::game_is_over() {
    return n_moves >= 6*7;
}

