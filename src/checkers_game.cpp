#include "checkers_game.h"
#include <iostream>
#include <algorithm>

CheckersGame::CheckersGame() {
    reset();
}

void CheckersGame::reset() {
    board.resize(64, 0); // 8x8 board, initially empty
    currentPlayer = 1;   // Player 1 starts
    gameOver = false;
    winner = ' ';
    movesSinceCapture = 0;
    initializeBoard();
}

void CheckersGame::initializeBoard() {
    int rank, file;

    for (int i=0; i<24; i++)
    {
        rank = i / 8;
        file = i % 8;
        if( (rank % 2) ^ (file %2) )
            board[i] = 1;
    }

    for (int i=40; i<64; i++)
    {
        rank = i / 8;
        file = i % 8;
        if( (rank % 2) ^ (file %2) )
            board[i] = -1;
    }
}


bool CheckersGame::makeMove(int action) {
    if (isGameOver()) {
        return false;
    }
    applyMove(action);
    checkGameOver();
    if (!gameOver) {
        currentPlayer *= -1; // Switch player
    }
    return true;
}

bool CheckersGame::isGameOver() const {
    return gameOver;
}

std::vector<float> CheckersGame::getBoardState() const {
    return std::vector<float>(board.begin(), board.end());
}

std::vector<int> CheckersGame::getValidActions() const {

    return generateMoves();
}

void CheckersGame::printBoard() const {
    std::cout << "Checkers Board:\n";
    for (int i = 0; i < 64; ++i) {
        if (i % 8 == 0) std::cout << "\n";
        if (board[i] == 0) std::cout << ". ";
        else if (board[i] == 1) std::cout << "m ";
        else if (board[i] == 2) std::cout << "M ";
        else if (board[i] == -1) std::cout << "o ";
        else if (board[i] == -2) std::cout << "O ";
    }
    std::cout << "\n";
}

char CheckersGame::getWinner() const {
    return winner;
}
std::vector<int> CheckersGame::generateMoves() const {
    std::vector<int> moves;
    bool captureAvailable = false;
    int mid, end, rank, file;

    for (size_t i = 0; i < board.size(); ++i) {
        int piece = board[i];

        // Skip empty squares
        if (piece == 0)
            continue;

        rank = i / 8;  // Row (rank)
        file = i % 8;  // Column (file)     

        if(currentPlayer == 1)
        {
            if(piece >= 1)
            {
                if( (file>1) && (rank<6) )
                {
                    mid = (rank+1)*8 + file-1;
                    end = (rank+2)*8 + file-2;
                    if( (board[mid] <= -currentPlayer) && (board[end] == 0) )
                    {
                        moves.push_back(i*64 + end);
                        captureAvailable = true;
                    }
                }
                if( (file < 6) && (rank<6) )
                {
                    mid = (rank+1)*8 + file+1;
                    end = (rank+2)*8 + file+2;
                    if( (board[mid] <= -currentPlayer) && (board[end] == 0) )
                    {
                        moves.push_back(i*64 + end);
                        captureAvailable = true;
                    }
                }
            }
            if(piece == 2)
            {
                if( (file > 1) && (rank>1) )
                {
                    mid = (rank-1)*8 + file-1;
                    end = (rank-2)*8 + file-2;
                    if( (board[mid] <= -currentPlayer) && (board[end] == 0) )
                    {
                        moves.push_back(i*64 + end);
                        captureAvailable = true;
                    }
                }
                if( (file < 6) && (rank>1) )
                {
                    mid = (rank-1)*8 + file+1;
                    end = (rank-2)*8 + file+2;
                    if( (board[mid] <= -currentPlayer) && (board[end] == 0) )
                    {
                        moves.push_back(i*64 + end);
                        captureAvailable = true;
                    }
                }
            }
        }

        if(currentPlayer == -1)
        {
            if(piece <= -1)
            {
                if( (file > 1) && (rank>1) )
                {
                    mid = (rank-1)*8 + file-1;
                    end = (rank-2)*8 + file-2;
                    if( (board[mid] >= -currentPlayer) && (board[end] == 0) )
                    {
                        moves.push_back(i*64 + end);
                        captureAvailable = true;
                    }
                }
                if( (file < 6) && (rank>1) )
                {
                    mid = (rank-1)*8 + file+1;
                    end = (rank-2)*8 + file+2;
                    if( (board[mid] >= -currentPlayer) && (board[end] == 0) )
                    {
                        moves.push_back(i*64 + end);
                        captureAvailable = true;
                    }
                }
            }
            if(piece == -2)
            {
                if( (file > 1) && (rank<6) )
                {
                    mid = (rank+1)*8 + file-1;
                    end = (rank+2)*8 + file-2;
                    if( (board[mid] >= -currentPlayer) && (board[end] == 0) )
                    {
                        moves.push_back(i*64 + end);
                        captureAvailable = true;
                    }
                }
                if( (file < 6) && (rank<6) )
                {
                    mid = (rank+1)*8 + file+1;
                    end = (rank+2)*8 + file+2;
                    if( (board[mid] >= -currentPlayer) && (board[end] == 0) )
                    {
                        moves.push_back(i*64 + end);
                        captureAvailable = true;
                    }
                }
            }
        }
    
    }

    if(!captureAvailable)
    for (size_t i = 0; i < board.size(); ++i) {
        int piece = board[i];

        // Skip empty squares
        if (piece == 0)
            continue;

        rank = i / 8;  // Row (rank)
        file = i % 8;  // Column (file)        

        if(currentPlayer == 1)
        {
            if(piece >= 1)
            {
                if( (file > 0) && (rank<7) )
                {
                    end = (rank+1)*8 + file-1;
                    if( board[end] == 0 )
                        moves.push_back(i*64 + end);
                }
                if( (file < 7) && (rank<7) )
                {
                    end = (rank+1)*8 + file+1;
                    if( board[end] == 0 )
                        moves.push_back(i*64 + end);
                }
            }
            if(piece == 2)
            {
                if( (file > 0) && (rank>0) )
                {
                    end = (rank-1)*8 + file-1;
                    if( board[end] == 0 )
                        moves.push_back(i*64 + end);
                }
                if( (file < 7) && (rank>0) )
                {
                    end = (rank-1)*8 + file+1;
                    if( board[end] == 0 )
                        moves.push_back(i*64 + end);
                }
            }
        }

        if(currentPlayer == -1)
        {
            if(piece <= -1)
            {
                if( (file > 0) && (rank>0) )
                {
                    end = (rank-1)*8 + file-1;
                    if( board[end] == 0 )
                        moves.push_back(i*64 + end);
                }
                if( (file < 7) && (rank>0) )
                {
                    end = (rank-1)*8 + file+1;
                    if( board[end] == 0 )
                        moves.push_back(i*64 + end);
                }
            }
            if(piece == -2)
            {
                if( (file > 0) && (rank<7) )
                {
                    end = (rank+1)*8 + file-1;
                    if( board[end] == 0 )
                        moves.push_back(i*64 + end);
                }
                if( (file < 7) && (rank<7) )
                {
                    end = (rank+1)*8 + file+1;
                    if( board[end] == 0 )
                        moves.push_back(i*64 + end);
                }
            }
        }
            
    }

    return moves;
}


void CheckersGame::applyMove(int action) {
    // Decode the action into a move
    // Assuming action encodes start and end indices as (start * 64 + end)
    int start = action / 64;
    int end = action % 64;

    // Validate the start and end positions
    if (start < 0 || start >= 64 || end < 0 || end >= 64) {
        throw std::invalid_argument("Invalid action: Out of bounds.");
    }

    int piece = board[start];
    if (piece == 0 || (currentPlayer == 1 && piece < 0) || (currentPlayer == -1 && piece > 0)) {
        throw std::invalid_argument("Invalid action: No valid piece to move.");
    }

    // Check for captures (if the move jumps over an opponent's piece)
    int middle = (start + end) / 2;
    if (std::abs(start - end) == 18 || std::abs(start - end) == 14) 
    { // Capture move
        movesSinceCapture = 0;
        if (board[middle] == 0 || (board[middle] > 0 && currentPlayer == 1) || (board[middle] < 0 && currentPlayer == -1)) {
            throw std::invalid_argument("Invalid action: No valid capture.");
        }

        // Remove the captured piece
        board[middle] = 0;
    }
    else
        movesSinceCapture++;

    // Move the piece
    board[end] = piece;
    board[start] = 0;

    // Check for promotion (reaching the last row)
    if ((currentPlayer == 1 && end >= 56) || (currentPlayer == -1 && end < 8)) {
        board[end] = (currentPlayer == 1) ? 2 : -2; // Promote to king
    }

    //this->printBoard();
    this->checkGameOver();
}

void CheckersGame::checkGameOver() {
    // Count the pieces for both players
    int player1Pieces = 0;
    int player2Pieces = 0;

    for (int piece : board) {
        if (piece == 1 || piece == 2) { // Player 1's man or king
            player1Pieces++;
        } else if (piece == -1 || piece == -2) { // Player 2's man or king
            player2Pieces++;
        }
    }

    // Check if either player has no pieces
    if (player1Pieces == 0) {
        gameOver = true;
        winner = 1; // Player 1 wins
        return;
    }
    if (player2Pieces == 0) {
        gameOver = true;
        winner = -1; // Player 2 wins
        return;
    }

    // Check if either player has no valid moves
    auto player1Moves = generateMoves(); // Assuming currentPlayer is set
    gameOver = player1Moves.empty();
    if(gameOver)
        winner = currentPlayer;
    if(movesSinceCapture >= 40)
    {
        gameOver = true;
        winner = 0;
    }
}

void CheckersGame::setBoardState(const std::vector<int>& newBoard) {
    if (newBoard.size() != board.size()) {
        throw std::invalid_argument("Invalid board size! Expected size: " + std::to_string(board.size()));
    }
    board = newBoard;
}
