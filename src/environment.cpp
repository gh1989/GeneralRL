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
    // Check for game over and determine reward
    done = game->isGameOver();
    float reward = 0.0;

    if (done) {
        reward = game->getWinner();
    }

    if (!isValidAction(action) && !done) {
        throw std::invalid_argument("Invalid action.");
    }

    // Apply the action
    if(!done)
    if (!game->makeMove(action)) {
        throw std::runtime_error("Failed to apply the action.");
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
