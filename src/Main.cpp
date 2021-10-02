#include "Game.hpp"

int main()
{
    Game game({800, 800}, "Minesweeper");
    while (!game.IsDone())
    {
        game.ProcessInput();
        game.Update();
        game.Draw();
        game.RestartClock();
    }
    return 0;
}