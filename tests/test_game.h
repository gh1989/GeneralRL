#ifndef TEST_GAME_H
#define TEST_GAME_H

#include "game_facade.h"
#include <vector>
#include <iostream>

class TestGame : public GameFacade {
public:
    TestGame();
    void reset() override;
    bool makeMove(int action) override;
    bool isGameOver() const override;
    std::vector<float> getBoardState() const override;
    std::vector<int> getValidActions() const override;
    void printBoard() const override;
    char getWinner() const override;

private:
    std::vector<float> state; // Example state representation
    bool gameOver;
    int currentPlayer; // 1 for Player 1, -1 for Player 2
};

#endif
