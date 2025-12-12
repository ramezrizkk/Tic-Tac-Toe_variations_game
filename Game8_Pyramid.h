/**
 * @file Game8_Pyramid.h
 * @brief Pyramid-shaped Tic-Tac-Toe game on a 3x5 grid.
 *
 * Provides Game8_Pyramid_Board and Game8_Pyramid_UI classes for pyramid variant.
 */

#ifndef GAME8_PYRAMID_H
#define GAME8_PYRAMID_H

#include <vector>
#include <string>
#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Game8_Pyramid_Board
 * @brief 3x5 pyramid board with predefined valid cells.
 *
 * Valid cells form a pyramid shape: 1 cell in top row, 3 in middle, 5 in base.
 * Win by aligning three marks horizontally, vertically, or diagonally.
 */
class Game8_Pyramid_Board : public Board<char> {
public:
    /** @brief Constructs pyramid board with starting position. */
    Game8_Pyramid_Board();

    /**
     * @brief Checks if coordinates are within pyramid shape.
     * @param r Row index.
     * @param c Column index.
     * @return true if cell is playable, false otherwise.
     */
    bool valid_cell(int r, int c) const;

    /**
     * @brief Places mark on valid empty cell.
     * @param m Move containing coordinates and symbol.
     * @return true if move applied, false otherwise.
     */
    bool update_board(Move<char>* m) override;

    /**
     * @brief Checks if player has three marks in row, column, or diagonal.
     * @param p Pointer to player to check.
     * @return true if player wins, false otherwise.
     */
    bool is_win(Player<char>* p) override;

    /**
     * @brief Checks if opponent has winning condition.
     * @param p Pointer to player to check.
     * @return true if player loses, false otherwise.
     */
    bool is_lose(Player<char>* p) override;

    /**
     * @brief Checks if board is full without winner.
     * @param p Pointer to player to check.
     * @return true if draw, false otherwise.
     */
    bool is_draw(Player<char>* p) override;

    /**
     * @brief Determines if game has ended (win, lose, or draw).
     * @param p Pointer to player to check.
     * @return true if game over, false otherwise.
     */
    bool game_is_over(Player<char>* p) override;
};

/**
 * @class Game8_Pyramid_UI
 * @brief UI for Pyramid Tic-Tac-Toe game.
 *
 * Handles player setup and move input for human and computer players.
 */
class Game8_Pyramid_UI : public UI<char> {
public:
    /** @brief Constructs UI with welcome message. */
    Game8_Pyramid_UI();

    /**
     * @brief Creates player of specified type.
     * @param n Player name.
     * @param s Player symbol ('X' or 'O').
     * @param t Player type (Human or Computer).
     * @return Pointer to new Player instance.
     */
    Player<char>* create_player(string& n, char s, PlayerType t) override;

    /**
     * @brief Gets move from current player.
     * @param p Pointer to current player.
     * @return Pointer to new Move instance.
     */
    Move<char>* get_move(Player<char>* p) override;

    /**
     * @brief Sets up two players for the game.
     * @return Array of two Player pointers.
     */
    Player<char>** setup_players() override;
};
//

#endif
