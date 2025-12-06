/**
 * @file NumericalTTT_Classes.h
 * @brief Defines the Numerical Tic-Tac-Toe (Game 9) specific classes that extend the generic board game framework.
 *
 * This file provides:
 * - `NumericalTTT_Board`: A specialized board class for the Numerical Tic-Tac-Toe game.
 * - `NumericalTTT_UI`: A user interface class tailored to Numerical Tic-Tac-Toe setup and player interaction.
 */

#ifndef NUMERICALTTT_CLASSES_H
#define NUMERICALTTT_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class NumericalTTT_Board
 * @brief Represents the Numerical Tic-Tac-Toe game board.
 *
 * This class inherits from the generic `Board<int>` class and implements
 * the specific logic required for the Numerical Tic-Tac-Toe (Game 9),
 * including move validation, win/draw detection, and display.
 *
 * @see Board
 */
class NumericalTTT_Board : public Board<int> {
private:
    int blank_symbol = 0;        ///< Empty cell represented by 0
    bool usedNumbers[10];        ///< Marks used numbers 1..9

public:
    /**
     * @brief Default constructor initializes a 3x3 board with zeros.
     */
    NumericalTTT_Board();

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to a Move<int> object containing move coordinates and symbol (number).
     * @return true if the move is valid and successfully applied, false otherwise.
     */
    bool update_board(Move<int>* move);

    /**
     * @brief Checks if the given player has won the game (any line sums to 15).
     * @param player Pointer to the player being checked.
     * @return true if the player has a winning line, false otherwise.
     */
    bool is_win(Player<int>* player);

    /**
     * @brief Checks if the game has ended in a draw.
     * @param player Pointer to the player being checked.
     * @return true if all cells are filled and no win detected.
     */
    bool is_draw(Player<int>* player);

    /**
     * @brief Determines if the game is over (win or draw).
     * @param player Pointer to the player being checked.
     * @return true if the game has ended, false otherwise.
     */
    bool game_is_over(Player<int>* player);

    /**
     * @brief Always returns false (not used separately in this game).
     */
    bool is_lose(Player<int>*) { return false; }
};


/**
 * @class NumericalTTT_UI
 * @brief User Interface class for the Numerical Tic-Tac-Toe (Game 9).
 *
 * Inherits from the generic `UI<int>` base class and provides
 * Numerical Tic-Tac-Toe–specific functionality for player setup and move input.
 *
 * @see UI
 */
class NumericalTTT_UI : public UI<int> {
public:
    /**
     * @brief Constructs a NumericalTTT_UI object.
     *
     * Initializes the base `UI<int>` class with a welcome message.
     */
    NumericalTTT_UI();

    /**
     * @brief Destructor for NumericalTTT_UI.
     */
    ~NumericalTTT_UI() {};

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol Integer used to mark player's type (1=odd, 2=even).
     * @param type The type of the player (Human or Computer).
     * @return Pointer to the newly created Player<int> instance.
     */
    Player<int>* create_player(string& name, int symbol, PlayerType type);

    /**
     * @brief Retrieves the next move from a player.
     * @param player Pointer to the player whose move is being requested.
     * @return A pointer to a new `Move<int>` object representing the player's action.
     */
    virtual Move<int>* get_move(Player<int>* player);

    /**
     * @brief Handles player setup and returns an array of two player pointers.
     * @return Pointer to an array of two Player<int>* objects.
     */
    Player<int>** setup_players();
};

#endif // NUMERICALTTT_CLASSES_H