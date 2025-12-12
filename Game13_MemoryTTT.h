/**
 * @file Game13_MemoryTTT.h
 * @brief Memory Tic-Tac-Toe where placed marks become hidden.
 *
 * Provides GhostBoard, GhostCPU, GhostHuman, and GhostUI classes.
 * Players place marks that are hidden immediately, testing memory.
 */
#ifndef _GHOST_TIC_TAC_TOE_H
#define _GHOST_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <iostream>

using namespace std;

// Class representing the game board where marks disappear
/**
 * @class GhostBoard
 * @brief 3x3 board where marks are hidden after placement.
 *
 * Uses dual state tracking: internal_state stores actual marks,
 * while board displays '0' to hide them from players.
 */
class GhostBoard : public Board<char> {
private:
    char internal_state[3][3]; ///< Hidden storage for actual marks


public:
    /** @brief Constructs empty board with both states cleared. */
    GhostBoard() : Board<char>(3, 3) {
        n_moves = 0;
        // Initialization loop
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < columns; c++) {
                board[r][c] = 0;         // 0 allows the board to print empty spaces
                internal_state[r][c] = 0; // Clear the hidden state
            }
        }
    }

    // --- GAME STATUS CHECKS (Moved to top) ---

    // Checks if the move is legal by looking at the HIDDEN board

    /**
     * @brief Checks if a cell is occupied in hidden state.
     * @param r Row coordinate.
     * @param c Column coordinate.
     * @return true if cell occupied, false otherwise.
     */
    bool validate_coordinate(int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= columns) return true; // Out of bounds treated as invalid
        return internal_state[r][c] != 0; // Returns true if occupied
    }

    /**
     * @brief Checks if player has three hidden marks in a row.
     * @param p Pointer to player to check.
     * @return true if player wins, false otherwise.
     */
    bool is_win(Player<char>* p) override {
        char token = p->get_symbol();

        // Check Diagonals first (Order changed from original)
        if (internal_state[0][0] == token && internal_state[1][1] == token && internal_state[2][2] == token)
            return true;
        if (internal_state[0][2] == token && internal_state[1][1] == token && internal_state[2][0] == token)
            return true;

        // Check Rows
        for (int i = 0; i < 3; i++) {
            if (internal_state[i][0] == token && internal_state[i][1] == token && internal_state[i][2] == token)
                return true;
        }

        // Check Columns
        for (int i = 0; i < 3; i++) {
            if (internal_state[0][i] == token && internal_state[1][i] == token && internal_state[2][i] == token)
                return true;
        }

        return false;
    }

    // Returns true if board is full and no winner
    /**
     * @brief Checks if board is full without winner.
     * @param p Pointer to player to check.
     * @return true if draw, false otherwise.
     */
    bool is_draw(Player<char>* p) override {
        return (n_moves >= 9 && !is_win(p));
    }

    /**
     * @brief Determines if game has ended (win or draw).
     * @param p Pointer to player to check.
     * @return true if game over, false otherwise.
     */
    bool game_is_over(Player<char>* p) override {
        return is_win(p) || is_draw(p);
    }

    // Not used in this logic
        /** @brief Not used (returns false). */
    bool is_lose(Player<char>* p) override {
        return false;
    }

    // --- MODIFICATION LOGIC (Moved to bottom) ---

    /**
     * @brief Places mark in hidden state and masks it on visible board.
     * @param move Contains coordinates and player's symbol.
     * @return true if move applied, false otherwise.
     */
    bool update_board(Move<char>* move) override {
        int r = move->get_x();
        int c = move->get_y();
        char token = move->get_symbol();

        // 1. Validate bounds
        if (r < 0 || r >= rows || c < 0 || c >= columns) {
            return false;
        }

        // 2. Validate against INTERNAL state
        if (internal_state[r][c] != 0) {
            return false;
        }

        // 3. Update states
        internal_state[r][c] = token; // Store the actual mark
        board[r][c] = '0';            // Mask the mark on the public board

        n_moves++;
        return true;
    }
};

// Swapped Order: CPU defined before Human
/**
 * @class GhostCPU
 * @brief AI player that makes random valid moves.
 */
class GhostCPU : public Player<char> {
public:
    /** @brief Constructs AI player with RANDOM type. */
    GhostCPU(string n, char symbol) : Player<char>(n, symbol, PlayerType::RANDOM) {}

    void get_move(int& x, int& y) {} // Logic handled in UI
};

/**
 * @class GhostHuman
 * @brief Human player for Memory Tic-Tac-Toe.
 */
class GhostHuman : public Player<char> {
public:
    /** @brief Constructs human player with HUMAN type. */
    GhostHuman(string n, char symbol) : Player<char>(n, symbol, PlayerType::HUMAN) {}

    void get_move(int& x, int& y) {} // Logic handled in UI
};

/**
 * @class GhostUI
 * @brief UI for Memory Tic-Tac-Toe game.
 *
 * Handles hidden board display and move input with validation.
 */
class GhostUI : public UI<char> {
public:
    /** @brief Constructs UI with game warning message. */
    GhostUI() : UI<char>("Game 13: Memory Tic-Tac-Toe\n\nWarning: Marks are invisible after placement.\n", 3) {}

    // Moved create_player to the top of the class
    /**
     * @brief Creates player (AI or human).
     * @param name Player name.
     * @param symbol Player symbol ('X' or 'O').
     * @param type Player type (RANDOM or HUMAN).
     * @return Pointer to new Player instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        if (type == PlayerType::RANDOM) {
            return new GhostCPU(name, symbol);
        }
        else {
            return new GhostHuman(name, symbol);
        }
    }

    // Main input logic
    /**
     * @brief Gets move from player with validation.
     * @param player Pointer to current player.
     * @return Pointer to new Move instance.
     */
    Move<char>* get_move(Player<char>* player) override {
        int r, c;
        GhostBoard* g_board = (GhostBoard*)player->get_board_ptr();

        if (player->get_type() == PlayerType::RANDOM) {
            // AI random selection
            while (true) {
                r = rand() % 3;
                c = rand() % 3;

                // If spot is free in the hidden board, take it
                if (!g_board->validate_coordinate(r, c)) {
                    break;
                }
            }
        }
        else {
            // Human selection
            while (true) {
                cout << player->get_name() << " (" << player->get_symbol() << ") >> Enter Row and Column (0-2): ";

                if (!(cin >> r >> c)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Input Error. Please type integers.\n";
                    continue;
                }

                if (r < 0 || r > 2 || c < 0 || c > 2) {
                    cout << "Out of bounds. Must be between 0 and 2.\n";
                    continue;
                }

                // Check if the spot is secretly taken
                if (g_board->validate_coordinate(r, c)) {
                    cout << "Spot occupied! (You forgot the board state)\n";
                    continue;
                }
                break;
            }
        }
        return new Move<char>(r, c, player->get_symbol());
    }
};

#endif