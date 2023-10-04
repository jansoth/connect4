#pragma once

/// @brief Hilfstyp um Row/Col nicht verwechseln zu können (Typsicherheit!!) 
struct Column{
    int value_;

    // Konstruktor implizit um Typumwandlung in int zu vermeiden
    explicit Column(int v) : value_{v} {}
};


/*    
besser alles ins Grid - macht mehr sinn. row/column nur kapselung von int um typsicherheit zu bekommen

    // brauch ich wirklich number? entspricht immer index im array... ich greif auch immer über index im array 
    const int NUMBER_;
    
    // ROW_COUNT_ besser in Grid festlegen und übergen:
    static const int ROW_COUNT_ = 6;

    std::array<Cell,ROW_COUNT_> cell{
        Cell(NUMBER_, 0), 
        Cell(NUMBER_, 1),
        Cell(NUMBER_, 2),
        Cell(NUMBER_, 3),
        Cell(NUMBER_, 4),
        Cell(NUMBER_, 5),
        };

public:
    // default constructor
    Column(int number) : NUMBER_{number} {};

    /// @brief add a Coin to the row
    ///
    /// Coin falls down as deep as it can
    /// @return Cell in which Coin was placed 
    Cell addCoin();

};

*/