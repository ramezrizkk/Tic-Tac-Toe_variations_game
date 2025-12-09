#ifndef OBSTACLESTTT_CLASSES_H
#define OBSTACLESTTT_CLASSES_H
#include "BoardGame_Classes.h"

class ObstaclesTTT_Board : public Board<char> {
private:
    char blank_symbol = '.';
    char obstacle_symbol = '#';
    int last_x, last_y;

    void add_random_obstacles(int count);
    bool check_line(int x, int y, int dx, int dy, char symbol);
public:
    ObstaclesTTT_Board();

    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>*) { return false; }
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
};

class ObstaclesTTT_UI : public UI<char> {
public:
    ObstaclesTTT_UI();
    ~ObstaclesTTT_UI() {}

    Player<char>* create_player(string& name, char symbol, PlayerType type);
    Move<char>* get_move(Player<char>* player);
};

#endif
