#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <array>
#include "Board.h"
#include "Tile.h"

Board::Board() {
    m_width = 8;            
    m_height = 8;
    m_size = m_width * m_height;
    m_mine_count = 10;
    m_mine_revealed = 0;
    m_gameStatus = true;
    m_gameWon = false;
    m_board = new Tile[m_size];
    for(int row {0}; row < m_size; row++) {
        m_board[row].SetValue(0);
    }
}

Board::Board(int height, int width, int mine_count) { // Constructor that takes in width and height from user
    m_height = height;                               // Calculates size of the board and allocates memory for it using pointer
    m_width = width;
    m_size = width * height;
    m_mine_count = mine_count;
    m_mine_revealed = 0;
    m_gameStatus = true;                            // game status checks whether game is still running
    m_gameWon = false;                              // When the game stops running, the code will check this variable to see if the player won the game or not
    m_board = new Tile[m_size];
    for(int row {0}; row < m_size; row++) {
        m_board[row].SetValue(0);                   // Seeds every tile with value 0 by default
    }
}

void Board::place_mines() {
    // This function places down the mines using c random functions
    // mine keeps track of total mines placed until it reaches the mine count
    std::srand(time(NULL));
    for (int i{0}; i < m_mine_count && i < m_size; i++) { // and here checks to allows the player to place more mines than the board size can hold, ex: 5 5 30
        int mine_row = std::rand() % m_height;  // Selects random index values based on size of the grid, places a mine into that index if there isn't one
        int mine_col = std::rand() % m_width;   // and places a mine into that index if there isn't one

        if (m_board[mine_row * m_width + mine_col].GetValue() != 9) {
            m_board[mine_row * m_width + mine_col].SetValue(9);
        } else {
            i--;                                                    // decrements i if a mine was unable to be placed 
        }
    }
}

void Board::update_counts() {
    for (int row{0}; row < m_height; row++) {
        for (int col{0}; col < m_width; col++) {
            // Checks to see if there are mines adjacent to the current index tile and increments tile value by 1 each time, bounds checking
            if (m_board[m_width * row + col].GetValue() != 9 ) {
                if (row != 0 && m_board[m_width * (row - 1) + col].GetValue() == 9) {
                    m_board[m_width * row + col].AddValue();
                }
                if (row != (m_height - 1) && m_board[m_width * (row + 1) + col].GetValue() == 9) {
                    m_board[m_width * row + col].AddValue();
                }
                if (col != (m_width - 1) && m_board[m_width * row + (col + 1)].GetValue() == 9) {
                    m_board[m_width * row + col].AddValue();
                }
                if (col != 0 && m_board[m_width * row + (col - 1)].GetValue() == 9) {
                    m_board[m_width * row + col].AddValue();
                }
                if (row != 0 && col != 0 && m_board[m_width * (row - 1) + (col - 1)].GetValue() == 9) {
                    m_board[m_width * row + col].AddValue();
                }
                if (row != (m_height - 1) && col != m_width - 1 && m_board[m_width * (row + 1) + (col + 1)].GetValue() == 9) {
                    m_board[m_width * row + col].AddValue();
                }
                if (row != 0 && col != (m_width - 1) && m_board[m_width * (row - 1) + (col + 1)].GetValue() == 9) {
                    m_board[m_width * row + col].AddValue();
                }
                if (row != (m_height - 1) && col != 0 && m_board[m_width * (row + 1) + (col - 1)].GetValue() == 9) {
                    m_board[m_width * row + col].AddValue();
                }
            }
        }
    }
}

void Board::play_board(int row, int col) {
    if (m_board[m_width * row + col].GetValue() == 9) { // If you selected a mine
        m_board[m_width * row + col].SetStatusTrue();   // Reveal the mine
        m_gameStatus = false;                           // Game stops running, meaning you lost
    }
    
    else {
        m_board[m_width * row + col].SetStatusTrue();  // Reveal the tile selected if not mine
        m_mine_revealed++;                             // Up the mine revealed count

        if (m_mine_revealed == (m_width * m_height - m_mine_count)) {
            m_gameStatus = false;                                       // Game is won here if mine revealed count is equal to width * height - mine count
            m_gameWon = true;
        }
    } 
}

void Board::revealed_board() const {
    // This function prints the board in grid format after mines are placed
    std::cout << kGreen << std::setw(5) << "  ";
    for (int col_num {0}; col_num < m_width; col_num++) {
        if (col_num < 10) {
            std::cout << col_num << "  ";
        
        }
        std::cout << std::setw(2);
        if (col_num > 9) {
            std::cout << col_num << "  ";
        }
    }
    std::cout << std::endl;
    for (int row{0}; row < m_height; row++) {
        std::cout << "   ";
        for (int lines{0}; lines < m_width; lines++) {
            std::cout << "|---";
        }
        std::cout << "|";
        std::cout << std::endl;
        if (row > 9) {
            std::cout << row << " "; 
        } else {
            std::cout << row << "  ";
        }
        if (!m_gameStatus && !m_gameWon) {                            // If the player loses the game
            for (int col{0}; col < m_width; col++) {
                if (m_board[m_width * row + col].GetValue() == 9) {  // If there is a mine, print M in place of it
                    std::cout << "| " << 'M' << " ";
                }
                else {
                    std::cout << "| " << m_board[m_width * row + col].GetValue() << " ";
                }
            }
            std::cout << "|";
            std::cout << std::endl;
        }
        if (m_gameStatus && !m_gameWon) {                                                   // If game is running but not won yet
            for (int col{0}; col < m_width; col++) {
                if (!m_board[m_width * row + col].GetStatus()) {  
                    std::cout << "| " << '#' << " ";                                        // Print out hidden tile if tile not revealed
                }
                else {
                    std::cout << "| " << m_board[m_width * row + col].GetValue() << " ";    // If revealed, print the value
                }
            }
            std::cout << "|";
            std::cout << std::endl;
        }
        if (!m_gameStatus && m_gameWon) {                                                  // If the game is won
            for (int col{0}; col < m_width; col++) {
                if (!m_board[m_width * row + col].GetStatus()) {  
                    std::cout << "| " << '#' << " ";                                      // Print out the mines still hidden
                }
                else {
                    std::cout << "| " << m_board[m_width * row + col].GetValue() << " ";  // Print tiles revealed
                }
            }
            std::cout << "|";
            std::cout << std::endl;
        }
    }

    std::cout << std::setw(3) << "   ";
    for(int lines{0}; lines < m_width; lines++) {
            std::cout << "|---";
        }
    std::cout << "|" << std::endl;
}

Board::~Board() {
    delete[] m_board; // Deallocates memory from the heap
    m_board = nullptr;
}