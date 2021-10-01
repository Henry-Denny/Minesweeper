#include "Game.hpp"

int main()
{
    Game game({1920, 1080}, "Minesweeper");
    while (!game.IsDone())
    {
        game.ProcessInput();
        game.Update();
        game.Draw();
        game.RestartClock();
    }
    return 0;
}