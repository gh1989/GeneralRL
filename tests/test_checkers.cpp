#include "checkers_game.h"
#include <iostream>
#include <cassert>
#include <vector>

void testGenerateMovesInitialState() {
    std::cout << "Running test: GenerateMoves Initial State\n";
    CheckersGame game;

    auto moves = game.generateMoves();

    // Ensure that moves are generated for the initial state
    assert(!moves.empty() && "No moves generated for the initial state!");

    // Verify Player 1 moves only forward
    for (int move : moves) {
        int start = move / 64;
        int end = move % 64;

        int start_rank = start / 8;
        int start_file = start % 8;
        std::cout << start_rank << std::endl;
        assert(start_rank < 3 && "Player 1 pieces should be in the first three ranks");
        assert(end >= 0 && end < 64 && "Moves should stay within the board");
        assert(end > start && "Moves should be forward for Player 1");
    }

    std::cout << "Passed: GenerateMoves Initial State\n";
}

void testGenerateMovesNormalMoves() {
    std::cout << "Running test: GenerateMoves Normal Moves\n";
    CheckersGame game;

    // Set up a custom board state
    std::vector<int> customBoard(64, 0); // Empty board
    customBoard[28] = 1;  // Player 1 piece
    customBoard[37] = -1; // Player 2 piece (to be captured)
    game.setBoardState(customBoard);    // Apply the custom board state

    auto moves = game.generateMoves();

    // Expect only one capture move due to Checkers rules prioritizing captures
    assert(moves.size() == 1 && "Expected exactly 1 move for Player 1 (capture only)");
    int expectedCapture = 28 * 64 + 46; // 28 -> 46 (capture)
    assert(moves[0] == expectedCapture && "Expected capture move 28 -> 46");

    std::cout << "Passed: GenerateMoves Normal Moves\n";
}

void testGenerateMovesWithCaptures() {
    std::cout << "Running test: GenerateMoves With Captures\n";
    CheckersGame game;

    // Set up a capture scenario
    std::vector<int> customBoard(64, 0); // Empty board
    customBoard[28] = 1;  // Player 1 piece
    customBoard[37] = -1; // Player 2 piece (to be captured)
    game.setBoardState(customBoard);    // Apply the custom board state

    auto moves = game.generateMoves();

    // Expect one capture move
    assert(moves.size() == 1 && "Expected 1 capture move for Player 1");
    int expectedMove = 28 * 64 + 46; // 28 (start) -> 46 (end, jumping over 37)
    assert(moves[0] == expectedMove && "Expected capture move to position 46");

    std::cout << "Passed: GenerateMoves With Captures\n";
}

void testGenerateMovesNoMoves() {
    std::cout << "Running test: GenerateMoves No Moves\n";
    CheckersGame game;

    // Set up a board state where Player 1 has no valid moves
    std::vector<int> customBoard(64, 0); // Empty board
    customBoard[9] = -1; // Place a Player 2 piece blocking Player 1's move
    game.setBoardState(customBoard);    // Apply the custom board state

    auto moves = game.generateMoves();

    // Expect no valid moves
    assert(moves.empty() && "Expected no moves for Player 1");

    std::cout << "Passed: GenerateMoves No Moves\n";
}


void testApplyMoveNormalMove() {
    std::cout << "Running test: Apply Move - Normal Move\n";
    CheckersGame game;

    // Set up a custom board state
    std::vector<int> customBoard(64, 0); // Empty board
    customBoard[28] = 1;  // Player 1 piece
    game.setBoardState(customBoard);    // Apply the custom board state

    // Apply a normal move (28 -> 19)
    int action = 28 * 64 + 19;
    bool success = game.makeMove(action);

    // Validate the board state after the move
    assert(success && "Normal move should succeed");
    auto board = game.getBoardState();
    assert(board[28] == 0 && "The piece should have left the start square");
    assert(board[19] == 1 && "The piece should have moved to the target square");

    std::cout << "Passed: Apply Move - Normal Move\n";
}

void testApplyMoveCapture() {
    std::cout << "Running test: Apply Move - Capture\n";
    CheckersGame game;

    // Set up a capture scenario
    std::vector<int> customBoard(64, 0); // Empty board
    customBoard[28] = 1;  // Player 1 piece
    customBoard[37] = -1; // Player 2 piece to be captured
    game.setBoardState(customBoard);    // Apply the custom board state

    // Apply a capture move (28 -> 46, capturing 37)
    int action = 28 * 64 + 46;
    bool success = game.makeMove(action);

    // Validate the board state after the capture
    assert(success && "Capture move should succeed");
    auto board = game.getBoardState();
    assert(board[28] == 0 && "The piece should have left the start square");
    assert(board[37] == 0 && "The captured piece should be removed");
    assert(board[46] == 1 && "The piece should have moved to the target square");

    std::cout << "Passed: Apply Move - Capture\n";
}
int main() {
    testGenerateMovesInitialState();
    testGenerateMovesNormalMoves();
    testGenerateMovesWithCaptures();
    testGenerateMovesNoMoves();
    testApplyMoveNormalMove();
    testApplyMoveCapture();
    std::cout << "All tests passed!\n";
    return 0;
}
