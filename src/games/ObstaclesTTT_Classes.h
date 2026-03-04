/**
 * @file ObstaclesTTT_Classes.h
 * @brief Obstacles Tic-Tac-Toe on 6x6 grid with dynamically added obstacles.
 *
 * Provides ObstaclesTTT_Board and ObstaclesTTT_UI classes. After each round,
 * 2 random obstacle cells (#) are added. Players win by placing 4 marks in a row.
 */

#ifndef OBSTACLESTTT_CLASSES_H
#define OBSTACLESTTT_CLASSES_H
#include "BoardGame_Classes.h"

 /**
  * @class ObstaclesTTT_Board
  * @brief 6x6 board with obstacle generation and 4-in-a-row win condition.
  *
  * Tracks last move position for win checking. Adds 2 random obstacles after
  * every round (every 2 moves). Obstacles block cells permanently.
  */
class ObstaclesTTT_Board : public Board<char> {
private:
    char blank_symbol = '.';  ///< Empty cell character
    char obstacle_symbol = '#'; ///< Obstacle marker
    int last_x, last_y;       ///< Last move coordinates for win checking

    /** @brief Adds random obstacle cells to the board. */
    void add_random_obstacles(int count);

    /**
     * @brief Checks for line of 4+ matching symbols from a position.
     * @param x Starting row.
     * @param y Starting column.
     * @param dx Row direction increment.
     * @param dy Column direction increment.
     * @param symbol Player's symbol to check.
     * @return true if line of 4+ found, false otherwise.
     */
    bool check_line(int x, int y, int dx, int dy, char symbol);

public:
    /** @brief Constructs empty 6x6 board. */
    ObstaclesTTT_Board();

    /**
     * @brief Places mark and adds obstacles after each round.
     * @param move Contains coordinates and player's symbol.
     * @return true if move applied, false otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if player has 4 in a row from last move.
     * @param player Pointer to player to check.
     * @return true if player wins, false otherwise.
     */
    bool is_win(Player<char>* player) override;

    /** @brief Not used (loss condition determined by opponent win). */
    bool is_lose(Player<char>*) override { return false; }

    /**
     * @brief Checks if board is full without winner.
     * @param player Pointer to player to check.
     * @return true if draw, false otherwise.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Determines if game has ended (win or draw).
     * @param player Pointer to player to check.
     * @return true if game over, false otherwise.
     */
    bool game_is_over(Player<char>* player) override;
};

/**
 * @class ObstaclesTTT_UI
 * @brief UI for Obstacles Tic-Tac-Toe game.
 *
 * Handles player setup and move input for human and computer players.
 */
class ObstaclesTTT_UI : public UI<char> {
public:
    /** @brief Constructs UI with welcome message. */
    ObstaclesTTT_UI();
    /** @brief Destructor for ObstaclesTTT_UI. */
    ~ObstaclesTTT_UI() {}

    /**
     * @brief Creates player of specified type.
     * @param name Player's name.
     * @param symbol Player's symbol ('X' or 'O').
     * @param type Player type (Human or Computer).
     * @return Pointer to new Player instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Gets move from player (coordinates).
     * @param player Pointer to current player.
     * @return Pointer to new Move instance.
     */
    Move<char>* get_move(Player<char>* player);
};

#endif