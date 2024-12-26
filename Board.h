#ifndef BOARD_H
#define BOARD_H
#include <array>
#include <string>
#include "Tile.h"

const std::string kResetColor = "\033[0m";
const std::string kGreen = "\033[32m";

class Board {
    // Creates a 1-D array using dynamic memory allocation
    // Initializes mine count
    private:
        int m_height;
        int m_width;
        int m_size;
        Tile *m_board {nullptr};
        int m_mine_count;
        int m_mine_revealed;
        bool m_gameStatus;
        bool m_gameWon;

    // Three functions to place the mines and to print the board with the mines laid
    public: 
        void place_mines();
        void update_counts();
        void revealed_board() const;
        void play_board(int, int);                                  // A function to check the tile entered by the player
        bool check_game_status() const { return m_gameStatus; }     // Returns game status in main
        bool check_win() const { return m_gameWon; }                // Check if the game has been won or not

        // Constructor
        Board();
        Board(int, int, int);                                       // width, height, and mine count
        // Destructor
        ~Board();                                                   // Deallocate memory for board
};

#endif