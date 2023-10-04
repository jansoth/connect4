#pragma once
#include <memory>

#include "Player.hpp"
#include "Grid.hpp"

class CLI_View;

class Game
{

    enum Neighbor
    {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
        TOP_LEFT,
        TOP_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_RIGHT
    };

    // Member-Variables
    Grid &grid;
    std::shared_ptr<CLI_View> view;                             // use Pointer to resolve conflict with circular dependencies... -could i use a reference instead??
    const int MAX_TURNS = grid.columnCount() * grid.rowCount(); // 7 col * 6 rows = 42
    int currentTurn = 1;
    Status currentPlayer = Status::COLOR_P1;
    Status winner = Status::EMPTY;
    Column slectedColumn_{-1};

    /// @brief returns if specified Neighbor to current Cell has the same Color
    ///
    /// @param grid Grid to check
    /// @param currentRow Rownumber of current Cell
    /// @param currentColumn Columnnumber of current Cell
    /// @param whichNeighbor Top, Bottom, Left,...
    /// @return if given Neighbor has same color
    bool NeighborHasSameColor(Row currentRow, Column currentColumn, Neighbor whichNeighbor);

    /// @brief get the topmost coin of a row
    /// @param column to check
    /// @return row of top coin. returns -1 if column is empty!
    Row getTopCoinOfColumn(Column column);

public:
    /// @brief Standard-Constructor.
    ///
    Game(std::shared_ptr<CLI_View> cliView, Grid &grid);

    /// @brief checks if there is a Winner after the last Move
    ///
    /// @param lastTurn column where the last coin was placed
    /// @return true: game is over (there is a winner or draw)
    bool isGameOver();

    Status getWinner();

    /// @brief change Player so next Player can drop coin
    void changePlayer();

    /// @brief
    /// @param selectedColumn where Coin should be dropped
    void dropCoin(Column selectedColumn);

    /// @brief checks if selected Column is full
    /// @param Column Column to Check
    /// @return true if column is already full
    bool columnIsFull(Column selectedColumn);

    /// @brief starts the Game
    void start();
};
