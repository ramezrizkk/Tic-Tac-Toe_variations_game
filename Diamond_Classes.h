#ifndef GEM_TICTACTOE_DEF
#define GEM_TICTACTOE_DEF

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "BoardGame_Classes.h"

using namespace std;

// Implements a diamond-shaped Tic-Tac-Toe variant on a 7x7 grid
class gem_grid : public Board<char>
{
public:
    // Grid dimensions are fixed at 7x7 for the diamond layout
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
    bool game_is_over(Player<char>* participant) override
    {
        return is_win(participant) || is_draw(participant);
    }

    // Loss condition check (not applicable to this variant)
    bool is_lose(Player<char>* participant) override
    {
        return false;
    }
};

// Controller for human participants
class human_participant : public Player<char>
{
public:
    human_participant(string identifier, char marker)
        : Player<char>(identifier, marker, PlayerType::HUMAN)
    {
    }

    void get_move(int& x, int& y)
    {
    }
};

// Controller for AI participants
class ai_participant : public Player<char>
{
public:
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
class gem_interaction : public UI<char>
{
public:
    gem_interaction()
        : UI<char>("Game 6: Diamond Tic-Tac-Toe\nObjective: Create BOTH a 3-in-a-row AND a 4-in-a-row in DIFFERENT orientations\n", 3)
    {
    }

    // Handle move acquisition for current player
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

#endif // GEM_TICTACTOE_DEF