#ifndef TICTACTOE_GAME_H
#define TICTACTOE_GAME_H

#include "game_facade.h"
#include <vector>
#include <iostream>

class TicTacToeGame : public GameFacade {
public:
    TicTacToeGame();
    void reset() override;
    bool makeMove(int action) override;
    bool isGameOver() const override;
    std::vector<float> getBoardState() const override;
    std::vector<int> getValidActions() const override;
    void printBoard() const override;
    char getWinner() const override;

private:
    std::vector<char> board;
    char currentPlayer;
    bool gameOver;
    char winner;
};

#endif