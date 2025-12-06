#ifndef FOURINROW_CLASSES_H
#define FOURINROW_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

class FourInRow_Board : public Board<char> {
private:
    char blank_symbol = '.';
    int last_x, last_y;

    // Helper method to find empty row in a column
    int find_empty_row(int column);

    // Helper method to check 4 in a direction
    bool check_line(int x, int y, int dx, int dy, char symbol);

public:
    FourInRow_Board();

    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>*) { return false; }
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
};

class FourInRow_UI : public UI<char> {
public:
    FourInRow_UI();
    ~FourInRow_UI() {}

    Player<char>* create_player(string& name, char symbol, PlayerType type);
    Move<char>* get_move(Player<char>* player);
};

#endif