#include "trainer.h"
#include "environment.h"
#include "agent.h"
#include "checkers_game.h" // Include CheckersGame implementation
#include <torch/torch.h>
#include <iostream>
#include <fstream>
#include <memory>

int main() {
    // Device configuration
    torch::Device device(torch::kCUDA);

    // Training configuration
    int numEpisodes = 100000;       // Number of training episodes
    float initialEpsilon = 0.25;     // Initial exploration rate
    float epsilonDecay = 0.99;      // Decay rate for exploration
    float minEpsilon = 0.01;        // Minimum exploration rate
    float learningRate = 1e-3;      // Learning rate for optimizer
    std::string modelPath = "checkers_model.pt";

    // Create the game instance (Checkers in this case)
    auto game = std::make_shared<CheckersGame>();

    // Create environment and agent
    Environment env(game);
    Agent agent(device, 64, 4096, learningRate);

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
