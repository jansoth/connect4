#include "CLI_View.hpp"
#include "Column.hpp"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void CLI_View::setController(std::shared_ptr<Game> controller)
{
    gameController_ = controller;
}

// view muss keine methode choose column vom interface haven. view regelt selber ein- und ausgabe. bei eingabe spricht es direkt controller an
// https://developer.mozilla.org/en-US/docs/Glossary/MVC
void CLI_View::initialize()
{
    drawGrid();
    Column lastTurn{0};
    do
    {
        processUserInput();
    } while (!gameController_->isGameOver());

    switch (gameController_->getWinner())
    {
    case Status::COLOR_P1:
        cout << "Player 1 (x) wins!" << endl;
        break;
    case Status::COLOR_P2:
        cout << "Player 2 (o) wins!" << endl;
        break;
    default:
        cout << "Game over - There is no Winner...";
        break;
    }
}

void CLI_View::drawGrid()
{
    for (Row row{gridModel_.rowCount() - 1}; row.value_ >= 0; row.value_--)
    {
        drawRow(row);
        cout << "\n";
    }
    cout << "---------------"
         << "\n";
    cout << " 0 1 2 3 4 5 6 "
         << "\n";
    cout << std::endl;
}

void CLI_View::drawRow(Row row)
{
    cout << "|";
    for (Column column{0}; column.value_ < gridModel_.columnCount(); column.value_++)
    {
        if (gridModel_.getCellStatus(column, row) == Status::COLOR_P1)
        {
            cout << "x|";
        }
        else if (gridModel_.getCellStatus(column, row) == Status::COLOR_P2)
        {
            cout << "o|";
        }
        else
        {
            cout << " |";
        }
    }
}

void CLI_View::processUserInput()
{
    Column selectedColumn{-1};
    bool invalidInput = true;
    do
    {

        cout << "Please enter a Column between 0 and 6" << std::endl;
        cin >> selectedColumn.value_;
        if (cin.fail()) // input not an integer
        {
            invalidInput = true;
        }
        else if (selectedColumn.value_ < 0 || selectedColumn.value_ > 6) // out of range
        {
            invalidInput = true;
        }
        else if (gameController_->columnIsFull(selectedColumn))
        {
            invalidInput = true;
        }
        else
        {
            invalidInput = false; // valid input
        }

        if (invalidInput)
        {
            cout << "Invalid Input!" << std::endl;
        }
        // notwendig weil cin nur bis zum nächsten leerzeichen auswertet. Weil danach noch "Enter" gedrückt wird gibts probleme
        // siehe auch https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
        // alternativ getline() verwenden
        std::cin.clear();
        std::cin.ignore(256, '\n');

    } while (invalidInput);

    gameController_->dropCoin(selectedColumn);
}