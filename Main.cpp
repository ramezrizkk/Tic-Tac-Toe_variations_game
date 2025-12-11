#include <iostream>
#include "BoardGame_Classes.h"
#include "NumericalTTT_Classes.h"
#include "Game7_FourByFour.h"
#include "SUS_Classes.h"
#include "InfinityXO_Classes.h"
#include "TTT5x5.h"
#include "MisereXO_Classes.h"
#include "FourInRow_Classes.h"
#include "ObstaclesTTT_Classes.h"
#include "wordTTT.h"
#include "Diamond_Classes.h"
#include "Game8_Pyramid.h"
#include "Ultimate_TTT_Board.h"
#include "Game13_MemoryTTT.h"
using namespace std;

int main() {
    while (true) {
        cout << "=====================================\n";
        cout << "          FCAI BOARD GAMES           \n";
        cout << "=====================================\n";
        cout << "1. SUS Tic-Tac-Toe\n";
        cout << "2. Four In A Row\n";
        cout << "3. 5x5 Tic-Tac-Toe\n";
        cout << "4. Word Tic - Tac - Toe\n";
        cout << "5. Misere Tic-Tac-Toe\n";
        cout << "6. Diamond Tic-Tac-Toe\n";
        cout << "7. 4x4 Moving Tokens\n";
        cout << "8. Pyramid Tic-Tac-Toe\n";
        cout << "9. Numerical Tic-Tac-Toe\n";
        cout << "10. Obstacles Tic-Tac-Toe\n";
        cout << "11. Infinity Tic-Tac-Toe\n";
        cout << "12. Ultimate Tic-Tac-Toe\n";
        cout << "13. Memory Tic-Tac-Toe\n";
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

        // ---------------- 4 in a row ----------------
        else if (choice == 2) {
            cout << "\n--- Starting Four-in-a-Row Game ---\n";
            board_char = new FourInRow_Board();
            ui_char = new FourInRow_UI();
            players_char = ui_char->setup_players();
            GameManager<char> gm(board_char, players_char, ui_char);
            gm.run();
        }

        // ---------------- 5x5 Tic-Tac-Toe ----------------
        else if (choice == 3) {
            cout << "\n--- Starting 5x5 Tic Tac Toe Game ---\n";
            board_char = new TTT5x5_Board();
            ui_char = new TTT5x5_UI();
            players_char = ui_char->setup_players();
            GameManager<char> gm(board_char, players_char, ui_char);
            gm.run();
        }

        // ---------------- Word Tic-Tac-Toe ----------------
        if (choice == 4) {
            cout << "\n--- Starting Word Tic-Tac-Toe Game ---\n";
            board_char = new ThreeWord_Board();
            ui_char = new WordGame_UI();
            players_char = ui_char->setup_players();
            GameManager<char> gm(board_char, players_char, ui_char);
            gm.run();
        }

        // ---------------- Misère Tic-Tac-Toe ----------------
        if (choice == 5) {
            cout << "\n--- Starting Misere Tic-Tac-Toe Game ---\n";
            board_char = new MisereXO_Board();
            ui_char = new MisereXO_UI();
            players_char = ui_char->setup_players();
            GameManager<char> gm(board_char, players_char, ui_char);
            gm.run();
        }

        // ---------------- Diamond Tic-Tac-Toe ----------------
        if (choice == 6) {
            cout << "\n--- Starting Diamond Tic-Tac-Toe Game ---\n";
            board_char = new gem_grid();
            ui_char = new gem_interaction();
            players_char = ui_char->setup_players();
            GameManager<char> gm(board_char, players_char, ui_char);
            gm.run();
        }

        // ------------------- 4x4 Moving Tokens -------------------
        else if (choice == 7) {
            cout << "\n--- Starting 4x4 Moving Tokens Game ---\n";
            board_char = new Game7_FourByFour_Board();
            ui_char = new Game7_FourByFour_UI();
            players_char = ui_char->setup_players();
            GameManager<char> gm(board_char, players_char, ui_char);
            gm.run();
        }

        // ---------------- Diamond Tic-Tac-Toe ----------------
        if (choice == 8) {
            cout << "\n--- Starting Pyramid Tic-Tac-Toe Game ---\n";
            board_char = new Game8_Pyramid_Board();
            ui_char = new Game8_Pyramid_UI();
            players_char = ui_char->setup_players();
            GameManager<char> gm(board_char, players_char, ui_char);
            gm.run();
        }

        // ---------------- Numerical Tic-Tac-Toe ----------------
        else if (choice == 9) {
            cout << "\n--- Starting Numerical Tic Tac Toe Game ---\n";
            board_int = new NumericalTTT_Board();
            ui_int = new NumericalTTT_UI();
            players_int = ui_int->setup_players();
            GameManager<int> gm(board_int, players_int, ui_int);
            gm.run();
        }

        if (choice == 10) {
            cout << "\n--- Starting Obstacles Tic-Tac-Toe Game ---\n";
            board_char = new ObstaclesTTT_Board();
            ui_char = new ObstaclesTTT_UI();
            players_char = ui_char->setup_players();
            GameManager<char> gm(board_char, players_char, ui_char);
            gm.run();
        }

        // ------------------- Infinity Tic-Tac-Toe -------------------
        else if (choice == 11) {
            cout << "\n--- Starting Infinity XO Game ---\n";
            board_char = new InfinityXO_Board();
            ui_char = new InfinityXO_UI();
            players_char = ui_char->setup_players();
            GameManager<char> gm(board_char, players_char, ui_char);
            gm.run();
        }

        // ------------------- Ultimate Tic-Tac-Toe -------------------
        else if (choice == 12) {
            cout << "\n--- Starting Ultimate Tic-Tac-Toe Game ---\n";
            board_char = new SuperGrid();
            ui_char = new MegaGameInterface();
            players_char = ui_char->setup_players();
            GameManager<char> gm(board_char, players_char, ui_char);
            gm.run();
        }

        // ------------------- Memory Tic-Tac-Toe -------------------
        else if (choice == 13) {
            cout << "\n--- Starting Memory Tic-Tac-Toe ---\n";
            board_char = new GhostBoard();
            ui_char = new GhostUI();
            players_char = ui_char->setup_players();
            GameManager<char> gm(board_char, players_char, ui_char);
            gm.run();
        }

        // ---------- Cleanup ----------
        delete board_char;
        delete board_int;

        if (players_char) { delete players_char[0]; delete players_char[1]; delete[] players_char; }
        if (players_int) { delete players_int[0];  delete players_int[1];  delete[] players_int; }

        delete ui_char;
        delete ui_int;
    }
}