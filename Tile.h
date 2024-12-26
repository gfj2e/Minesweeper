#ifndef TILE_H
#define TILE_H
/* Creates Tile class that will be contained within a board object
   Each tile will be it's own object that contains a value
*/
class Tile {
    private:
        int m_value;          // The value of the tile
        bool m_isRevealed;    // bool to check if the mine has been revealed
    public:
        Tile();
        void SetValue(int);                              // Setter
        void AddValue();                                // Another setter
        int GetValue() const;                           // Getter
        bool GetStatus() const { return m_isRevealed; } // Return status of the boolean m_isRevealed
        void SetStatusTrue();                           // function to reveal a tile, sets bool to true
};

#endif