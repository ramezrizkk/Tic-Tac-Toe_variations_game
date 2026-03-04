#include "FourInRow_Classes.h"
#include <iostream>
#include <cctype>
using namespace std;


FourInRow_Board::FourInRow_Board() : Board(6 , 7) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;

}

int FourInRow_Board::find_empty_row(int column)
{
    for (int i = rows - 1; i >= 0; i--) {
        if (board[i][column] == blank_symbol) {
            return i;
        }
    }
    return -1;
}

bool FourInRow_Board::check_line(int x, int y, int dx, int dy, char symbol) {
    int count = 1;  // Count the piece at (x, y) itself

    // Check in positive direction (forward)
    int nx = x + dx;
    int ny = y + dy;
    while (nx >= 0 && nx < rows && ny >= 0 && ny < columns && board[nx][ny] == symbol) {
        count++;
        nx += dx;
        ny += dy;
    }

    // Check in negative direction (backward)
    nx = x - dx;
    ny = y - dy;
    while (nx >= 0 && nx < rows && ny >= 0 && ny < columns && board[nx][ny] == symbol) {
        count++;
        nx -= dx;
        ny -= dy;
    }

    return count >= 4;
}

bool FourInRow_Board::update_board(Move<char>*move) {
    int column = move->get_y();
    char symbol = move->get_symbol();

    if (column < 0 || column >= columns) return false;

    int row = find_empty_row(column);
    if (row == -1) return false;  // Column full

    board[row][column] = toupper(symbol);

    // store last move position
    last_x = row;
    last_y = column;

    n_moves++;
    return true;
}

bool FourInRow_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();
    int x = last_x;
    int y = last_y;

    // Only check 4 directions from the last move
    if (check_line(x, y, 0, 1, sym)) return true;   // Horizontal
    if (check_line(x, y, 1, 0, sym)) return true;   // Vertical  
    if (check_line(x, y, 1, 1, sym)) return true;   // Diagonal
    if (check_line(x, y, 1, -1, sym)) return true;  // Anti-Diagonal

    return false;
}

bool FourInRow_Board::is_draw(Player<char>* player) {
    return (n_moves == 42 && !is_win(player));
}

bool FourInRow_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- FourInRow_UI Implementation

FourInRow_UI::FourInRow_UI() : UI<char>("Welcome to Four-in-a-Row!", 3) {}

Player<char>* FourInRow_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* FourInRow_UI::get_move(Player<char>* player) {
    int column;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease " << player->get_name() << " enter column (0-6): ";
        cin >> column;
    }
    else {
        column = rand() % 7;  // 0 to 6
        cout << player->get_name() << " chooses column " << column << "\n";
    }

    return new Move<char>(0, column, player->get_symbol()); //we will get x later from find empty row function
}
