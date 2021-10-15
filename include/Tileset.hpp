#ifndef TILESET_HPP
#define TILESET_HPP

#include <string>
#include <vector>

#include <SFML/System/Vector2.hpp>

#include "Tile.hpp"
#include "Constants.hpp"
#include "Textures.hpp"

class Tileset
{
public:
    Tileset(const std::string &l_texturesPathname);
    ~Tileset();

    bool IsMine(sf::Vector2u l_gridCoords);
    void ExploreTile(sf::Vector2u l_gridCoords);
    void DrawTiles(sf::RenderWindow *l_wind);
    void ShowAllMines();
    void ResetMinefield(int l_numMines);

private:
    int GetNumNearbyMines(sf::Vector2u l_gridCoords);
    void DeleteTiles();
    void CreateTiles();
    void PlantMines(int l_numMines);
    
    std::vector<std::vector<Tile*>> m_tileset;
    Textures m_textures;
};

#endif