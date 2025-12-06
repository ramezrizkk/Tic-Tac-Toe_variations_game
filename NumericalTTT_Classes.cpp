/**
 * @file NumericalTTT_Classes.cpp
 * @brief Implementation of the Numerical Tic-Tac-Toe (Game 9) board and UI classes.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "NumericalTTT_Classes.h"

using namespace std;

//--------------------------------------- NumericalTTT_Board Implementation

NumericalTTT_Board::NumericalTTT_Board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
    for (int i = 0; i < 10; ++i)
        usedNumbers[i] = false;
    n_moves = 0;
}

bool NumericalTTT_Board::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int val = move->get_symbol();

    // Check boundaries
    if (x < 0 || x >= rows || y < 0 || y >= columns) return false;

    // Check if cell is empty and number valid
    if (board[x][y] != blank_symbol || val < 1 || val > 9 || usedNumbers[val]) return false;

    board[x][y] = val;
    usedNumbers[val] = true;
    n_moves++;
    return true;
}

bool NumericalTTT_Board::is_win(Player<int>* player) {
    // Winning condition: any row, column or diagonal sums to 15
    for (int i = 0; i < 3; ++i) {
        int rowSum = board[i][0] + board[i][1] + board[i][2];
        int colSum = board[0][i] + board[1][i] + board[2][i];
        if ((rowSum == 15 && board[i][0] && board[i][1] && board[i][2]) ||
            (colSum == 15 && board[0][i] && board[1][i] && board[2][i]))
            return true;
    }

    int diag1 = board[0][0] + board[1][1] + board[2][2];
    int diag2 = board[0][2] + board[1][1] + board[2][0];

    if ((diag1 == 15 && board[0][0] && board[1][1] && board[2][2]) ||
        (diag2 == 15 && board[0][2] && board[1][1] && board[2][0]))
        return true;

    return false;
}

bool NumericalTTT_Board::is_draw(Player<int>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool NumericalTTT_Board::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- NumericalTTT_UI Implementation

NumericalTTT_UI::NumericalTTT_UI() : UI<int>("Welcome to FCAI Numerical Tic-Tac-Toe Game", 3) {}

Player<int>* NumericalTTT_UI::create_player(string& name, int symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name;
    if (symbol == 1)
        cout << " (Odd numbers: 1,3,5,7,9)";
    else
        cout << " (Even numbers: 2,4,6,8)";
    cout << endl;

    return new Player<int>(name, symbol, type);
}

Move<int>* NumericalTTT_UI::get_move(Player<int>* player) {
    int x, y, val;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move (row col number): ";
        cin >> x >> y >> val;
    }
    else {
        // Computer: random valid move
        srand((unsigned)time(nullptr));
        NumericalTTT_Board* b = dynamic_cast<NumericalTTT_Board*>(player->get_board_ptr());
        vector<pair<int, int>> empty;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (b->get_board_matrix()[i][j] == 0)
                    empty.push_back({ i,j });

        vector<int> possible;
        if (player->get_symbol() == 1) { // odd
            for (int n : {1, 3, 5, 7, 9})
                if (n <= 9) possible.push_back(n);
        }
        else { // even
            for (int n : {2, 4, 6, 8})
                if (n <= 9) possible.push_back(n);
        }

        if (!empty.empty() && !possible.empty()) {
            auto cell = empty[rand() % empty.size()];
            val = possible[rand() % possible.size()];
            x = cell.first;
            y = cell.second;
        }
        else {
            x = y = 0;
            val = 1;
        }
        //cout << player->get_name() << " (computer) plays (" << x << "," << y << ") = " << val << endl;
    }

    return new Move<int>(x, y, val);
}

Player<int>** NumericalTTT_UI::setup_players() {
    Player<int>** players = new Player<int>*[2];

    cout << "\nSetting up players for Numerical Tic-Tac-Toe:\n";

    string n1, n2;
    cout << "Enter Player 1 name (Odd numbers): ";
    getline(cin >> ws, n1);
    cout << "Choose Player 1 type: 1. Human  2. Computer: ";
    int c1; cin >> c1;
    PlayerType t1 = (c1 == 2) ? PlayerType::COMPUTER : PlayerType::HUMAN;
    players[0] = create_player(n1, 1, t1);

    cout << "\nEnter Player 2 name (Even numbers): ";
    getline(cin >> ws, n2);
    cout << "Choose Player 2 type: 1. Human  2. Computer: ";
    int c2; cin >> c2;
    PlayerType t2 = (c2 == 2) ? PlayerType::COMPUTER : PlayerType::HUMAN;
    players[1] = create_player(n2, 2, t2);

    return players;
}