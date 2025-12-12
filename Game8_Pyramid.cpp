/**
 * @file Game8_Pyramid.cpp
 * @brief Implementation of Pyramid Tic-Tac-Toe game classes.
 */
#include "Game8_Pyramid.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Game8_Pyramid_Board::Game8_Pyramid_Board()
    : Board<char>(3, 5)
{
    board = {
        {'.', '.', 'X', '.', '.'},
        {'.', 'X', '.', 'O', '.'},
        {'X', '.', 'O', '.', 'O'}
    };
    n_moves = 6;
}

bool Game8_Pyramid_Board::valid_cell(int r, int c) const {
    if (r == 0) return c == 2;
    if (r == 1) return (c >= 1 && c <= 3);
    if (r == 2) return (c >= 0 && c <= 4);
    return false;
}

bool Game8_Pyramid_Board::update_board(Move<char>* m) {
    int r = m->get_x(), c = m->get_y();
    char s = m->get_symbol();

    if (!valid_cell(r, c)) return false;
    if (board[r][c] != '.') return false;

    board[r][c] = s;
    n_moves++;
    return true;
}

bool Game8_Pyramid_Board::is_win(Player<char>* p) {
    char s = p->get_symbol();

    
    for (int i = 0; i <= 2; i++)
        if (board[2][i] == s && board[2][i + 1] == s && board[2][i + 2] == s)
            return true;

    
    if (board[1][1] == s && board[1][2] == s && board[1][3] == s)
        return true;

    
    if (board[0][2] == s && board[1][2] == s && board[2][2] == s)
        return true;

    return false;
}

bool Game8_Pyramid_Board::is_lose(Player<char>* p) {
    char o = (p->get_symbol() == 'X') ? 'O' : 'X';
    Player<char> opp("tmp", o, PlayerType::HUMAN);
    return is_win(&opp);
}

bool Game8_Pyramid_Board::is_draw(Player<char>* p) {
    if (is_win(p) || is_lose(p)) return false;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 5; j++)
            if (valid_cell(i, j) && board[i][j] == '.')
                return false;

    return true;
}

bool Game8_Pyramid_Board::game_is_over(Player<char>* p) {
    return is_win(p) || is_lose(p) || is_draw(p);
}

// =============================
// ========== UI =================
// =============================

Game8_Pyramid_UI::Game8_Pyramid_UI()
    : UI<char>("Welcome to Game 8: Pyramid Tic-Tac-Toe!", 2)
{
    srand((unsigned)time(nullptr));
}

Player<char>* Game8_Pyramid_UI::create_player(string& n, char s, PlayerType t) {
    return new Player<char>(n, s, t);
}

Move<char>* Game8_Pyramid_UI::get_move(Player<char>* p) {
    int r, c;

    if (p->get_type() == PlayerType::HUMAN) {
        cout << "Enter move (row col): ";
        cin >> r >> c;
    }
    else {
        Board<char>* b = p->get_board_ptr();
        vector<pair<int, int>> moves;

        auto matrix = b->get_board_matrix();
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 5; j++)
                if (matrix[i][j] == '.' &&
                    ((i == 0 && j == 2) ||
                        (i == 1 && j >= 1 && j <= 3) ||
                        (i == 2)))
                    moves.push_back({ i,j });

        auto mv = moves[rand() % moves.size()];
        r = mv.first;
        c = mv.second;
        cout << "Computer played: " << r << " " << c << "\n";
    }

    return new Move<char>(r, c, p->get_symbol());
}

Player<char>** Game8_Pyramid_UI::setup_players() {
    Player<char>** P = new Player<char>*[2];
    string name1, name2;
    int t1, t2;

    cout << "Enter Player X name: ";
    getline(cin >> ws, name1);
    cout << "1. Human  2. Computer: ";
    cin >> t1;

    cout << "Enter Player O name: ";
    getline(cin >> ws, name2);
    cout << "1. Human  2. Computer: ";
    cin >> t2;

    P[0] = create_player(name1, 'X', (t1 == 2 ? PlayerType::COMPUTER : PlayerType::HUMAN));
    P[1] = create_player(name2, 'O', (t2 == 2 ? PlayerType::COMPUTER : PlayerType::HUMAN));

    return P;
}