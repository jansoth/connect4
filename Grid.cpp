#include "Grid.hpp"
#include "Status.hpp"

// Konstruktor
Grid::Grid()
{
    // alle Elemente des Arrays auf Empty setzen
    for (int i = 0; i < ROW_COUNT_; i++)
    {
        array2D.at(i).fill(Status::EMPTY);
    }
}

Status Grid::getCellStatus(Column col, Row row) const
{
    return array2D.at(row.value_).at(col.value_);
}

void Grid::setCellStatus(Column col, Row row, Status status)
{
    array2D.at(row.value_).at(col.value_) = status;
}
