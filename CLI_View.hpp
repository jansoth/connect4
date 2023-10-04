#pragma once
#include "ViewInterface.hpp"
#include "ObserverInterface.hpp"
#include "Grid.hpp"
#include "Game.hpp"

class CLI_View : public ViewInterface, public ObserverInterface
{
    Grid &gridModel_;
    std::shared_ptr<Game> gameController_;

    /// @brief get User Input (where to Drop coin)
    void processUserInput();

    void drawRow(Row row);

public:
    // Constructor
    CLI_View(Grid &gridModel, std::shared_ptr<Game> controller) : gridModel_{gridModel}, gameController_{controller} {}

    void setController(std::shared_ptr<Game> controller);

    void initialize() override;
    void drawGrid() override;
};