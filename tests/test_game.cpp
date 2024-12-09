#include "test_game.h"
#include <algorithm>

TestGame::TestGame() {
    reset();
}

void TestGame::reset() {
    // Reset the game state
    state = {0.0, 0.0, 0.0}; // Example: A simple 1D state with 3 positions
    gameOver = false;
    currentPlayer = 1; // Player 1 starts
}

bool TestGame::makeMove(int action) {
    if (action < 0 || action >= static_cast<int>(state.size()) || state[action] != 0.0) {
        return false; // Invalid move
    }

    state[action] = static_cast<float>(currentPlayer); // Mark the move
    currentPlayer *= -1; // Switch player
    gameOver = std::all_of(state.begin(), state.end(), [](float val) { return val != 0.0; });
    return true;
}

bool TestGame::isGameOver() const {
    return gameOver;
}

std::vector<float> TestGame::getBoardState() const {
    return state;
}

std::vector<int> TestGame::getValidActions() const {
    std::vector<int> validActions;
    for (size_t i = 0; i < state.size(); ++i) {
        if (state[i] == 0.0) {
            validActions.push_back(static_cast<int>(i));
        }
    }
    return validActions;
}

void TestGame::printBoard() const {
    std::cout << "Game state: ";
    for (float val : state) {
        std::cout << (val == 1.0 ? "X" : (val == -1.0 ? "O" : ".")) << " ";
    }
    std::cout << "\n";
}

char TestGame::getWinner() const {
    // TestGame always ends in a draw for simplicity
    return 'D';
}
