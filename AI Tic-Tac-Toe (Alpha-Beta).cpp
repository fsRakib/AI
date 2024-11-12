#include <bits/stdc++.h>
using namespace std;

const int SIZE = 4; // Board size
const int WINNING_LENGTH = 4; // Winning length (4 in a row)
const char HUMAN = 'X';
const char COMPUTER = 'O';
const char EMPTY = '_';

// Function to print the board
void printBoard(const vector<vector<char>>& board) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Check if a player has won
bool isGameOver(const vector<vector<char>>& board, char player) {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j <= SIZE - WINNING_LENGTH; j++) {
            bool winRow = true, winCol = true;
            for (int k = 0; k < WINNING_LENGTH; k++) {
                if (board[i][j + k] != player) winRow = false;
                if (board[j + k][i] != player) winCol = false;
            }
            if (winRow || winCol) return true;
        }
    }
    // Check diagonals
    for (int i = 0; i <= SIZE - WINNING_LENGTH; i++) {
        for (int j = 0; j <= SIZE - WINNING_LENGTH; j++) {
            bool winDiag1 = true, winDiag2 = true;
            for (int k = 0; k < WINNING_LENGTH; k++) {
                if (board[i + k][j + k] != player) winDiag1 = false;
                if (board[i + k][j + WINNING_LENGTH - 1 - k] != player) winDiag2 = false;
            }
            if (winDiag1 || winDiag2) return true;
        }
    }
    return false;
}

// Evaluate board state
int evaluate(const vector<vector<char>>& board) {
    if (isGameOver(board, COMPUTER)) return 10;
    if (isGameOver(board, HUMAN)) return -10;
    return 0;
}

// Check if there are moves left
bool isMovesLeft(const vector<vector<char>>& board) {
    for (const auto& row : board)
        for (char cell : row)
            if (cell == EMPTY) return true;
    return false;
}

// Minimax algorithm with alpha-beta pruning
int minimax(vector<vector<char>>& board, int depth, bool isMax, int alpha, int beta) {
    int score = evaluate(board);
    if (score == 10 || score == -10 || depth == 0 || !isMovesLeft(board)) return score;

    if (isMax) {
        int best = INT_MIN;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = COMPUTER;
                    best = max(best, minimax(board, depth - 1, false, alpha, beta));
                    board[i][j] = EMPTY;
                    alpha = max(alpha, best);
                    if (beta <= alpha) return best;
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = HUMAN;
                    best = min(best, minimax(board, depth - 1, true, alpha, beta));
                    board[i][j] = EMPTY;
                    beta = min(beta, best);
                    if (beta <= alpha) return best;
                }
            }
        }
        return best;
    }
}

// Find the best move for the computer
pair<int, int> findBestMove(vector<vector<char>>& board) {
    int bestValue = INT_MIN;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = COMPUTER;
                int moveValue = minimax(board, 3, false, INT_MIN, INT_MAX);
                board[i][j] = EMPTY;
                if (moveValue > bestValue) {
                    bestMove = {i, j};
                    bestValue = moveValue;
                }
            }
        }
    }
    return bestMove;
}

// Main function
int main() {
    vector<vector<char>> board(SIZE, vector<char>(SIZE, EMPTY));
    printBoard(board);

    while (true) {
        int row, col;
        cout << "Enter row and column (1-based index): ";
        cin >> row >> col;
        row--; col--; // Convert to 0-based indexing for internal processing

        if (row < 0 || col < 0 || row >= SIZE || col >= SIZE || board[row][col] != EMPTY) {
            cout << "Invalid move. Try again." << endl;
            continue;
        }

        board[row][col] = HUMAN;
        if (isGameOver(board, HUMAN)) {
            printBoard(board);
            cout << "You won!" << endl;
            break;
        }

        auto [bestRow, bestCol] = findBestMove(board);
        board[bestRow][bestCol] = COMPUTER;
        printBoard(board);

        if (isGameOver(board, COMPUTER)) {
            cout << "Computer won!" << endl;
            break;
        }

        if (!isMovesLeft(board)) {
            cout << "It's a tie!" << endl;
            break;
        }
    }

    return 0;
}
