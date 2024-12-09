#include "trainer.h"
#include "environment.h"
#include "agent.h"
#include "tictactoe_game.h"
#include <cassert>

void testTrainer() {
    torch::Device device(torch::kCPU);
    auto game = std::make_shared<TicTacToeGame>();
    Environment env(game);
    Agent agent(device);

    Trainer trainer(env, agent);

    // Train for 1 episode
    trainer.train(1);
    std::cout << "Trainer test passed.\n";
}

int main() {
    testTrainer();
    return 0;
}
