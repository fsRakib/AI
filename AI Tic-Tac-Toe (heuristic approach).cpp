
#include <iostream>
#include <vector>
#include <cstdlib>  // For random numbers
#include <ctime>    // For time-based randomness

using namespace std;

const int SIZE = 4;  // Board size (4x4 for Tic-Tac-Toe)
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
        if (i < SIZE - 1) cout << "---|---|---|---\n";
    }
    cout << "\n";
}

// Function to check for a winner
char checkWinner() {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][2] == board[i][3] && board[i][0] != ' ') return board[i][0];  // Row check
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[2][i] == board[3][i] && board[0][i] != ' ') return board[0][i];  // Column check
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[2][2] == board[3][3] && board[0][0] != ' ') return board[0][0];  // Top-left to bottom-right
    if (board[0][3] == board[1][2] && board[1][2] == board[2][1] && board[2][1] == board[3][0] && board[0][3] != ' ') return board[0][3];  // Top-right to bottom-left

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

// Function to get a list of available moves
vector<pair<int, int>> getAvailableMoves() {
    vector<pair<int, int>> moves;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                moves.push_back({i, j});
            }
        }
    }
    return moves;
}

// AI move strategy: prioritize winning or blocking
pair<int, int> findBestMove() {
    // First, try to find a winning move
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';  // Try AI move
                if (checkWinner() == 'O') {
                    board[i][j] = ' ';  // Undo move
                    return {i, j};  // AI wins
                }
                board[i][j] = ' ';  // Undo move
            }
        }
    }

    // Second, try to block the player from winning
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'X';  // Try player move
                if (checkWinner() == 'X') {
                    board[i][j] = ' ';  // Undo move
                    return {i, j};  // Block player
                }
                board[i][j] = ' ';  // Undo move
            }
        }
    }

    // If no winning or blocking moves, choose a random move
    vector<pair<int, int>> availableMoves = getAvailableMoves();
    srand(time(0));  // Seed for randomness
    int randomIndex = rand() % availableMoves.size();
    return availableMoves[randomIndex];
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
