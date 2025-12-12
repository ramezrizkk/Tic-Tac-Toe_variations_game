/**
 * @file TTT5x5.h
 * @brief 5x5 Tic-Tac-Toe variant where players aim for most 3-in-a-row sequences.
 *
 * Provides TTT5x5_Board and TTT5x5_UI classes for the 5x5 grid game.
 */

#pragma once

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

const int TTT_SIZE = 5;
const int END_MOVES = 24;

/**
 * @class TTT5x5_Board
 * @brief 5x5 board where players score by creating three-in-a-row sequences.
 *
 * Players alternate placing marks until 24 moves are made. Winner is determined
 * by counting all horizontal, vertical, and diagonal triplets.
 */
class TTT5x5_Board : public Board<char> {
private:
    const char blank_symbol = '.'; ///< Empty cell character

    /**
     * @brief Counts all triplets of player's symbol on board.
     * @param sym Player's symbol ('X' or 'O').
     * @return Total number of triplets found.
     */
    int count_triples(char sym) const;

public:
    /** @brief Constructs an empty 5x5 board. */
    TTT5x5_Board();

    /**
     * @brief Places player's mark on board if valid.
     * @param move Contains coordinates and player's symbol.
     * @return true if move applied, false otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if player has more triplets than opponent at game end.
     * @param player Pointer to player to check.
     * @return true if player wins, false otherwise.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if player has fewer triplets than opponent at game end.
     * @param player Pointer to player to check.
     * @return true if player loses, false otherwise.
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Checks if players have equal triplets at game end.
     * @param player Pointer to player to check.
     * @return true if game is draw, false otherwise.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Determines if 24 moves have been made.
     * @param player Pointer to player to check.
     * @return true if game has ended, false otherwise.
     */
    bool game_is_over(Player<char>* player) override;
};

/**
 * @class TTT5x5_UI
 * @brief User interface for 5x5 Tic-Tac-Toe game.
 */
class TTT5x5_UI : public UI<char> {
public:
    /** @brief Constructs UI with welcome message. */
    TTT5x5_UI();

    /**
     * @brief Creates player of specified type.
     * @param name Player's name.
     * @param symbol Player's symbol ('X' or 'O').
     * @param type Player type (Human or Computer).
     * @return Pointer to new Player instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Gets move coordinates from player.
     * @param player Pointer to current player.
     * @return Pointer to new Move instance.
     */
    Move<char>* get_move(Player<char>* player) override;
};