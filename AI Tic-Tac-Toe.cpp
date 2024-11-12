#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int SIZE = 4;  // Board size (3x3 for Tic-Tac-Toe)
vector<vector<char>> board(SIZE, vector<char>(SIZE, ' '));  // Initialize empty board

// Function to display the board
void displayBoard() {
    cout << "\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << " " << board[i][j] << " ";
            if (j < SIZE - 1) cout << "|";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "---|---|---\n";
    }
    cout << "\n";
}

// Function to check for a winner
char checkWinner() {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') return board[i][0];  // Row check
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') return board[0][i];  // Column check
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') return board[0][0];  // Top-left to bottom-right
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') return board[0][2];  // Top-right to bottom-left

    return ' ';  // No winner
}

// Function to check if the board is full (draw condition)
bool isBoardFull() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

// Minimax algorithm to find the best move for the AI
int minimax(int depth, bool isMaximizingPlayer) {
    char winner = checkWinner();
    if (winner == 'X') return -1;  // Player wins
    if (winner == 'O') return 1;   // AI wins
    if (isBoardFull()) return 0;   // Draw

    if (isMaximizingPlayer) {
        int best = INT_MIN;  // Maximize AI's score
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';  // AI's move
                    best = max(best, minimax(depth + 1, false));
                    board[i][j] = ' ';  // Undo move
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;  // Minimize player's score
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';  // Player's move
                    best = min(best, minimax(depth + 1, true));
                    board[i][j] = ' ';  // Undo move
                }
            }
        }
        return best;
    }
}

// Function to find the best move for AI using Minimax
pair<int, int> findBestMove() {
    int bestVal = INT_MIN;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';  // AI's move
                int moveVal = minimax(0, false);
                board[i][j] = ' ';  // Undo move
                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

// Main game loop with AI
void playGame() {
    char currentPlayer = 'X';  // Human starts first
    while (true) {
        displayBoard();

        if (currentPlayer == 'X') {
            // Player's move
            int row, col;
            cout << "Player X, enter your move (row and column): ";
            cin >> row >> col;

            // Validate input
            if (row < 1 || row > SIZE || col < 1 || col > SIZE || board[row - 1][col - 1] != ' ') {
                cout << "Invalid move. Try again.\n";
                continue;
            }

            board[row - 1][col - 1] = currentPlayer;
        } else {
            // AI's move
            cout << "AI (Player O) is making a move...\n";
            pair<int, int> bestMove = findBestMove();
            board[bestMove.first][bestMove.second] = currentPlayer;
        }

        // Check for a winner
        char winner = checkWinner();
        if (winner != ' ') {
            displayBoard();
            cout << "Player " << winner << " wins!\n";
            break;
        }

        // Check for a draw
        if (isBoardFull()) {
            displayBoard();
            cout << "It's a draw!\n";
            break;
        }

        // Switch player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

int main() {
    cout << "Welcome to Tic-Tac-Toe! You are X and the AI is O.\n";
    playGame();
    return 0;
}
