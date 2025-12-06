#include "Game7_FourByFour.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <tuple>

using namespace std;

Game7_FourByFour_Board::Game7_FourByFour_Board() : Board<char>(4, 4) {
    for (auto& r : board)
        for (auto& c : r)
            c = '.';

    board[0][0] = board[0][1] = board[1][0] = board[1][1] = 'X';
    board[2][2] = board[2][3] = board[3][2] = board[3][3] = 'O';

    n_moves = 8;
}

bool Game7_FourByFour_Board::in_bounds(int x, int y) const {
    return x >= 0 && x < 4 && y >= 0 && y < 4;
}

bool Game7_FourByFour_Board::update_board(Move<char>* m) {
    MoveMoveChar* mv = static_cast<MoveMoveChar*>(m);

    int fx = mv->get_x(), fy = mv->get_y();
    int tx = mv->get_to_x(), ty = mv->get_to_y();
    char s = mv->get_symbol();

    if (!in_bounds(fx, fy) || !in_bounds(tx, ty))
        return false;

    if (board[fx][fy] != s || board[tx][ty] != '.')
        return false;

    int dx = abs(tx - fx), dy = abs(ty - fy);

    if (!((dx == 1 && dy == 0) || (dx == 0 && dy == 1)))
        return false;

    board[fx][fy] = '.';
    board[tx][ty] = s;
    n_moves++;

    return true;
}

bool Game7_FourByFour_Board::is_win(Player<char>* p) {
    char s = p->get_symbol();

    
    for (int i = 0; i < 4; i++)
        for (int j = 0; j <= 1; j++)
            if (board[i][j] == s &&
                board[i][j + 1] == s &&
                board[i][j + 2] == s)
                return true;

    
    for (int j = 0; j < 4; j++)
        for (int i = 0; i <= 1; i++)
            if (board[i][j] == s &&
                board[i + 1][j] == s &&
                board[i + 2][j] == s)
                return true;

    
    for (int i = 0; i <= 1; i++)
        for (int j = 0; j <= 1; j++)
            if (board[i][j] == s &&
                board[i + 1][j + 1] == s &&
                board[i + 2][j + 2] == s)
                return true;

    
    for (int i = 0; i <= 1; i++)
        for (int j = 2; j <= 3; j++)
            if (board[i][j] == s &&
                board[i + 1][j - 1] == s &&
                board[i + 2][j - 2] == s)
                return true;

    return false;
}

bool Game7_FourByFour_Board::is_lose(Player<char>* p) {
    char o = (p->get_symbol() == 'X') ? 'O' : 'X';

    Player<char> temp("tmp", o, PlayerType::HUMAN);
    return is_win(&temp);
}

bool Game7_FourByFour_Board::has_any_moves(char s) const {
    const int dx[4] = { 1, -1, 0, 0 };
    const int dy[4] = { 0, 0, 1, -1 };

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (board[i][j] == s)
                for (int k = 0; k < 4; k++) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if (in_bounds(ni, nj) && board[ni][nj] == '.')
                        return true;
                }

    return false;
}

bool Game7_FourByFour_Board::is_draw(Player<char>* p) {
    if (is_win(p) || is_lose(p))
        return false;

    return !has_any_moves('X') && !has_any_moves('O');
}

bool Game7_FourByFour_Board::game_is_over(Player<char>* p) {
    return is_win(p) || is_lose(p) || is_draw(p);
}

Game7_FourByFour_UI::Game7_FourByFour_UI()
    : UI<char>("Welcome toascii FCAI 4x4 Moving-Tokens Game", 2) {
    srand((unsigned)time(nullptr));
}

Player<char>* Game7_FourByFour_UI::create_player(string& name, char s, PlayerType t) {
    return new Player<char>(name, s, t);
}

Move<char>* Game7_FourByFour_UI::get_move(Player<char>* p) {
    int fx, fy, tx, ty;

    if (p->get_type() == PlayerType::HUMAN) {
        cout << "Enter move (fromX fromY toX toY): ";
        cin >> fx >> fy >> tx >> ty;
    }
    else {
        auto* b = static_cast<Game7_FourByFour_Board*>(p->get_board_ptr());

        vector<tuple<int, int, int, int>> cand;
        const int dx[4] = { 1, -1, 0, 0 };
        const int dy[4] = { 0, 0, 1, -1 };

        auto M = b->get_board_matrix();

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (M[i][j] == p->get_symbol())
                    for (int k = 0; k < 4; k++) {
                        int ni = i + dx[k], nj = j + dy[k];
                        if (b->in_bounds(ni, nj) && M[ni][nj] == '.')
                            cand.push_back({ i, j, ni, nj });
                    }

        if (!cand.empty()) {
            auto pick = cand[rand() % cand.size()];
            fx = get<0>(pick);
            fy = get<1>(pick);
            tx = get<2>(pick);
            ty = get<3>(pick);
        }
        else fx = fy = tx = ty = 0;
    }

    return new MoveMoveChar(fx, fy, tx, ty, p->get_symbol());
}

Player<char>** Game7_FourByFour_UI::setup_players() {
    Player<char>** p = new Player<char>*[2];

    string n1, n2;
    int t1, t2;

    cout << "Enter Player X name: ";
    getline(cin >> ws, n1);
    cout << "1. Human  2. Computer: ";
    cin >> t1;

    cout << "Enter Player O name: ";
    getline(cin >> ws, n2);
    cout << "1. Human  2. Computer: ";
    cin >> t2;

    p[0] = create_player(n1, 'X', (t1 == 2 ? PlayerType::COMPUTER : PlayerType::HUMAN));
    p[1] = create_player(n2, 'O', (t2 == 2 ? PlayerType::COMPUTER : PlayerType::HUMAN));

    return p;
}