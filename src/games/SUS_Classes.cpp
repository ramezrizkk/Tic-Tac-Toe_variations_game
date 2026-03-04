//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "SUS_Classes.h"

using namespace std;

//--------------------------------------- X_O_Board Implementation

SUS_Board::SUS_Board() : Board(3, 3) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
    scores[0] = 0;
    scores[1] = 0;

}

bool SUS_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate: position in bounds and cell is empty
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        return false;  // Out of bounds
    }

    if (board[x][y] != blank_symbol) {
        return false;  // Cell already occupied
    }
    if (mark == 0) { // Undo move (it will need much more work to remove any score related to this cell)
        n_moves--;
        board[x][y] = blank_symbol;
        return true;
    }
    // Place the symbol
    board[x][y] = toupper(mark);
    n_moves++;

    // Now check if this move completed any S-U-S sequences
    // the current player (the one with the current mark) gets the score

    // Check row x
    if (is_SUS(board[x][0], board[x][1], board[x][2])) {
        if (mark == 'S') {
            scores[0]++;
        }
        else {
            scores[1]++;
        }
    }

    // Check column y
    if (is_SUS(board[0][y], board[1][y], board[2][y])) {
        if (mark == 'S') {
            scores[0]++;
        }
        else {
            scores[1]++;
        }
    }

    // Check main diagonal
    if (x == y) {
        if (is_SUS(board[0][0], board[1][1], board[2][2])) {
            if (mark == 'S') {
                scores[0]++;
            }
            else {
                scores[1]++;
            }
        }
    }

    // Check anti-diagonal
    if (x + y == 2) {
        if (is_SUS(board[0][2], board[1][1], board[2][0])) {
            if (mark == 'S') {
                scores[0]++;
            }
            else {
                scores[1]++;
            }
        }
    }

    return true;
}

bool SUS_Board::is_win(Player<char>* player) {
    // Game must be over first (board full)
    if (n_moves != 9) {
        return false;
    }

    char sym = player->get_symbol();
    int my_score = get_score(sym);
    int opponent_score;

    if (sym == 'S') {
        opponent_score = scores[1];  // U's score
    }
    else {
        opponent_score = scores[0];  // S's score
    }

    // Current player wins if they have more S-U-S
    return (my_score > opponent_score);
}

bool SUS_Board::is_lose(Player<char>* player) {
    // Game must be over first (board full)
    if (n_moves != 9) {
        return false;
    }

    char sym = player->get_symbol();
    int my_score = get_score(sym);
    int opponent_score;

    if (sym == 'S') {
        opponent_score = scores[1];  // U's score
    }
    else {
        opponent_score = scores[0];  // S's score
    }

    // Current player wins if they have more S-U-S
    return (my_score < opponent_score);
}


bool SUS_Board::is_draw(Player<char>* player) {
    // Game must be over AND scores must be equal

    if (n_moves != 9) {
        return false;
    }

    return (scores[0] == scores[1]);
}

bool SUS_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

bool SUS_Board::is_SUS(char c1, char c2, char c3)
{
    return (c1 == 'S' && c2 == 'U' && c3 == 'S');
}

int SUS_Board::get_score(char symbol)
{
    if (symbol == 'S')
    {
        return scores[0];
    }
    else
    {
        return scores[1];
    }
}

vector<pair<int, int>> SUS_Board::get_valid_moves() {
    vector<pair<int, int>> moves;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == blank_symbol)
                moves.push_back({ i, j });
    return moves;
}

// Score a potential move
int SUS_Board::get_move_score(int x, int y, char symbol) {
    int score = 0;
    char opponent = (symbol == 'S') ? 'U' : 'S';

    // Temporarily place the piece
    char original = board[x][y];
    board[x][y] = symbol;

    // Check if we create S-U-S
    // Check row
    if (board[x][0] == 'S' && board[x][1] == 'U' && board[x][2] == 'S') score += 100;
    // Check column
    if (board[0][y] == 'S' && board[1][y] == 'U' && board[2][y] == 'S') score += 100;
    // Check diagonals
    if (x == y && board[0][0] == 'S' && board[1][1] == 'U' && board[2][2] == 'S') score += 100;
    if (x + y == 2 && board[0][2] == 'S' && board[1][1] == 'U' && board[2][0] == 'S') score += 100;

    // Restore board
    board[x][y] = original;

    // Prefer center
    if (x == 1 && y == 1) score += 10;

    return score;
}



//--------------------------------------- SUS_UI Implementation

SUS_UI::SUS_UI() : UI<char>("Weclome to FCAI SUS Tic-Tac-Toe Game", 3) {}

Player<char>* SUS_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* SUS_UI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::HUMAN) {
        int x, y;
        cout << "\nPlease " << player->get_name() << " enter x and y (0 to 2)\n> ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }
    else { // Smart Computer
        cout << "\nComputer " << player->get_name() << " is thinking...\n";

        char symbol = player->get_symbol();

        // Get board from player and cast to SUS_Board
        SUS_Board* board = dynamic_cast<SUS_Board*>(player->get_board_ptr());

        // Get all possible moves
        auto moves = board->get_valid_moves();

        int best_score = -1000;
        pair<int, int> best_move = moves[0];

        // Try each possible move and pick the best
        for (auto& move : moves) {
            int score = board->get_move_score(move.first, move.second, symbol);

            if (score > best_score) {
                best_score = score;
                best_move = move;
            }
        }

        cout << player->get_name() << " chooses " << best_move.first << "," << best_move.second << "\n";
        return new Move<char>(best_move.first, best_move.second, symbol);
    }
}

Player<char>** SUS_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameS = get_player_name("Player S");
    PlayerType typeS = get_player_type_choice("Player S", type_options);
    players[0] = create_player(nameS, 'S', typeS);

    string nameU = get_player_name("Player U");
    PlayerType typeU = get_player_type_choice("Player U", type_options);
    players[1] = create_player(nameU, 'U', typeU);

    return players;
}
