/**
 * @file Diamond_Classes.h
 * @brief Diamond-shaped Tic-Tac-Toe variant on 7x7 grid.
 *
 * Provides gem_grid, human_participant, ai_participant, and gem_interaction
 * classes for a game where players need both 3-in-a-row and 4-in-a-row in
 * different orientations to win.
 */
#ifndef GEM_TICTACTOE_DEF
#define GEM_TICTACTOE_DEF

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "BoardGame_Classes.h"

using namespace std;

// Implements a diamond-shaped Tic-Tac-Toe variant on a 7x7 grid
/**
 * @class gem_grid
 * @brief 7x7 diamond-shaped board for Diamond Tic-Tac-Toe.
 *
 * Out-of-bounds cells are marked with space. Win requires both a triplet
 * (3 marks) and quartet (4 marks) in different orientations (horizontal,
 * vertical, diagonal, anti-diagonal).
 */
class gem_grid : public Board<char>
{
public:
    // Grid dimensions are fixed at 7x7 for the diamond layout
     /** @brief Constructs 7x7 diamond board with out-of-bounds cells marked. */
    gem_grid() : Board<char>(7, 7)
    {
        n_moves = 0;

        // Set all cells to empty state represented by '.'
        for (int row_index = 0; row_index < 7; row_index++)
        {
            for (int col_index = 0; col_index < 7; col_index++)
            {
                board[row_index][col_index] = '.';
            }
        }

        // Define out-of-bounds positions using space character
        // Top row exclusions
        board[0][0] = ' ';
        board[0][1] = ' ';
        board[0][2] = ' ';
        board[0][4] = ' ';
        board[0][5] = ' ';
        board[0][6] = ' ';

        // Second row exclusions
        board[1][0] = ' ';
        board[1][1] = ' ';
        board[1][5] = ' ';
        board[1][6] = ' ';

        // Third row edge exclusions
        board[2][0] = ' ';
        board[2][6] = ' ';

        // Fourth row is fully valid (central horizontal axis)

        // Fifth row edge exclusions
        board[4][0] = ' ';
        board[4][6] = ' ';

        // Sixth row exclusions
        board[5][0] = ' ';
        board[5][1] = ' ';
        board[5][5] = ' ';
        board[5][6] = ' ';

        // Bottom row exclusions
        board[6][0] = ' ';
        board[6][1] = ' ';
        board[6][2] = ' ';
        board[6][4] = ' ';
        board[6][5] = ' ';
        board[6][6] = ' ';
    }

    // Process a player's move attempt
    /**
     * @brief Places mark on valid diamond cells only.
     * @param move Contains coordinates and player's mark.
     * @return true if move valid and applied, false otherwise.
     */
    bool update_board(Move<char>* action) override
    {
        int row = action->get_x();
        int col = action->get_y();
        char player_mark = action->get_symbol();

        // Validate coordinate boundaries
        if (row < 0 || row >= 7 || col < 0 || col >= 7)
        {
            return false;
        }

        // Reject moves on invalid spaces or already occupied cells
        if (board[row][col] == ' ' || board[row][col] != '.')
        {
            return false;
        }

        // Commit the move in uppercase format
        board[row][col] = toupper(player_mark);
        n_moves++;
        return true;
    }

    // Scan for any three consecutive symbols and identify the alignment
    /**
     * @brief Searches for any 3 consecutive marks of player.
     * @param player_mark The symbol to search for.
     * @param orientation Output parameter for found orientation.
     * @return true if triplet found, false otherwise.
     */
    bool validate_triplet(char player_mark, string& orientation)
    {
        player_mark = toupper(player_mark);

        // Horizontal scanning
        for (int r = 0; r < 7; r++)
        {
            for (int c = 0; c <= 4; c++)
            {
                if (board[r][c] == player_mark &&
                    board[r][c + 1] == player_mark &&
                    board[r][c + 2] == player_mark)
                {
                    orientation = "horizontal";
                    return true;
                }
            }
        }

        // Vertical scanning
        for (int r = 0; r <= 4; r++)
        {
            for (int c = 0; c < 7; c++)
            {
                if (board[r][c] == player_mark &&
                    board[r + 1][c] == player_mark &&
                    board[r + 2][c] == player_mark)
                {
                    orientation = "vertical";
                    return true;
                }
            }
        }

        // Main diagonal scanning
        for (int r = 0; r <= 4; r++)
        {
            for (int c = 0; c <= 4; c++)
            {
                if (board[r][c] == player_mark &&
                    board[r + 1][c + 1] == player_mark &&
                    board[r + 2][c + 2] == player_mark)
                {
                    orientation = "diagonal";
                    return true;
                }
            }
        }

        // Anti-diagonal scanning
        for (int r = 0; r <= 4; r++)
        {
            for (int c = 3; c < 7; c++)
            {
                if (board[r][c] == player_mark &&
                    board[r + 1][c - 1] == player_mark &&
                    board[r + 2][c - 2] == player_mark)
                {
                    orientation = "anti-diagonal";
                    return true;
                }
            }
        }

        return false;
    }

    // Scan for any four consecutive symbols and identify the alignment
    /**
     * @brief Searches for any 4 consecutive marks of player.
     * @param player_mark The symbol to search for.
     * @param orientation Output parameter for found orientation.
     * @return true if quartet found, false otherwise.
     */
    bool validate_quartet(char player_mark, string& orientation)
    {
        player_mark = toupper(player_mark);

        // Horizontal scanning
        for (int r = 0; r < 7; r++)
        {
            for (int c = 0; c <= 3; c++)
            {
                if (board[r][c] == player_mark &&
                    board[r][c + 1] == player_mark &&
                    board[r][c + 2] == player_mark &&
                    board[r][c + 3] == player_mark)
                {
                    orientation = "horizontal";
                    return true;
                }
            }
        }

        // Vertical scanning
        for (int r = 0; r <= 3; r++)
        {
            for (int c = 0; c < 7; c++)
            {
                if (board[r][c] == player_mark &&
                    board[r + 1][c] == player_mark &&
                    board[r + 2][c] == player_mark &&
                    board[r + 3][c] == player_mark)
                {
                    orientation = "vertical";
                    return true;
                }
            }
        }

        // Main diagonal scanning
        for (int r = 0; r <= 3; r++)
        {
            for (int c = 0; c <= 3; c++)
            {
                if (board[r][c] == player_mark &&
                    board[r + 1][c + 1] == player_mark &&
                    board[r + 2][c + 2] == player_mark &&
                    board[r + 3][c + 3] == player_mark)
                {
                    orientation = "diagonal";
                    return true;
                }
            }
        }

        // Anti-diagonal scanning
        for (int r = 0; r <= 3; r++)
        {
            for (int c = 4; c < 7; c++)
            {
                if (board[r][c] == player_mark &&
                    board[r + 1][c - 1] == player_mark &&
                    board[r + 2][c - 2] == player_mark &&
                    board[r + 3][c - 3] == player_mark)
                {
                    orientation = "anti-diagonal";
                    return true;
                }
            }
        }

        return false;
    }

    // Determine if the player has met the win condition
    /**
     * @brief Checks if player has both triplet and quartet in different orientations.
     * @param participant Pointer to player to check.
     * @return true if player meets win condition, false otherwise.
     */
    bool is_win(Player<char>* participant) override
    {
        char target_symbol = toupper(participant->get_symbol());
        string triplet_orientation, quartet_orientation;

        // Verify both required formations exist
        bool found_triplet = validate_triplet(target_symbol, triplet_orientation);
        bool found_quartet = validate_quartet(target_symbol, quartet_orientation);

        // Victory requires both formations in different alignments
        if (found_triplet && found_quartet && triplet_orientation != quartet_orientation)
        {
            return true;
        }

        return false;
    }

    // Check for draw condition (no empty cells remaining)
    /**
     * @brief Checks if board is full without winner.
     * @param participant Pointer to player to check.
     * @return true if draw, false otherwise.
     */
    bool is_draw(Player<char>* participant) override
    {
        int vacant_cells = 0;

        for (int r = 0; r < 7; r++)
        {
            for (int c = 0; c < 7; c++)
            {
                if (board[r][c] == '.')
                {
                    vacant_cells++;
                }
            }
        }

        return (vacant_cells == 0 && !is_win(participant));
    }

    // Overall game termination verification
    /**
     * @brief Determines if game has ended (win or draw).
     * @param participant Pointer to player to check.
     * @return true if game over, false otherwise.
     */
    bool game_is_over(Player<char>* participant) override
    {
        return is_win(participant) || is_draw(participant);
    }

    // Loss condition check (not applicable to this variant)
    /** @brief is_lose not applicable (returns false). */
    bool is_lose(Player<char>* participant) override
    {
        return false;
    }
};

// Controller for human participants
/**
 * @class human_participant
 * @brief Controller for human players in Diamond game.
 */
class human_participant : public Player<char>
{
public:
    /** @brief Constructs human player with name and symbol. */
    human_participant(string identifier, char marker)
        : Player<char>(identifier, marker, PlayerType::HUMAN)
    {
    }

    void get_move(int& x, int& y)
    {
    }
};

// Controller for AI participants
/**
 * @class ai_participant
 * @brief Controller for AI players in Diamond game (random moves).
 */
class ai_participant : public Player<char>
{
public:
    /** @brief Constructs AI player with name, symbol, and seeds random generator. */
    ai_participant(string identifier, char marker)
        : Player<char>(identifier, marker, PlayerType::RANDOM)
    {
        srand(static_cast<unsigned int>(time(0)));
    }

    void get_move(int& x, int& y)
    {
    }
};

// User interaction management
/**
 * @class gem_interaction
 * @brief UI for Diamond Tic-Tac-Toe game.
 *
 * Handles move input for humans and automated random moves for AI.
 */
class gem_interaction : public UI<char>
{
public:
    /** @brief Constructs UI with game objective message. */
    gem_interaction()
        : UI<char>("Game 6: Diamond Tic-Tac-Toe\nObjective: Create BOTH a 3-in-a-row AND a 4-in-a-row in DIFFERENT orientations\n", 3)
    {
    }

    // Handle move acquisition for current player
    /**
     * @brief Gets move from current player.
     * @param current Pointer to player whose turn it is.
     * @return Pointer to new Move instance.
     */
    Move<char>* get_move(Player<char>* current) override
    {
        int row, col;

        // Automated opponent logic
        if (current->get_type() == PlayerType::RANDOM)
        {
            gem_grid* game_board = (gem_grid*)current->get_board_ptr();

            while (true)
            {
                row = rand() % 7;
                col = rand() % 7;

                if (game_board->get_cell(row, col) == '.')
                {
                    break;
                }
            }

            return new Move<char>(row, col, current->get_symbol());
        }

        // Human player input handling
        while (true)
        {
            cout << current->get_name() << ", specify your move coordinates (row column, 0-6): ";
            cin >> row >> col;

            // Validate input range
            if (row < 0 || row > 6 || col < 0 || col > 6)
            {
                cout << "Coordinates exceed board boundaries. Valid range: 0-6.\n";
                continue;
            }

            gem_grid* game_board = (gem_grid*)current->get_board_ptr();

            // Reject out-of-diamond positions
            if (game_board->get_cell(row, col) == ' ')
            {
                cout << "Selected position lies outside the diamond boundary.\n";
                continue;
            }

            // Reject occupied cells
            if (game_board->get_cell(row, col) != '.')
            {
                cout << "Cell already occupied by another mark.\n";
                continue;
            }

            break;
        }

        return new Move<char>(row, col, current->get_symbol());
    }

    // Player instance factory
        /**
     * @brief Creates player instance (human or AI).
     * @param identifier Player name.
     * @param symbol Player mark ('X' or 'O').
     * @param kind Player type (HUMAN or RANDOM).
     * @return Pointer to new Player instance.
     */

    Player<char>* create_player(string& identifier, char symbol, PlayerType kind) override
    {
        if (kind == PlayerType::RANDOM)
        {
            return new ai_participant(identifier, symbol);
        }
        else
        {
            return new human_participant(identifier, symbol);
        }
    }
};
//
#endif // GEM_TICTACTOE_DEF
