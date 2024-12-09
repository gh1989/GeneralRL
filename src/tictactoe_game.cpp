#include "tictactoe_game.h"
#include <algorithm>
#include <array>

TicTacToeGame::TicTacToeGame() {
    reset();
}

void TicTacToeGame::reset() {
    board = std::vector<char>(9, ' ');
    currentPlayer = 'X';
    gameOver = false;
    winner = ' ';
}

bool TicTacToeGame::makeMove(int action) {
    if (action < 0 || action >= 9 || board[action] != ' ') {
        return false; // Invalid move
    }

    board[action] = currentPlayer;

    // Winning line indices (rows, columns, diagonals)
    static const std::array<std::array<int, 3>, 8> winningLines = {{
        {0, 1, 2}, // Top row
        {3, 4, 5}, // Middle row
        {6, 7, 8}, // Bottom row
        {0, 3, 6}, // Left column
        {1, 4, 7}, // Middle column
        {2, 5, 8}, // Right column
        {0, 4, 8}, // Diagonal (top-left to bottom-right)
        {2, 4, 6}  // Diagonal (top-right to bottom-left)
    }};

    // Check if the current player has a winning line
    for (const auto& line : winningLines) {
        if (board[line[0]] == currentPlayer &&
            board[line[1]] == currentPlayer &&
            board[line[2]] == currentPlayer) {
            gameOver = true;
            winner = currentPlayer;
            return true;
        }
    }

    // Check for a draw (no empty spaces left)
    if (std::all_of(board.begin(), board.end(), [](char c) { return c != ' '; })) {
        gameOver = true;
        winner = 'D'; // Draw
    } else {
        // Switch to the other player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return true;
}

bool TicTacToeGame::isGameOver() const {
    return gameOver;
}

std::vector<float> TicTacToeGame::getBoardState() const {
    std::vector<float> state(9);
    for (size_t i = 0; i < board.size(); ++i) {
        if (board[i] == 'X') {
            state[i] = 1.0f;
        } else if (board[i] == 'O') {
            state[i] = -1.0f;
        } else {
            state[i] = 0.0f;
        }
    }
    return state;
}

std::vector<int> TicTacToeGame::getValidActions() const {
    std::vector<int> validActions;
    for (size_t i = 0; i < board.size(); ++i) {
        if (board[i] == ' ') {
            validActions.push_back(static_cast<int>(i));
        }
    }
    return validActions;
}

void TicTacToeGame::printBoard() const {
    for (size_t i = 0; i < board.size(); i += 3) {
        std::cout << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << "\n";
        if (i < 6) std::cout << "---------\n";
    }
}

char TicTacToeGame::getWinner() const {
    return winner;
}