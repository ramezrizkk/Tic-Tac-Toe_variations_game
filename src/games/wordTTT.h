#pragma once
#include "BoardGame_Classes.h"
#include <fstream>
#include <set>

using namespace std;

/**
 * @class ThreeWord_Board
 * @brief Represents the 3x3 board for the Three-Letter Word Game.
 *
 * Inherits from Board<char> and implements the game-specific logic.
 */
class ThreeWord_Board : public Board<char> {
private:
    char blank_symbol = ' '; ///< Character used to represent an empty cell.
    set<string> dictionary;  ///< Set of valid 3-letter words from dic.txt.

    /** @brief Loads the dictionary of 3-letter words from "dic.txt". */
    void load_dictionary();

    /** @brief Checks if a 3-letter string is a valid word. */
    bool is_valid_word(const string& word) const;

public:
    /**
     * @brief Default constructor that initializes a 3x3 board and loads the dictionary.
     */
    ThreeWord_Board();

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to a Move<char> object containing move coordinates and symbol (letter).
     * @return true if the move is valid and successfully applied, false otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if the player's last move resulted in a win (forming a valid 3-letter word).
     * @param player Pointer to the player being checked.
     * @return true if the player has won, false otherwise.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if the player has lost. (Not used in this game logic).
     */
    bool is_lose(Player<char>*) override { return false; };

    /**
     * @brief Checks if the game has ended in a draw (board filled, no win).
     * @param player Pointer to the player being checked.
     * @return true if the game is a draw, false otherwise.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Determines if the game is over (win or draw).
     * @param player Pointer to the player to evaluate.
     * @return true if the game has ended, false otherwise.
     */
    bool game_is_over(Player<char>* player) override;
};

/**
 * @class WordGame_UI
 * @brief User Interface class for the Three-Letter Word Game.
 *
 * Inherits from the generic UI<char> base class.
 */
class WordGame_UI : public UI<char> {
public:
    /**
     * @brief Constructs a WordGame_UI object.
     */
    WordGame_UI();

    /**
     * @brief Retrieves the next move from a player (row, column, and letter).
     * @param player Pointer to the player whose move is being requested.
     * @return A pointer to a new Move<char> object representing the player's action.
     */
    virtual Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Custom setup for players, uses 'L1' and 'L2' as default symbols.
     */
    Player<char>** setup_players() override;

    /**
     * @brief Creates a generic Player<char> object (as we don't need a custom WordGame_Player).
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

