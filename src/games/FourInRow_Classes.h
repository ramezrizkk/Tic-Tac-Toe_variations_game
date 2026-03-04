/**
 * @file FourInRow_Classes.h
 * @brief Four-in-a-Row game implementation (Connect Four style).
 *
 * Provides FourInRow_Board and FourInRow_UI classes for the 6x7 grid game.
 */

#ifndef FOURINROW_CLASSES_H
#define FOURINROW_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class FourInRow_Board
 * @brief 6x7 board for Four-in-a-Row game with gravity-based placement.
 *
 * Players drop marks in columns, which fall to the lowest available row.
 * Win by connecting four marks horizontally, vertically, or diagonally.
 */
class FourInRow_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Empty cell character
    int last_x, last_y;      ///< Coordinates of the last move

    /**
     * @brief Finds the lowest empty row in a given column.
     * @param column The column index to check.
     * @return Row index of lowest empty cell, or -1 if column is full.
     */
    int find_empty_row(int column);

    /**
     * @brief Checks for a line of 4+ matching symbols in a direction.
     * @param x Starting row coordinate.
     * @param y Starting column coordinate.
     * @param dx Row direction increment (-1, 0, or 1).
     * @param dy Column direction increment (-1, 0, or 1).
     * @param symbol The player's symbol to check.
     * @return true if line of 4+ found, false otherwise.
     */
    bool check_line(int x, int y, int dx, int dy, char symbol);

public:
    /** @brief Constructs a 6x7 Four-in-a-Row board. */
    FourInRow_Board();

    /**
     * @brief Drops a mark into the specified column.
     * @param move Contains column and player's symbol (x coordinate ignored).
     * @return true if move is valid and applied, false otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if player has four in a row from their last move.
     * @param player Pointer to the player to check.
     * @return true if player has won, false otherwise.
     */
    bool is_win(Player<char>* player) override;

    /** @brief Four-in-a-Row uses is_lose to check opponent win. */
    bool is_lose(Player<char>*) override { return false; }

    /**
     * @brief Checks if board is completely filled without a winner.
     * @param player Pointer to the player to check.
     * @return true if game is draw, false otherwise.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Determines if game is over (win or draw).
     * @param player Pointer to the player to check.
     * @return true if game has ended, false otherwise.
     */
    bool game_is_over(Player<char>* player) override;
};

/**
 * @class FourInRow_UI
 * @brief User interface for Four-in-a-Row game.
 *
 * Handles player setup and move input for humans and computer players.
 */
class FourInRow_UI : public UI<char> {
public:
    /** @brief Constructs Four-in-a-Row UI with welcome message. */
    FourInRow_UI();

    /** @brief Destructor for FourInRow_UI. */
    ~FourInRow_UI() {}

    /**
     * @brief Creates a player of specified type.
     * @param name Player's name.
     * @param symbol Player's symbol ('X' or 'O').
     * @param type Player type (Human or Computer).
     * @return Pointer to new Player instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Gets column choice from player (human or computer).
     * @param player Pointer to current player.
     * @return Pointer to new Move instance (row set to 0, will be updated by board).
     */
    Move<char>* get_move(Player<char>* player) override;
};

#endif