#include "agent.h"
#include "environment.h"
#include "checkers_game.h"
#include <cassert>

void testAgent() {
    torch::Device device(torch::kCPU);
    Agent agent(device, 64, 64);
    auto game = std::make_shared<CheckersGame>();
    Environment env(game);
    std::vector<float> state = env.reset();
    std::vector<int> validActions = env.getValidActions();

    // Test action selection
    int action = agent.chooseAction(state, validActions, true);
    assert(std::find(validActions.begin(), validActions.end(), action) != validActions.end());
    std::cout << "Action selection test passed.\n";

    // Test policy update
    std::vector<Transition> transitions = {
        {state, action, 1.0f},
    };
    agent.updatePolicy(transitions);
    std::cout << "Policy update test passed.\n";
}

int main() {
    testAgent();
    return 0;
}
