#ifndef GAME8_PYRAMID_H
#define GAME8_PYRAMID_H

#include <vector>
#include <string>
#include "BoardGame_Classes.h"
using namespace std;

class Game8_Pyramid_Board : public Board<char> {
public:
    Game8_Pyramid_Board();
    bool valid_cell(int r, int c) const;
    bool update_board(Move<char>* m) override;
    bool is_win(Player<char>* p) override;
    bool is_lose(Player<char>* p) override;
    bool is_draw(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;
};

class Game8_Pyramid_UI : public UI<char> {
public:
    Game8_Pyramid_UI();
    Player<char>* create_player(string& n, char s, PlayerType t) override;
    Move<char>* get_move(Player<char>* p) override;
    Player<char>** setup_players() override;
};

#endif