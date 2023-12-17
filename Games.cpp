// File name: A3_Task2_3_S24_20221023_20221054_20221098
// Purpose: Games App
// Author(s): افرايم يوسف خميس دميان & رامز رجائي مكرم زكي & عبدالرحمن قدري محمد زينهم احمد
// ID(s): 20221023 & 20221054 & 20221098
// Section: S24
// Date: 17/12/2023

#include <bits/stdc++.h>
#include "gamesApp.h"

using namespace std;

int main() {
    int play;
    cout << "\n  ^_^  Welcome to our Games App  ^_^\n";
    while (play) {
        unsigned int gameChoice;
        here:
        cout << "\n==========================================\n\n";
        cout << "To play ( Pyramid_TicTacToe )  Enter (1)\n";
        cout << "To play ( Four-in-a-row )      Enter (2)\n";
        cout << "To play ( 5 * 5 TicTacToe )    Enter (3)\n";
        cout << "To play ( X-O Game )           Enter (4)\n\n";
        cin >> gameChoice;

        if (gameChoice > 4){
            cout << "\nNot valid !!!! \n"
                    "Choose again from menu \n";
            goto here;
        }

        cout << "\nPress (1) if you want to play with computer:"
                "\nPress (2) if you want to play with your friend:\n";

        int choice;
        cin >> choice;
        Player *players[2];
        players[0] = new Player(1, 'x');

        if (choice != 1) {
                players[1] = new Player(2, 'o');
        }
        else {
            if (gameChoice == 1) {
                players[1] = new RandomPlayer('o', 3, 5);
            } else if (gameChoice == 2) {
                players[1] = new RandomPlayer('o', 6, 7);
            } else if (gameChoice == 3) {
                players[1] = new RandomPlayer('o', 5, 5);
            } else if (gameChoice == 4) {
                players[1] = new RandomPlayer('o', 3, 3);
            }
        }
        if (gameChoice == 1) {
            GameManager PyramidTicTacToe (new Pyramid_TicTacToe, players);
            PyramidTicTacToe.run();
        }
        else if (gameChoice == 2) {
            GameManager fourInRow (new connect_four_Board, players);
            fourInRow.run();
        }
        else if (gameChoice == 3) {
            GameManager ticTecToe (new Tic_Tec_Toe, players);
            ticTecToe.run();
        }
        else if (gameChoice == 4) {
            GameManager x_o_game (new X_O_Board, players);
            x_o_game.run();
        }

        cout << "\nIf you want to quit our Games App enter 0 \n"
                "If you want to continue press any number \n";
        cin >> play;
        cout << endl;
    }
    cout << "GoodBye ^_^\n";
}