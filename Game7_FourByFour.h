/**
 * @file 4x4_Classes.h
 * @brief Defines the 4x4 (Tic-Tac-Toe) specific classes that extend the generic board game framework.
 *
 * This file provides:
 * - `Game7_FourByFour_Board`: A specialized board class for the 4x4 Tic-Tac-Toe game.
 * - `Game7_FourByFour_UI`: A user interface class tailored to 4x4 game setup and player interaction.
 */
#ifndef GAME7_FOURBYFOUR_H
#define GAME7_FOURBYFOUR_H

#include <vector>
#include <string>
#include "BoardGame_Classes.h"

using namespace std;

/**
 * @class MoveMoveChar
 * @brief Represents the next move for the player.
 *
 * This class inherits from the generic `Move<char>` class and implements
 * the specific logic required for the next move
 */
class MoveMoveChar : public Move<char> {
    int to_x, to_y;

public:
    MoveMoveChar(int fx, int fy, int tx, int ty, char symbol)
        : Move<char>(fx, fy, symbol), to_x(tx), to_y(ty) {}

    int get_to_x() const { return to_x; }
    int get_to_y() const { return to_y; }
};

/**
 * @class Game7_FourByFour_Board
 * @brief Represents the Four By Four Tic-Tac-Toe game board.
 *
 * This class inherits from the generic `Board<char>` class and implements
 * the specific logic required for the class 4x4 Tic-Tac-Toe Game,
 * including move validation, win/draw detection, and display.
 *
 * @see Board
 */
class Game7_FourByFour_Board : public Board<char> {
public:
    Game7_FourByFour_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    bool in_bounds(int x, int y) const;
    bool has_any_moves(char symbol) const;
};


/**
 * @class Game7_FourByFour_UI
 * @brief User Interface class for the 4x4 (Tic-Tac-Toe) game.
 *
 * Inherits from the generic `UI<char>` base class and provides
 * 4x4 specific functionality for player setup and move input.
 *
 * @see UI
 */
class Game7_FourByFour_UI : public UI<char> {
public:
    Game7_FourByFour_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
    Player<char>** setup_players() override;
};

#endif