#include <bits/stdc++.h>
#include "Pyramid_TicTacToe.h"
using namespace std;

int main() {
    cout << "Welcome to Pyramid TicTacToe Game :)\n";
    int choice;
    Player* players[2];
    Board* BOARD = new Pyramid_TicTacToe;
    players[0] = new Player (1, 'x');
    cout << "\nPress (1) if you want to play with computer ( Easy )"
            "\nPress (2) if you want to play with your friend"
            "\nPress (3) if you want to play with AI Player ( HARD )\n";
    cin >> choice;
    if (choice == 2)
        players[1] = new Player (2, 'o');
    else if ( choice == 3 ) {
        players[1] = new AIPlayer('o', BOARD);
    }
    else if (choice==1) {
        players[1] = new RandomPlayer('o',2,5);
    }
    GameManager Pyramid (BOARD, players);
    Pyramid.run();
}
