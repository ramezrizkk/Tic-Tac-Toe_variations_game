/**
 * @file TTT5x5.cpp
 * @brief Implementation of 5x5 Tic-Tac-Toe game classes.
 */
#include "TTT5x5.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cctype>    // for toupper

using namespace std;

// ========= TTT5x5_Board Implementation =============================================================

TTT5x5_Board::TTT5x5_Board() : Board(TTT_SIZE, TTT_SIZE)
{
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            board[row][column] = blank_symbol;
        }
    }
}

bool TTT5x5_Board::update_board(Move<char>* move)
{
    int x = move->get_x() ;
    int y = move->get_y() ;
    char mark = move->get_symbol();

    // Validate move and apply if valid
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || mark == 0)) {

        if (mark == 0) { // Undo move
            n_moves--;
            board[x][y] = blank_symbol;
        }
        else {         // Apply move
            n_moves++;
            board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

int TTT5x5_Board::count_triples(char sym) const
{
    int count = 0;

    auto check_triple = [&](int r, int c, int dr, int dc) {
        return (board[r][c] == sym &&
                board[r + dr][c + dc] == sym &&
                board[r + 2 * dr][c + 2 * dc] == sym);
    };

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c <= columns - 3; ++c) {
            if (check_triple(r, c, 0, 1)) {
                count++;
            }
        }
    }

    for (int r = 0; r <= rows - 3; ++r) {
        for (int c = 0; c < columns; ++c) {
            if (check_triple(r, c, 1, 0)) {
                count++;
            }
        }
    }

    for (int r = 0; r <= rows - 3; ++r) {
        for (int c = 0; c <= columns - 3; ++c) {
            if (check_triple(r, c, 1, 1)) {
                count++;
            }
        }
    }

    for (int r = 0; r <= rows - 3; ++r) {
        for (int c = 2; c < columns; ++c) {
            if (check_triple(r, c, 1, -1)) {
                count++;
            }
        }
    }

    return count;
}

bool TTT5x5_Board::game_is_over(Player<char>* player) {

    return n_moves >= END_MOVES;
}

bool TTT5x5_Board::is_win(Player<char>* player) {
    if (!game_is_over(player)) return false;


    char sym = player->get_symbol();
    char oppSym = (sym == 'X' ? 'O' : 'X');

    int myCount = count_triples(sym);
    int oppCount = count_triples(oppSym);

    return myCount > oppCount;
}

bool TTT5x5_Board::is_lose(Player<char>* player) {
    if (!game_is_over(player)) return false;

    char sym = player->get_symbol();
    char oppSym = (sym == 'X' ? 'O' : 'X');

    int myCount = count_triples(sym);
    int oppCount = count_triples(oppSym);


    return oppCount > myCount;
}

bool TTT5x5_Board::is_draw(Player<char>* player) {
    if (!game_is_over(player)) return false;

    char sym = player->get_symbol();
    char oppSym = (sym == 'X' ? 'O' : 'X');

    int myCount = count_triples(sym);
    int oppCount = count_triples(oppSym);


    return myCount == oppCount;
}

// ================= TTT5x5_UI Implementation =========================================

TTT5x5_UI::TTT5x5_UI() : UI<char>("Welcome to 5x5 Tic-Tac-Toe Game", 3) {}

Player<char>* TTT5x5_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* TTT5x5_UI::get_move(Player<char>* player) {
    int x , y ;
    char mark = player->get_symbol();
    Board<char>* boardPtr = player->get_board_ptr();

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease " << player->get_name() << " enter x and y (0 to " << TTT_SIZE-1 << ")\n> ";
        cin >> x >> y;
    }
    else {

        if (boardPtr->get_n_moves() >= boardPtr->get_rows() * boardPtr->get_columns()) {
            return nullptr;
        }

        int rows = boardPtr->get_rows();
        int cols = boardPtr->get_columns();

        do {
            x = rand() % rows;
            y = rand() % cols;
        } while (boardPtr->get_cell(x, y) != '.');

    }

    return new Move<char>(x, y, mark);
}
