/**
 * @file SUS_Classes.h
 * @brief Defines the SUS (Tic-Tac-Toe) specific classes that extend the generic board game framework.
 *
 * This file provides:
 * - `SUS_Board`: A specialized board class for the Tic-Tac-Toe game.
 * - `SUS_UI`: A user interface class tailored to SUS game setup and player interaction.
 */
#ifndef INFINITYTTT_CLASSES_H
#define INFINITYTTT_CLASSES_H

#include "BoardGame_Classes.h"
#include "queue"
using namespace std;

/**
 * @class InfinitylTTT_Board
 * @brief Represents the Inifinity XO Tic-Tac-Toe game board.
 *
 * This class inherits from the generic `Board<char>` class and implements
 * the specific logic required for the Infinity XO Tic-Tac-Toe (Game 11),
 * including move validation, win/draw detection, and display.
 *
 * @see Board
 */
class InfinityXO_Board : public Board<char> {
private:
	char blank_symbol = '.';
    //The history of the players
	queue<pair<int, int>> playerX_history;
	queue<pair<int, int>> playerO_history;
public:
	/**
 * @brief Default constructor that initializes a 3x3 X-O board.
 */
	InfinityXO_Board();

	/**
	 * @brief Updates the board with a player's move.
	 * @param move Pointer to a Move<char> object containing move coordinates and symbol.
	 * @return true if the move is valid and successfully applied, false otherwise.
	 */
	bool update_board(Move<char>*move);

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
    bool is_lose(Player<char>*) { return false; };

    /**
     * @brief Checks if the game has ended in a draw.
     * @param player Pointer to the player being checked.
     * @return Always returns false (there's no draw in Infinity XO Game).
     */
    bool is_draw(Player<char>* player) { return false; };

    /**
     * @brief Determines if the game is over (win or draw).
     * @param player Pointer to the player to evaluate.
     * @return true if the game has ended, false otherwise.
     */
    bool game_is_over(Player<char>* player);
};

/**
 * @class XO_UI
 * @brief User Interface class for the X-O (Tic-Tac-Toe) game.
 *
 * Inherits from the generic `UI<char>` base class and provides
 * X-O–specific functionality for player setup and move input.
 *
 * @see UI
 */
class InfinityXO_UI : public UI<char> {
public:
    /**
     * @brief Constructs an XO_UI object.
     *
     * Initializes the base `UI<char>` class with the welcome message "FCAI Infinity X-O".
     */
    InfinityXO_UI();

    /**
     * @brief Destructor for InfinityXO_UI.
     */
    ~InfinityXO_UI() {};

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol Character symbol ('X' or 'O') assigned to the player.
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
};

#endif // INFINITYTTT_CLASSES_H
