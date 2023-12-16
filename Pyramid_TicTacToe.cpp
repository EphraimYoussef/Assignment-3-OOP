// header

class Pyramid_TicTacToe : public Board {
public:
    Pyramid_TicTacToe(); // done
    bool update_board (int x, int y, char mark); // done;
    void display_board(); // done
    bool is_winner(); // done
    bool is_draw(); // done
    bool game_is_over(); // done
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// implement

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
