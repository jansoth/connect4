#pragma once

#include <array>
#include "Status.hpp"
#include "Column.hpp"
#include "Row.hpp"

class Grid
{

    // Member-Variables
    static const int COLUMN_COUNT_ = 7;
    static const int ROW_COUNT_ = 6;

    // grid as 2D Array: äußeres: row, inneres Col.
    std::array<std::array<Status, COLUMN_COUNT_>, ROW_COUNT_> array2D;

public:
    // Konstruktor
    /// @brief setz alle Elemente des Grids auf Empty
    Grid();

    Status getCellStatus(Column col, Row row) const;

    void setCellStatus(Column col, Row row, Status status);

    int columnCount() const { return COLUMN_COUNT_; }
    int rowCount() const { return ROW_COUNT_; }
};