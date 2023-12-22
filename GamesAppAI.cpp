// File name: A3_Task2_3_S24_20221023_20221054_20221098
// Purpose: Games App
// Author(s): افرايم يوسف خميس دميان & رامز رجائي مكرم زكي & عبدالرحمن قدري محمد زينهم احمد
// ID(s): 20221023 & 20221054 & 20221098
// Section: S24
// Date: 17/12/2023

#include <bits/stdc++.h>
#include "GAMESAI.h"

using namespace std;

int main() {
    int play = 1;
    cout << "\n  ^_^  Welcome to our Games App  ^_^\n";
    while (play) {
        Board* pyramidBoard = new Pyramid_TicTacToe;
        Board* fourInRowBoard = new connect_four_Board;
        Board* fiveFiveBoard = new Tic_Tec_Toe;
        Board* XOBoard = new X_O_Board;

        unsigned int gameChoice;
        here:
        cout << "\n==========================================\n\n";
        cout << "To play ( Pyramid_TicTacToe )  Enter (1)\n";
        cout << "To play ( Four-in-a-row )      Enter (2)\n";
        cout << "To play ( 5 * 5 TicTacToe )    Enter (3)\n";
        cout << "To play ( X-O Game )           Enter (4)\n\n";
        cin >> gameChoice;

        if (gameChoice > 4 || gameChoice == 0){
            cout << "\nNot valid !!!! \n"
                    "Choose again from menu \n";
            goto here;
        }

        there:
        cout << "\nPress (1) if you want to play with computer ( Easy )"
                "\nPress (2) if you want to play with your friend"
                "\nPress (3) if you want to play with AI Player ( HARD )\n";
        unsigned int choice;
        cin >> choice;

        if (gameChoice == 4 && choice == 3) {
            cout << "\nSorry, Not Available To This Game Choose Again \n";
            goto there;
        }

        if ( choice> 3 || choice == 0 ){
            cout << "\nNot valid !!!! \n"
                    "Choose again \n";
            goto there;
        }

        Player *players[2];
        players[0] = new Player(1, 'x');

        if (choice == 2) {
                players[1] = new Player(2, 'o');
        }
        else if (choice == 1) {
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
        else {
            if (gameChoice == 1) {

                players[1] = new AIPlayer ('o', pyramidBoard);
            }
            else if (gameChoice == 2) {
                players[1] = new AIPlayer ('o', fourInRowBoard);
            }
            else if (gameChoice == 3) {
                players[1] = new AIPlayer ('o', fiveFiveBoard);
            }
        }

        if (gameChoice == 1) {
            delete XOBoard;
            delete fourInRowBoard;
            delete fiveFiveBoard;
            GameManager PyramidTicTacToe (pyramidBoard, players);
            PyramidTicTacToe.run();
        }
        else if (gameChoice == 2) {
            delete XOBoard;
            delete pyramidBoard;
            delete fiveFiveBoard;
            GameManager fourInRow (fourInRowBoard, players);
            fourInRow.run();

        }
        else if (gameChoice == 3) {
            delete XOBoard;
            delete fourInRowBoard;
            delete pyramidBoard;
            GameManager ticTecToe (fiveFiveBoard, players);
            ticTecToe.run();

        }
        else if (gameChoice == 4) {
            delete pyramidBoard;
            delete fourInRowBoard;
            delete fiveFiveBoard;
            GameManager x_o_game (XOBoard, players);
            x_o_game.run();
        }

        cout << "\nIf you want to quit our Games App enter 0 \n"
                "If you want to continue press any number else \n";
        cin >> play;
        cout << endl;
    }
    cout << "GoodBye ^_^\n";
}

