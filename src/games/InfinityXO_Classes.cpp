#include "InfinityXO_Classes.h"
//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

//--------------------------------------- X_O_Board Implementation

InfinityXO_Board::InfinityXO_Board() : Board(3, 3) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool InfinityXO_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate move and apply if valid
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || mark == 0)) {
        if (toupper(mark) == 'X') {
            if (playerX_history.size() == 3) {
                board[playerX_history.front().first][playerX_history.front().second] = blank_symbol;
                playerX_history.pop();
            }
            //no need to trace the number of moves
            if (mark == 0) { // Undo move  // will need more work if we wann use it for example to edit the palyer history
                //n_moves--;
                board[x][y] = blank_symbol;
            }
            else {         // Apply move
                //n_moves++; 
                board[x][y] = 'X';
                playerX_history.push({ x, y });
            }
            return true;
        }
        else if (toupper(mark) == 'O') {
            if (playerO_history.size() == 3) {
                board[playerO_history.front().first][playerO_history.front().second] = blank_symbol;
                playerO_history.pop();
            }
            //no need to trace the number of moves because there's no draw, the maximum n_moves is 6
            if (mark == 0) { // Undo move  // will need more work if we wann use it for example to edit the palyer history
                //n_moves--;
                board[x][y] = blank_symbol;
            }
            else {         // Apply move
                //n_moves++; 
                board[x][y] = 'O';
                playerO_history.push({ x, y });
            }
            return true;
        }
    }

    return false;
}

bool InfinityXO_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };

    // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        if ((all_equal(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym) ||
            (all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym))
            return true;
    }

    // Check diagonals
    if ((all_equal(board[0][0], board[1][1], board[2][2]) && board[1][1] == sym) ||
        (all_equal(board[0][2], board[1][1], board[2][0]) && board[1][1] == sym))
        return true;

    return false;
}
bool InfinityXO_Board::game_is_over(Player<char>* player) {
    return is_win(player);
}

//--------------------------------------- InfinityXO_UI Implementation

InfinityXO_UI::InfinityXO_UI() : UI<char>("Weclome to FCAI Infinity Tic-Tac-Toe Game", 3) {}


Player<char>* InfinityXO_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* InfinityXO_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease " << player->get_name() << " enter x and y (0 to 2)\n> ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}
// no need to edit the setup for the players