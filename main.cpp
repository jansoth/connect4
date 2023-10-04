#include "Game.hpp"
#include "CLI_View.hpp"
#include <memory>

int main()
{
    Grid grid{};
    std::shared_ptr<CLI_View> cliView = std::make_shared<CLI_View>(grid, nullptr); // hier wird eine Instanz von CLI_View erstellt, in einen std::shared_ptr verpackt und der Variable cliView zugewiesen
    std::shared_ptr<Game> gameController = std::make_shared<Game>(cliView, grid);
    cliView->setController(gameController);
    gameController->start();

    return 0;
}