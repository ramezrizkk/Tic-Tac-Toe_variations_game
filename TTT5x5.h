#pragma once

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

const int TTT_SIZE = 5;
const int END_MOVES = 24;

class TTT5x5_Board : public Board<char> {
private:
    const char blank_symbol = '.';


    int count_triples(char sym) const;

public:
    TTT5x5_Board();

    bool update_board(Move<char>* move) override;


    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

// ----------------------------------------------------


class TTT5x5_UI : public UI<char> {


public:
    // Constructor
    TTT5x5_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};