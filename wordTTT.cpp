#include <iostream>
#include <algorithm> // for transform
#include <cctype>    // for toupper
#include "wordTTT.h"

using namespace std;

//--------------------------------------- ThreeWord_Board Implementation

/**
 * @brief Loads the dictionary of 3-letter words from "dic.txt".
 * Converts all words to uppercase for case-insensitive checking.
 */
void ThreeWord_Board::load_dictionary() {
    ifstream file("dic.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open dic.txt. Dictionary will be empty.\n";
        return;
    }

    string word;
    while (file >> word) {
        // Convert word to uppercase
        transform(word.begin(), word.end(), word.begin(), ::toupper);
        if (word.length() == 3) {
            dictionary.insert(word);
        }
    }
    file.close();
    cout << "Loaded " << dictionary.size() << " valid 3-letter words.\n";
}

/**
 * @brief Checks if a 3-letter string is a valid word present in the dictionary.
 */
bool ThreeWord_Board::is_valid_word(const string& word) const {
    string upper_word = word;
    transform(upper_word.begin(), upper_word.end(), upper_word.begin(), ::toupper);
    return dictionary.count(upper_word);
}

ThreeWord_Board::ThreeWord_Board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;

    load_dictionary();
}

bool ThreeWord_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        return false;
    }

    if (board[x][y] != blank_symbol) {

        return false;
    }

    if (isalpha(mark)) {
        n_moves++;
        board[x][y] = toupper(mark);
        return true;
    }

    return false; // Invalid symbol (not a letter)
}

/**
 * @brief Checks all 8 possible lines (rows, columns, diagonals) for a valid 3-letter word.
 */
bool ThreeWord_Board::is_win(Player<char>* player) {

    auto is_filled = [&](char a, char b, char c) {
        return a != blank_symbol && b != blank_symbol && c != blank_symbol;
    };

    // Check rows
    for (int i = 0; i < rows; ++i) {
        if (is_filled(board[i][0], board[i][1], board[i][2])) {
            string word(1, board[i][0]);
            word += board[i][1];
            word += board[i][2];
            if (is_valid_word(word)) return true;
        }
    }

    // Check columns
    for (int i = 0; i < columns; ++i) {
        if (is_filled(board[0][i], board[1][i], board[2][i])) {
            string word(1, board[0][i]);
            word += board[1][i];
            word += board[2][i];
            if (is_valid_word(word)) return true;
        }
    }

    // Main diagonal
    if (is_filled(board[0][0], board[1][1], board[2][2])) {
        string word(1, board[0][0]);
        word += board[1][1];
        word += board[2][2];
        if (is_valid_word(word)) return true;
    }

    // Anti-diagonal
    if (is_filled(board[0][2], board[1][1], board[2][0])) {
        string word(1, board[0][2]);
        word += board[1][1];
        word += board[2][0];
        if (is_valid_word(word)) return true;
    }

    return false;
}

/**
 * @brief Checks if the game has ended in a draw (board filled, no win).
 */
bool ThreeWord_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

/**
 * @brief Determines if the game is over.
 */
bool ThreeWord_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- WordGame_UI Implementation

WordGame_UI::WordGame_UI() : UI<char>("Welcome to the Three-Letter Word Game!", 4) {}

/**
 * @brief Custom setup for players.
 * The symbols are not 'X' or 'O', but any letter. However, we'll use a placeholder
 * symbol 'L' followed by the player number to distinguish them in the Player object,
 * but the actual move symbol will be the letter the player enters.
 * The base Player class requires a T symbol, so we'll pass '1' and '2' as T=char.
 *
 * NOTE: The original X-O setup used static_cast<T>('X') and 'O', which is reasonable.
 * For this game, the actual move symbol is determined *during* get_move.
 * We'll stick to 'X' and 'O' for the Player object's internal symbol, but prompt
 * for the actual *letter* in get_move.
 */
Player<char>** WordGame_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer (Random)" };

    // Player 1 setup
    string name1 = get_player_name("Player 1");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, 'X', type1);

    // Player 2 setup
    string name2 = get_player_name("Player 2");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, 'O', type2);

    return players;
}

Player<char>* WordGame_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << " (ID: " << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* WordGame_UI::get_move(Player<char>* player) {
    int x, y;
    char letter;
    Board<char>* boardPtr = player->get_board_ptr();

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << ", enter your move (row, col) and letter (e.g., 0 0 A): ";
        cin >> x >> y >> letter;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        // Simple random move for COMPUTER.
        // Note: A true AI would try to form words.
        x = rand() % boardPtr->get_rows();
        y = rand() % boardPtr->get_columns();
        // Computer plays a random letter 'A' through 'Z'
        letter = 'A' + (rand() % 26);
        cout << "\nComputer " << player->get_name() << " chose: " << x << " " << y << " " << letter << "\n";
    }

    return new Move<char>(x, y, toupper(letter));
}