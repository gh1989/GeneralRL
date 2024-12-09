#ifndef GAME_FACADE_H
#define GAME_FACADE_H

#include <vector>
#include <string>
#include <memory>

class GameFacade {
public:
    virtual ~GameFacade() = default;

    // Reset the game to its initial state
    virtual void reset() = 0;

    // Apply a move and return true if successful
    virtual bool makeMove(int action) = 0;

    // Check if the game has ended
    virtual bool isGameOver() const = 0;

    // Get the current board state
    virtual std::vector<float> getBoardState() const = 0;

    // Get a list of valid actions
    virtual std::vector<int> getValidActions() const = 0;

    // Print the current board state
    virtual void printBoard() const = 0;

    // Optional: Return the winner
    virtual char getWinner() const = 0;
};

#endif
