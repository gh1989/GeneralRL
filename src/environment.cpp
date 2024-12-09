#include "environment.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

Environment::Environment(std::shared_ptr<GameFacade> game)
    : game(std::move(game)) {
    reset();
}

std::vector<float> Environment::reset() {
    game->reset();
    done = false;
    return getState();
}

std::tuple<std::vector<float>, float, bool> Environment::step(int action) {
    if (done) {
        throw std::runtime_error("Cannot take actions in a finished game. Call reset() to start a new game.");
    }

    if (!isValidAction(action)) {
        throw std::invalid_argument("Invalid action.");
    }

    // Apply the action
    if (!game->makeMove(action)) {
        throw std::runtime_error("Failed to apply the action.");
    }

    // Check for game over and determine reward
    done = game->isGameOver();
    float reward = 0.0;

    if (done) {
        char winner = game->getWinner();
        if (winner == 'X') {
            reward = 1.0f; // Agent wins
        } else if (winner == 'O') {
            reward = -1.0f; // Opponent wins
        } else if (winner == 'D') {
            reward = 0.0f; // Draw
        }
    }

    return {getState(), reward, done};
}

std::vector<float> Environment::getState() const {
    return game->getBoardState();
}

std::vector<int> Environment::getValidActions() const {
    return game->getValidActions();
}

bool Environment::isValidAction(int action) const {
    const auto& validActions = getValidActions();
    return std::find(validActions.begin(), validActions.end(), action) != validActions.end();
}

void Environment::printState() const {
    game->printBoard();
}
