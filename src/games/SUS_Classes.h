/**
 * @file SUS_Classes.h
 * @brief Defines the SUS (Tic-Tac-Toe) specific classes that extend the generic board game framework.
 *
 * This file provides:
 * - `SUS_Board`: A specialized board class for the Tic-Tac-Toe game.
 * - `SUS_UI`: A user interface class tailored to SUS game setup and player interaction.
 */

#ifndef SUS_CLASSES_H
#define SUS_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;


//
/**
 * @class SUS_Board
 * @brief Represents the Tic-Tac-Toe game board.
 *
 * This class inherits from the generic `Board<char>` class and implements
 * the specific logic required for the Tic-Tac-Toe (SUS) game, including
 * move updates, win/draw detection, and display functions.
 *
 * @see Board
 */
class SUS_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.
    int scores[2];  // scores[0] = Player S, scores[1] = Player U

public:
    /**
     * @brief Default constructor that initializes a 3x3 SUS board.
     */
    SUS_Board();

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to a Move<char> object containing move coordinates and symbol.
     * @return true if the move is valid and successfully applied, false otherwise.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks if the given player has won the game.
     * @param player Pointer to the player being checked.
     * @return true if the player has a winning line, false otherwise.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Checks if the given player has lost the game.
     * @param player Pointer to the player being checked.
     * @return Always returns false (not used in X-O logic).
     */
    bool is_lose(Player<char>*);

    /**
     * @brief Checks if the game has ended in a draw.
     * @param player Pointer to the player being checked.
     * @return true if all cells are filled and no player has won, false otherwise.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Determines if the game is over (win or draw).
     * @param player Pointer to the player to evaluate.
     * @return true if the game has ended, false otherwise.
     */
    bool game_is_over(Player<char>* player);

        /**
     * @brief Helper method to check if three characters form S-U-S
     * @param three characters
     * @return true if the three characters form a SUS, false otherwise.
     */
    bool is_SUS(char c1, char c2, char c3);

    /** @brief Get score for a player
    */
    int get_score(char symbol);

    // Returns all empty cells
    vector<pair<int, int>> get_valid_moves();

    // Simple scoring without full minimax
    int get_move_score(int x, int y, char symbol);
};


/**
 * @class SUS_UI
 * @brief User Interface class for the SUS (Tic-Tac-Toe) game.
 *
 * Inherits from the generic `UI<char>` base class and provides
 * SUS–specific functionality for player setup and move input.
 *
 * @see UI
 */
class SUS_UI : public UI<char> {
public:
    /**
     * @brief Constructs an SUS_UI object.
     *
     * Initializes the base `UI<char>` class with the welcome message "FCAI SUS Game".
     */
    SUS_UI();

    /**
     * @brief Destructor for SUS_UI.
     */
    ~SUS_UI() {};

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol Character symbol ('S' or 'U) assigned to the player.
     * @param type The type of the player (Human or Computer).
     * @return Pointer to the newly created Player<char> instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Retrieves the next move from a player.
     * @param player Pointer to the player whose move is being requested.
     * @return A pointer to a new `Move<char>` object representing the player's action.
     */
    virtual Move<char>* get_move(Player<char>* player);

    /**
     * @brief Handles player setup and returns an array of two player pointers.
     * @return Pointer to an array of two Player<int>* objects.
     */
    Player<char>** setup_players() override;
};
//
#endif // SUS_CLASSES_H


