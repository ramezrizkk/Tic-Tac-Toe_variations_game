#include <iostream>
#include "BoardGame_Classes.h"
#include "NumericalTTT_Classes.h"
#include "Game7_FourByFour.h"
#include "SUS_Classes.h"
#include "InfinityXO_Classes.h"
#include "TTT5x5.h"
#include "MisereXO_Classes.h"

using namespace std;

int main() {
    while (true) {
        cout << "=====================================\n";
        cout << "          FCAI BOARD GAMES           \n";
        cout << "=====================================\n";
        cout << "1. SUS Tic-Tac-Toe\n";
        cout << "2. 5x5 Tic-Tac-Toe\n";
        cout << "3. Misere Tic-Tac-Toe\n";
        cout << "4. Numerical Tic-Tac-Toe\n";
        cout << "5. 4x4 Moving Tokens\n";
        cout << "6. Infinity Tic-Tac-Toe\n";

        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 0) return 0;

        Board<char>* board_char = nullptr;
        Board<int>* board_int = nullptr;
        UI<char>* ui_char = nullptr;
        UI<int>* ui_int = nullptr;
        Player<char>** players_char = nullptr;
        Player<int>** players_int = nullptr;

        //// ------------------- X-O Game -------------------
        //if (choice == 1) {
        //    board_char = new X_O_Board();
        //    ui_char = new XO_UI();
        //    players_char = ui_char->setup_players();
        //    GameManager<char> gm(board_char, players_char, ui_char);
        //    gm.run();
        //}
        
        // ---------------- SUS Tic-Tac-Toe ----------------
        if (choice == 1) {
            cout << "\n--- Starting SUS Game ---\n";
            board_char = new SUS_Board();
            ui_char = new SUS_UI();
            players_char = ui_char->setup_players();
            GameManager<char> gm(board_char, players_char, ui_char);
            gm.run();
        }

        // ---------------- 5x5 Tic-Tac-Toe ----------------
        else if (choice == 2) {
            cout << "\n--- Starting 5x5 Tic Tac Toe Game ---\n";
            board_char = new TTT5x5_Board();
            ui_char = new TTT5x5_UI();
            players_char = ui_char->setup_players();
            GameManager<char> gm(board_char, players_char, ui_char);
            gm.run();
        }

        // ---------------- Misère Tic-Tac-Toe ----------------
        if (choice == 3) {
            cout << "\n--- Starting Misere Tic-Tac-Toe Game ---\n";
            board_char = new MisereXO_Board();
            ui_char = new MisereXO_UI();
            players_char = ui_char->setup_players();
            GameManager<char> gm(board_char, players_char, ui_char);
            gm.run();
        }

        // ---------------- Numerical Tic-Tac-Toe ----------------
        else if (choice == 4) {
            cout << "\n--- Starting Numerical Tic Tac Toe Game ---\n";
            board_int = new NumericalTTT_Board();
            ui_int = new NumericalTTT_UI();
            players_int = ui_int->setup_players();
            GameManager<int> gm(board_int, players_int, ui_int);
            gm.run();
        }

        // ------------------- 4x4 Moving Tokens -------------------
        else if (choice == 5) {
            cout << "\n--- Starting 4x4 Moving Tokens Game ---\n";
            board_char = new Game7_FourByFour_Board();
            ui_char = new Game7_FourByFour_UI();
            players_char = ui_char->setup_players();
            GameManager<char> gm(board_char, players_char, ui_char);
            gm.run();
        }

        // ------------------- Infinity Tic-Tac-Toe -------------------
        else if (choice == 6) {
            cout << "\n--- Starting Infinity XO Game ---\n";
            board_char = new InfinityXO_Board();
            ui_char = new InfinityXO_UI();
            players_char = ui_char->setup_players();
            GameManager<char> gm(board_char, players_char, ui_char);
            gm.run();
        }
        // ------------------- Game 8 -------------------
        /*else if (choice == 8) {
            cout << "\n--- Starting Game 8 (Pyramid Tic-Tac-Toe) ---\n";
            board_char = new Game8_Pyramid_Board();
            ui_char = new Game8_Pyramid_UI();
            players_char = ui_char->setup_players();
            GameManager<char> gm(board_char, players_char, ui_char);
            gm.run();
            }
        */

        // ---------- Cleanup ----------
        delete board_char;
        delete board_int;

        if (players_char) { delete players_char[0]; delete players_char[1]; delete[] players_char; }
        if (players_int) { delete players_int[0];  delete players_int[1];  delete[] players_int; }

        delete ui_char;
        delete ui_int;
    }
}