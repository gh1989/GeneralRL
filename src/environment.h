#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "game_facade.h"
#include <vector>
#include <tuple>
#include <torch/torch.h>
#include <memory>

class Environment {
public:
    explicit Environment(std::shared_ptr<GameFacade> game);

    std::vector<float> reset();
    std::tuple<std::vector<float>, float, bool> step(int action);
    std::vector<float> getState() const;
    std::vector<int> getValidActions() const;
    void printState() const;

private:
    std::shared_ptr<GameFacade> game;  // Use GameFacade for flexibility
    bool done = false;
    bool isValidAction(int action) const;
};

#endif