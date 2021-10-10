#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/System/Vector2.hpp>

namespace constants
{
    const sf::Vector2u k_numTiles { 40, 20 };
    constexpr int k_tileSize { 40 };
    constexpr int k_tilePadding { 2 };
    constexpr int k_panelHeight { 400 };
    constexpr int k_numMines { 20 };
}

#endif