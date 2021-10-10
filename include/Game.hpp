#ifndef GAME_HPP
#define GAME_HPP

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Constants.hpp"
#include "Tileset.hpp"

class Game
{
public:
    Game(sf::Vector2u l_winSize, const std::string &l_title);

    void ProcessInput();
    void Draw();

    bool IsDone();

private:
    sf::Vector2u m_winSize;
    sf::RenderWindow m_window;
    Tileset m_tileset;

    bool m_done;

    void Setup(const std::string &l_title);
    void Reset();
    sf::Vector2u GetGridCoord(sf::Vector2i l_worldPos);
};

#endif