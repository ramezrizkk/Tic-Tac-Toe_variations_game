/**
 * @file ObstaclesTTT_Classes.cpp
 * @brief Implementation of Obstacles Tic-Tac-Toe game classes.
 */
#include "ObstaclesTTT_Classes.h"

void ObstaclesTTT_Board::add_random_obstacles(int count) {
    // Find all empty cells
    vector<pair<int, int>> empty_cells;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] == blank_symbol) {
                empty_cells.push_back({ i, j });
            }
        }
    }

    // If not enough empty cells, add what we can
    if (empty_cells.size() < count) {
        count = empty_cells.size();
    }

    // Randomly pick 'count' cells and make them obstacles
    for (int i = 0; i < count; i++) {
        int random_index = rand() % empty_cells.size();
        int x = empty_cells[random_index].first;
        int y = empty_cells[random_index].second;

        board[x][y] = '#';  // Obstacle character

        // Remove from empty_cells so we don't pick it again
        empty_cells.erase(empty_cells.begin() + random_index);
    }
    n_moves += count;//might cause a problem if it's 1 because then the number of moves 
    //will change it's type between even and odd
    // but after this move the game will end anyway because if it's 1 this means that there's only one place remaining
    // and it will be filled with obstacle then the game will end in draw so maybe it won't ruin anything
    //because after we update the board we go and check if the game is draw or win... etc

}

bool ObstaclesTTT_Board::check_line(int x, int y, int dx, int dy, char symbol) {
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

bool ObstaclesTTT_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate bounds
    if (x < 0 || x >= rows || y < 0 || y >= columns) return false;

    // Validate cell is empty (not occupied by player or obstacle)
    if (board[x][y] != blank_symbol) return false;

    // Place piece
    board[x][y] = toupper(mark);
    last_x = x;
    last_y = y;
    n_moves++;

    // After every round (both players moved), add 2 obstacles
    if (n_moves % 2 == 0) {
        cout << "Adding 2 random obstacles..." << endl;
        add_random_obstacles(2);
    }

    return true;
}

ObstaclesTTT_Board::ObstaclesTTT_Board() : Board(6, 6) {
    // Initialize 6x6 board with blank symbols
    for (auto& row : board) {
        for (auto& cell : row) {
            cell = blank_symbol;
        }
    }
}

bool ObstaclesTTT_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();

    if (check_line(last_x, last_y, 0, 1, sym)) return true;   // Horizontal
    if (check_line(last_x, last_y, 1, 0, sym)) return true;   // Vertical
    if (check_line(last_x, last_y, 1, 1, sym)) return true;   // Diagonal
    if (check_line(last_x, last_y, 1, -1, sym)) return true;  // Anti-Diagonal

    return false;
}

bool ObstaclesTTT_Board::is_draw(Player<char>* player) {
    return (n_moves == 36 && !is_win(player));
}

bool ObstaclesTTT_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- ObstaclesTTT_UI Implementation

ObstaclesTTT_UI::ObstaclesTTT_UI() : UI<char>("Welcome to Four-in-a-Row!", 3) {}

Player<char>* ObstaclesTTT_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* ObstaclesTTT_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << ", enter x and y (0-5): ";
        cin >> x >> y;
    }
    else {
        // Random empty cell
        Board<char>* b = player->get_board_ptr();
        do {
            x = rand() % 6;
            y = rand() % 6;
        } while (b->get_cell(x, y) != '.');  // Keep trying until empty
    }

    return new Move<char>(x, y, player->get_symbol());
}