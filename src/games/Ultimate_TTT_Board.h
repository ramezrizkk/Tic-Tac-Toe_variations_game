/**
 * @file Ultimate_TTT_Board.h
 * @brief Ultimate Tic-Tac-Toe on a 9x9 grid composed of nine 3x3 zones.
 *
 * Provides SuperGrid and MegaGameInterface classes. Players play on a local
 * 3x3 zone, and winning a zone marks it on the global 3x3 grid. Win the global
 * grid to win the game.
 */
#ifndef _MEGA_TICTACTOE_H
#define _MEGA_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Represents the 9x9 grid composed of 9 smaller 3x3 zones
/**
 * @class SuperGrid
 * @brief 9x9 board made of nine 3x3 zones for Ultimate Tic-Tac-Toe.
 *
 * Each 3x3 zone tracks its own winner. Winning a zone claims it on the
 * main 3x3 grid. Win by getting three zones in a row.
 */
class SuperGrid : public Board<char> {
private:
    char zone_winners[3][3]; ///< Stores winner of each 3x3 zone


public:
    /** @brief Constructs empty 9x9 board and clears zone winners. */
    SuperGrid() : Board<char>(9, 9) {
        // Clear the main 9x9 grid
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                board[r][c] = '.';
            }
        }
        // Clear the zone status grid
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                zone_winners[r][c] = '.';
            }
        }
    }

    // --- WIN CHECKING LOGIC ---
    /**
     * @brief Checks if player has three zones in a row.
     * @param p Pointer to player to check.
     * @return true if player wins, false otherwise.
     */
    bool is_win(Player<char>* p) override {
        char token = p->get_symbol();

        // Check horizontal zones
        for (int r = 0; r < 3; r++) {
            if (zone_winners[r][0] == token && zone_winners[r][1] == token && zone_winners[r][2] == token)
                return true;
        }

        // Check vertical zones
        for (int c = 0; c < 3; c++) {
            if (zone_winners[0][c] == token && zone_winners[1][c] == token && zone_winners[2][c] == token)
                return true;
        }

        // Check diagonals
        bool d1 = (zone_winners[0][0] == token && zone_winners[1][1] == token && zone_winners[2][2] == token);
        bool d2 = (zone_winners[0][2] == token && zone_winners[1][1] == token && zone_winners[2][0] == token);

        return (d1 || d2);
    }

    /**
     * @brief Checks if all 81 cells are filled without winner.
     * @param p Pointer to player to check.
     * @return true if draw, false otherwise.
     */
    bool is_draw(Player<char>* p) override {
        // Game ends in draw if all 81 moves are made without a global winner
        return (n_moves == 81 && !is_win(p));
    }

    /**
     * @brief Determines if game has ended (win or draw).
     * @param p Pointer to player to check.
     * @return true if game over, false otherwise.
     */
    bool game_is_over(Player<char>* p) override {
        return is_win(p) || is_draw(p);
    }

    /** @brief Not used (returns false). */
    bool is_lose(Player<char>* p) override { return false; }

    // --- GAMEPLAY LOGIC ---
    /**
     * @brief Places mark in a 3x3 zone if zone is valid and not full.
     * @param move Contains coordinates and player's symbol.
     * @return true if move applied, false otherwise.
     */
    bool update_board(Move<char>* move) override {
        int row = move->get_x();
        int col = move->get_y();
        char mark = move->get_symbol();

        // 1. Boundary Safety Check
        if (row < 0 || row >= 9 || col < 0 || col >= 9) return false;

        // 2. Occupancy Check
        if (board[row][col] != '.') return false;

        // 3. Zone Validation
        int block_row = row / 3;
        int block_col = col / 3;

        // Ensure the zone isn't already claimed or full
        if (zone_winners[block_row][block_col] != '.' || isZoneFull(block_row, block_col)) {
            return false;
        }

        // 4. Place Mark
        board[row][col] = mark;
        n_moves++;

        // 5. Update Zone Status
        if (zone_winners[block_row][block_col] == '.') {
            char result = scanForZoneWin(block_row, block_col);
            if (result != '.') {
                zone_winners[block_row][block_col] = result;
            }
        }

        return true;
    }

    // Helper: Validates if a zone is playable for the UI
    /**
     * @brief Checks if a 3x3 zone is available for play (not won or full).
     * @param br Zone row index (0-2).
     * @param bc Zone column index (0-2).
     * @return true if zone is playable, false otherwise.
     */
    bool isZonePlayable(int br, int bc) {
        return (zone_winners[br][bc] == '.' && !isZoneFull(br, bc));
    }

private:
    // --- PRIVATE HELPERS (Moved to Bottom) ---

    // Checks if a specific 3x3 zone has been won
    /**
     * @brief Checks a specific 3x3 zone for a winner.
     * @param block_row Zone row index (0-2).
     * @param block_col Zone column index (0-2).
     * @return Winning symbol, or '.' if no winner.
     */
    char scanForZoneWin(int block_row, int block_col) {
        int base_r = block_row * 3;
        int base_c = block_col * 3;

        // Scan rows and columns within the zone
        for (int k = 0; k < 3; k++) {
            // Row check
            if (board[base_r + k][base_c] != '.' &&
                board[base_r + k][base_c] == board[base_r + k][base_c + 1] &&
                board[base_r + k][base_c + 1] == board[base_r + k][base_c + 2])
                return board[base_r + k][base_c];

            // Column check
            if (board[base_r][base_c + k] != '.' &&
                board[base_r][base_c + k] == board[base_r + 1][base_c + k] &&
                board[base_r + 1][base_c + k] == board[base_r + 2][base_c + k])
                return board[base_r][base_c + k];
        }

        // Diagonal checks
        char center = board[base_r + 1][base_c + 1];
        if (center == '.') return '.'; // Optimization: if center is empty, diags can't win

        if (board[base_r][base_c] == center && center == board[base_r + 2][base_c + 2])
            return center;

        if (board[base_r][base_c + 2] == center && center == board[base_r + 2][base_c])
            return center;

        return '.';
    }

    // Checks if a zone has no empty spots left
    /**
     * @brief Checks if a 3x3 zone has no empty cells.
     * @param block_row Zone row index (0-2).
     * @param block_col Zone column index (0-2).
     * @return true if zone is full, false otherwise.
     */
    bool isZoneFull(int block_row, int block_col) {
        int base_r = block_row * 3;
        int base_c = block_col * 3;

        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                if (board[base_r + r][base_c + c] == '.') {
                    return false;
                }
            }
        }
        return true;
    }
};
/**
 * @class MegaGameInterface
 * @brief UI for Ultimate Tic-Tac-Toe game.
 *
 * Displays 9x9 board with zone separators and handles move input
 * for human and computer players.
 */
class MegaGameInterface : public UI<char> {
public:
    /** @brief Constructs UI with cell width of 3. */
    MegaGameInterface() : UI<char>(3) {}

    /**
     * @brief Displays 9x9 board formatted with 3x3 zone separators.
     * @param matrix The board state to display.
     */
    void display_board_matrix(const vector<vector<char>>& matrix) const override {
        cout << "\n    0 1 2   3 4 5   6 7 8\n";
        cout << "  #######################\n";

        for (int r = 0; r < 9; ++r) {
            cout << r << " #";
            for (int c = 0; c < 9; ++c) {
                cout << " " << matrix[r][c];
                // Add vertical separator every 3 columns
                if ((c + 1) % 3 == 0) cout << " #";
            }
            cout << "\n";
            // Add horizontal separator every 3 rows
            if ((r + 1) % 3 == 0) cout << "  #######################\n";
        }
        cout << endl;
    }

    /**
     * @brief Gets move from player with zone playability validation.
     * @param p Pointer to current player.
     * @return Pointer to new Move instance.
     */
    Move<char>* get_move(Player<char>* p) override {
        int row, col;

        // Downcast to access specific SuperGrid methods
        SuperGrid* grid = dynamic_cast<SuperGrid*>(p->get_board_ptr());

        if (p->get_type() == PlayerType::HUMAN) {
            cout << ">> " << p->get_name() << " [" << p->get_symbol() << "], input Row (0-8) & Col (0-8): ";
            cin >> row >> col;

            // Pre-validation feedback
            if (row >= 0 && row < 9 && col >= 0 && col < 9) {
                int br = row / 3;
                int bc = col / 3;
                if (!grid->isZonePlayable(br, bc)) {
                    cout << ">> Warning: That zone is closed (won or full). Try elsewhere.\n";
                }
            }
        }
        else {
            // AI Logic: Randomly hunt for valid spot
            while (true) {
                row = rand() % 9;
                col = rand() % 9;

                int br = row / 3;
                int bc = col / 3;

                // Optimization: Only attempt move if the zone is actually open
                if (grid->isZonePlayable(br, bc)) {
                    break;
                }
            }
        }
        return new Move<char>(row, col, p->get_symbol());
    }
};

#endif