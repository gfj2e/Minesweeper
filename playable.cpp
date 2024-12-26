/* Garrett Johnson
*  2170-002
*  Filename: minesweeper.cpp, Board.h, Board.cpp, Tile.h, Tile.cpp
*  Creating a minesweeper game
*/

#include "Board.h"
#include "Tile.h"
#include <iostream>
#include <string>

int main() {
    int height {};
    int width {};
    int mine_count {};

    std::cout << "Enter Rows, Cols, and Mines: ";     // Prompt user for input 
    std::cin >> height >> width >> mine_count;

    // Creates board object with height and width and mine count
    Board board(height, width, mine_count);
    // Places mines
    board.place_mines();
    board.update_counts();
    int x, y;
    while (board.check_game_status()) {
        std::cout << std::endl;
        board.revealed_board();
        std::cout << "  Enter a row and column to dig: ";
        std::cin >> x >> y;
        while (x > (height - 1) || x < 0 || y > (width - 1) || y < 0) {     // Error checking to prevent player from accessing outside of the bounds of the memory
            std::cout << "  Please enter a valid row and column: ";
            std::cin >> x >> y;
        }
        board.play_board(x, y);
    }
    //Prints the final board
    std::cout << kResetColor << std::endl;
    if (board.check_win()) {
        std::cout << "YOU'VE WON!!!\n";
    } else {
        std::cout << "YOU'VE LOST!!!\n";
    }
    std::cout << "Final Board: \n";
    board.revealed_board();

    return 0;
}