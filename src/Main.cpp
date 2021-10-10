#include "Constants.hpp"
#include "Game.hpp"

int main()
{
    using namespace constants;
    Game game({k_numTiles.x * k_tileSize, (k_numTiles.y * k_tileSize) + k_panelHeight}, "Minesweeper");
    while (!game.IsDone())
    {
        game.ProcessInput();
        game.Draw();
    }
    return 0;
}