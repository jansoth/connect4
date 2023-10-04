#include "Game.hpp"
#include "CLI_View.hpp"
#include "Status.hpp"
#include "Grid.hpp"
#include "Player.hpp"

#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>

// Constructor
Game::Game(std::shared_ptr<CLI_View> cliView, Grid &gr) : view(cliView), grid(gr) {}

bool Game::isGameOver()
{
    // reached max turns?
    if (currentTurn >= MAX_TURNS)
    {
        return true;
    }

    Column column = slectedColumn_;
    // row checken anhand column
    Row row = getTopCoinOfColumn(column);

    // vwenn spalte noch leer
    if (row.value_ == -1)
    {
        return false;
    }

    // set starting values for iterators
    Column columnIterator{column.value_};
    Row rowIterator{row.value_};

    // lambda for resetting iterator values to start
    auto resetIterators = [&rowIterator, &columnIterator, row, column]()
    {
        rowIterator.value_ = row.value_;
        columnIterator.value_ = column.value_;
    };

    int countSameColor = 1;

    // check 4 in a row
    // count how many same colors to the right
    while (NeighborHasSameColor(row, columnIterator, Neighbor::RIGHT))
    {
        // NeighborHasSameColor muss out of bounds checken
        columnIterator.value_++;
        countSameColor++;
    }

    // count how many same colors to the left
    resetIterators();
    while (NeighborHasSameColor(row, columnIterator, Neighbor::LEFT))
    {
        columnIterator.value_--;
        countSameColor++;
    }
    if (4 == countSameColor)
    {
        // change curren Player because Player already changed after drop coin -> winner would return wrong value
        changePlayer();
        winner = currentPlayer;
        return true;
    }

    // ---------------------------------------------
    // check 4 in a column
    countSameColor = 1;
    resetIterators();

    // count how many same colors above
    while (NeighborHasSameColor(rowIterator, column, Neighbor::TOP))
    {
        rowIterator.value_++;
        countSameColor++;
    }

    // count how many same colors below
    resetIterators();
    while (NeighborHasSameColor(rowIterator, column, Neighbor::BOTTOM))
    {
        rowIterator.value_--;
        countSameColor++;
    }
    if (4 == countSameColor)
    {
        // change curren Player because Player already changed after drop coin -> winner would return wrong value
        changePlayer();
        winner = currentPlayer;
        return true;
    }

    // ---------------------------------------------
    // check 4 in Diagonal ascending left to right
    countSameColor = 1;
    resetIterators();

    // check up & right
    while (NeighborHasSameColor(rowIterator, columnIterator, Neighbor::TOP_RIGHT))
    {
        rowIterator.value_++;
        columnIterator.value_++;
        countSameColor++;
    }

    resetIterators();

    // check down & left
    while (NeighborHasSameColor(rowIterator, columnIterator, Neighbor::BOTTOM_LEFT))
    {
        rowIterator.value_--;
        columnIterator.value_--;
        countSameColor++;
    }

    if (4 == countSameColor)
    {
        // change curren Player because Player already changed after drop coin -> winner would return wrong value
        changePlayer();
        winner = currentPlayer;
        return true;
    }

    // ---------------------------------------------
    // check 4 in Diagonal descending left to right
    countSameColor = 1;
    resetIterators();

    // check down & right
    while (NeighborHasSameColor(rowIterator, columnIterator, Neighbor::BOTTOM_RIGHT))
    {
        rowIterator.value_--;
        columnIterator.value_++;
        countSameColor++;
    }

    resetIterators();
    // check up & left
    while (NeighborHasSameColor(rowIterator, columnIterator, Neighbor::TOP_LEFT))
    {
        rowIterator.value_++;
        columnIterator.value_--;
        countSameColor++;
    }

    if (4 == countSameColor)
    {
        // change curren Player because Player already changed after drop coin -> winner would return wrong value
        changePlayer();
        winner = currentPlayer;
        return true;
    }
    return false;
}

bool Game::NeighborHasSameColor(Row currentRow, Column currentColumn, Neighbor whichNeighbor)
{

    Status thisCellStatus = grid.getCellStatus(currentColumn, currentRow);

    // getCellStatus needs Row/Column Objects
    Row rowOnTop{currentRow.value_ + 1};
    Row rowUnderneath{currentRow.value_ - 1};
    Column columnToTheLeft{currentColumn.value_ - 1};
    Column columnToTheRight{currentColumn.value_ + 1};

    switch (whichNeighbor)
    {
    case Neighbor::TOP:
        // grenzen prüfen
        if (currentRow.value_ == grid.rowCount() - 1)
        {
            return false;
        }
        if (thisCellStatus == grid.getCellStatus(currentColumn, rowOnTop))
        {
            return true;
        }
        break;

    case Neighbor::BOTTOM:
        // grenzen prüfen
        if (0 == currentRow.value_)
        {
            return false;
        }
        if (thisCellStatus == grid.getCellStatus(currentColumn, rowUnderneath))
        {
            return true;
        }
        break;

    case Neighbor::LEFT:
        // grenzen prüfen
        if (0 == currentColumn.value_)
        {
            return false;
        }
        if (thisCellStatus == grid.getCellStatus(columnToTheLeft, currentRow))
        {
            return true;
        }
        break;

    case Neighbor::RIGHT:
        if (currentColumn.value_ == grid.columnCount() - 1)
        {
            return false;
        }
        if (thisCellStatus == grid.getCellStatus(columnToTheRight, currentRow))
        {
            return true;
        }
        break;

    case Neighbor::TOP_LEFT:
        if (currentColumn.value_ == 0 || currentRow.value_ == grid.rowCount() - 1)
        {
            return false;
        }
        if (thisCellStatus == grid.getCellStatus(columnToTheLeft, rowOnTop))
        {
            return true;
        }
        break;

    case Neighbor::TOP_RIGHT:
        if (currentColumn.value_ == grid.columnCount() - 1 || currentRow.value_ == grid.rowCount() - 1)
        {
            return false;
        }
        if (thisCellStatus == grid.getCellStatus(columnToTheRight, rowOnTop))
        {
            return true;
        }
        break;

    case Neighbor::BOTTOM_LEFT:
        if (currentColumn.value_ == 0 || currentRow.value_ == 0)
        {
            return false;
        }
        if (thisCellStatus == grid.getCellStatus(columnToTheLeft, rowUnderneath))
        {
            return true;
        }
        break;

    case Neighbor::BOTTOM_RIGHT:
        if (currentColumn.value_ == grid.columnCount() - 1 || currentRow.value_ == 0)
        {
            return false;
        }
        if (thisCellStatus == grid.getCellStatus(columnToTheRight, rowUnderneath))
        {
            return true;
        }
        break;
    } // End of switch

    // falls nachbar nicht gleich -> false (statt in jedem Case)
    return false;
} // End of NeighborHasSameColor

Row Game::getTopCoinOfColumn(Column column)
{
    for (Row row{0}; row.value_ < grid.rowCount(); row.value_++)
    {
        if (grid.getCellStatus(column, row) == Status::EMPTY)
        {
            row.value_--;
            return row;
        }
        else if (row.value_ == grid.rowCount() - 1)
        {
            return row; // top is reached withoud finding empty cell
        }
    }
}

bool Game::columnIsFull(Column selectedColumn)
{
    if (getTopCoinOfColumn(selectedColumn).value_ >= grid.rowCount() - 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Game::dropCoin(Column selectedColumn)
{
    // ob voll ist wurde schon von view abgefragt
    Row row = getTopCoinOfColumn(selectedColumn);
    row.value_++;

    grid.setCellStatus(selectedColumn, row, currentPlayer);
    changePlayer();

    currentTurn++;
    view->drawGrid(); // sollte besser im Model passieren -> update Observer

    slectedColumn_ = selectedColumn;
}

Status Game::getWinner()
{
    return winner;
}

void Game::changePlayer()
{
    if (currentPlayer == Status::COLOR_P1)
    {
        currentPlayer = Status::COLOR_P2;
    }
    else
    {
        currentPlayer = Status::COLOR_P1;
    }
}

void Game::start()
{
    view->initialize();
}
