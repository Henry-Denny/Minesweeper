#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/System/Vector2.hpp>

namespace constants
{
    const sf::Vector2u k_numTiles { 30, 15 };
    constexpr int k_tileSize { 80 };
    constexpr int k_tilePadding { 0 };
    constexpr int k_panelHeight { 400 };
    constexpr int k_numMines { 40 };
}

#endif