#include "trainer.h"
#include "environment.h"
#include "agent.h"
#include "tictactoe_game.h" // For Tic-Tac-Toe implementation
#include <torch/torch.h>
#include <iostream>
#include <fstream>
#include <memory>

int main() {
    // Device configuration
    torch::Device device(torch::cuda::is_available() ? torch::kCUDA : torch::kCPU);
    std::cout << "Using device: " << (torch::cuda::is_available() ? "GPU" : "CPU") << "\n";

    // Training configuration
    int numEpisodes = 100000;       // Number of training episodes
    float initialEpsilon = 1;  // Initial exploration rate
    float epsilonDecay = 0.99;   // Decay rate for exploration
    float minEpsilon = 0.01;      // Minimum exploration rate
    float learningRate = 1e-2;   // Learning rate for optimizer
    std::string modelPath = "tictactoe_model.pt";

    // Create the game instance (Tic-Tac-Toe in this case)
    auto game = std::make_shared<TicTacToeGame>();

    // Create environment and agent
    Environment env(game);
    Agent agent(device, learningRate);

    // Configure epsilon decay
    agent.setEpsilon(initialEpsilon, epsilonDecay, minEpsilon);

    // Load existing model if available
    std::ifstream modelFile(modelPath);
    if (modelFile.good()) {
        agent.loadModel(modelPath);
        std::cout << "Loaded model from " << modelPath << "\n";
    } else {
        std::cout << "No existing model found. Training from scratch.\n";
    }

    // Create trainer
    Trainer trainer(env, agent);

    // Train the agent
    std::cout << "Starting training for " << numEpisodes << " episodes...\n";
    trainer.train(numEpisodes);

    // Save the trained model
    agent.saveModel(modelPath);

    std::cout << "Training complete. Model saved to " << modelPath << "\n";
    return 0;
}
