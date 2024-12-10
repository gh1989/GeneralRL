#ifndef NETWORK_H
#define NETWORK_H

#include <torch/torch.h>

struct GeneralGameNet : torch::nn::Module {
    explicit GeneralGameNet(torch::Device device, int inputSize, int actionSize)
        : device(device), inputSize(inputSize), actionSize(actionSize) {
        // Define layers dynamically based on input and action sizes
        fc1 = register_module("fc1", torch::nn::Linear(inputSize, 64));
        fc2 = register_module("fc2", torch::nn::Linear(64, 64));
        policyHead = register_module("policyHead", torch::nn::Linear(64, actionSize)); // Action size
        valueHead = register_module("valueHead", torch::nn::Linear(64, 1));           // Scalar value

        // Move the model to the specified device
        this->to(device);
    }

    std::tuple<torch::Tensor, torch::Tensor> forward(torch::Tensor x) {
        x = x.to(device); // Ensure input tensor is on the correct device
        x = torch::relu(fc1->forward(x));
        x = torch::relu(fc2->forward(x));
        auto policy = torch::softmax(policyHead->forward(x), 1);
        auto value = torch::tanh(valueHead->forward(x));
        return std::make_tuple(policy, value);
    }

private:
    torch::Device device;        // Store the device
    int inputSize;               // Input size (e.g., 9 for Tic-Tac-Toe, 64 for Checkers)
    int actionSize;              // Number of possible actions
    torch::nn::Linear fc1{nullptr}, fc2{nullptr}, policyHead{nullptr}, valueHead{nullptr};
};

#endif