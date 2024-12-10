#ifndef CHECKERS_GAME_H
#define CHECKERS_GAME_H

#include "game_facade.h"
#include <vector>
#include <string>

class CheckersGame : public GameFacade {
public:
    CheckersGame();
    void reset() override;
    bool makeMove(int action) override;
    bool isGameOver() const override;
    std::vector<float> getBoardState() const override;
    void setBoardState(const std::vector<int>& newBoard);
    std::vector<int> getValidActions() const override;
    void printBoard() const override;
    char getWinner() const override;
    std::vector<int> generateMoves() const;
    void applyMove(int action);

private:
    std::vector<int> board; // 1D representation of 8x8 board
    int currentPlayer;      // 1 for Player 1, -1 for Player 2
    bool gameOver;
    char winner;

    void initializeBoard();
    void checkGameOver();
};

#endif
