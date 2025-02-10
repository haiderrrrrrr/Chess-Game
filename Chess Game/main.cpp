#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int BOARD_SIZE = 8;
const char EMPTY = '.';
const char ROOK = 'R';
const char KNIGHT = 'N';
const char BISHOP = 'B';
const char QUEEN = 'Q';
const char KING = 'K';


void init_board(char board[][BOARD_SIZE]) {
    memset(board, EMPTY, BOARD_SIZE * BOARD_SIZE * sizeof(char));

    // Initialize other pieces
    char pieces[] = { ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK };

    for (int i = 0; i < BOARD_SIZE; i++) {
        board[0][i] = pieces[i];
        board[7][i] = tolower(pieces[i]);
    }
}

void display_board(char board[][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
}

void get_move(int &row_from, int &col_from, int &row_to, int &col_to) {
    cout << "Enter move (row_from col_from row_to col_to): ";
    cin >> row_from >> col_from >> row_to >> col_to;
}

bool is_valid_move(char board[][BOARD_SIZE], int row_from, int col_from, int row_to, int col_to, int player) {
    char piece = board[row_from][col_from];
    char target = board[row_to][col_to];

    // Check if the move is within the board
    if (row_from < 0 || row_from >= BOARD_SIZE || col_from < 0 || col_from >= BOARD_SIZE ||
        row_to < 0 || row_to >= BOARD_SIZE || col_to < 0 || col_to >= BOARD_SIZE) {
        return false;
    }

    // Check if there is a piece at the origin and if it belongs to the current player
    if (piece == EMPTY || isupper(piece) != (player == 0)) {
        return false;
    }

    // Check if the destination is not occupied by a piece of the same color
    if (target != EMPTY && isupper(target) == (player == 0)) {
        return false;
    }

    int row_diff = abs(row_to - row_from);
    int col_diff = abs(col_to - col_from);

    switch (toupper(piece)) {
        case ROOK: {
            if (row_diff > 0 && col_diff > 0) {
                return false;
            }

            int row_step = row_to > row_from ? 1 : -1;
            int col_step = col_to > col_from ? 1 : -1;
            int row, col;

            for (row = row_from + row_step, col = col_from + col_step;
                 row != row_to && col != col_to;
                 row += row_step, col += col_step) {
                if (board[row][col] != EMPTY) {
                    return false;
                }
            }
            break;
        }
        case KNIGHT: {
            if (!((row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2))) {
                return false;
            }
            break;
        }
        case BISHOP: {
            if (row_diff != col_diff) {
                                return false;
            }

            int row_step = row_to > row_from ? 1 : -1;
            int col_step = col_to > col_from ? 1 : -1;
            int row, col;

            for (row = row_from + row_step, col = col_from + col_step;
                 row != row_to && col != col_to;
                 row += row_step, col += col_step) {
                if (board[row][col] != EMPTY) {
                    return false;
                }
            }
            break;
        }
        case QUEEN: {
            if (row_diff != col_diff && (row_diff > 0 && col_diff > 0)) {
                return false;
            }

            int row_step = row_to > row_from ? 1 : -1;
            int col_step = col_to > col_from ? 1 : -1;
            int row, col;

            for (row = row_from + row_step, col = col_from + col_step;
                 row != row_to && col != col_to;
                 row += row_step, col += col_step) {
                if (board[row][col] != EMPTY) {
                    return false;
                }
            }
            break;
        }
        case KING: {
            if (row_diff > 1 || col_diff > 1) {
                return false;
            }
            break;
        }
        default:
            return false;
    }

    return true;
}

void update_board(char board[][BOARD_SIZE], int row_from, int col_from, int row_to, int col_to) {
    board[row_to][col_to] = board[row_from][col_from];
    board[row_from][col_from] = EMPTY;
}

int check_game_status(char board[][BOARD_SIZE]) {
    // Implement game status checking logic here
    return 0;
}

int main() {
    char board[BOARD_SIZE][BOARD_SIZE];
    init_board(board);
    display_board(board);

    int player = 0; // 0 for white, 1 for black
    int game_status = 0; // 0 for ongoing, 1 for white wins, 2 for black wins, 3 for draw

    while (game_status == 0) {
        cout << (player == 0 ? "White" : "Black") << " player's turn." << endl;
        int row_from, col_from, row_to, col_to;
        get_move(row_from, col_from, row_to, col_to);

        if (is_valid_move(board, row_from, col_from, row_to, col_to, player)) {
            update_board(board, row_from, col_from, row_to, col_to);
            display_board(board);
            game_status = check_game_status(board);
            player = 1 - player; // Switch players
        } else {
            cout << "Invalid move, try again." << endl;
        }
    }

    if (game_status == 1) {
        cout << "White wins!" << endl;
    } else if (game_status == 2) {
        cout << "Black wins!" << endl;
    } else {
        cout << "Draw!" << endl;
    }

    return 0;
}