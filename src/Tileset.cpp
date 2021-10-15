#include "Tileset.hpp"

Tileset::Tileset(const std::string &l_texturesPathname) :
    m_tileset { std::vector<std::vector<Tile*>>(constants::k_numTiles.x, std::vector<Tile*>(constants::k_numTiles.y, nullptr)) }, m_textures(l_texturesPathname)
{

}

Tileset::~Tileset()
{
    DeleteTiles();
}

void Tileset::ResetMinefield(int l_numMines)
{
    m_tilesRecovered = 0;
    DeleteTiles();
    CreateTiles();
    PlantMines(l_numMines);
}

void Tileset::PlantMines(int l_numMines)
{
    std::vector<Tile*> availableTiles(constants::k_numTiles.x * constants::k_numTiles.y);
    int index = 0;
    for (const auto &l_column : m_tileset)
    {
        for (const auto &l_tile : l_column)
        {
            availableTiles[index] = l_tile;
            ++index;
        }
    }
    for (int i = 0; i < l_numMines; ++i)
    {
        int index = rand() % availableTiles.size();
        availableTiles[index]->Arm();
        availableTiles.erase(availableTiles.begin() + (index));
    }
}

void Tileset::CreateTiles()
{
    for (int x = 0; x < constants::k_numTiles.x; ++x)
    {
        for (int y = 0; y < constants::k_numTiles.y; ++y)
        {
            m_tileset[x][y] = new Tile(m_textures.GetTexture("Default"));
        }
    }
}

void Tileset::DeleteTiles()
{
    for (int x = 0; x < constants::k_numTiles.x; ++x)
    {
        for (int y = 0; y < constants::k_numTiles.y; ++y)
        {
            if (!m_tileset[x][y]) { continue; }
            delete m_tileset[x][y];
            m_tileset[x][y] = nullptr;
        }
    }
}

bool Tileset::IsMine(sf::Vector2u l_gridCoords)
{
    Tile *tile = m_tileset[l_gridCoords.x][l_gridCoords.y];
    if (!tile->IsMine()) { return false; }

    tile->SetTexture(m_textures.GetTexture("Mine"));
    tile->Reveal();
    return true;
}

int Tileset::GetNumNearbyMines(sf::Vector2u l_gridCoords)
{
    int nearbyMines = 0;
    for (int yOff = -1; yOff <= 1; ++yOff)
    {
        for (int xOff = -1; xOff <= 1; ++xOff)
        {
            // Boundary checks
            if (
                (l_gridCoords.x + xOff) < 0 ||
                (l_gridCoords.x + xOff) >= constants::k_numTiles.x ||
                (l_gridCoords.y + yOff) < 0 ||
                (l_gridCoords.y + yOff) >= constants::k_numTiles.y ||
                (xOff == 0 && yOff == 0)
            ) { continue; }
            // Mine check
            if (m_tileset[l_gridCoords.x + xOff][l_gridCoords.y + yOff]->IsMine())
            {
                ++nearbyMines;
            }
        }
    }
    return nearbyMines;
}

void Tileset::ExploreTile(sf::Vector2u l_gridCoords)
{
    Tile *tile = m_tileset[l_gridCoords.x][l_gridCoords.y];
    if (!tile->IsHidden() || tile->IsFlagged()) { return; }

    tile->Reveal();
    ++m_tilesRecovered;
    int numNearbyMines = GetNumNearbyMines(l_gridCoords);
    if (numNearbyMines != 0)
    {
        switch (numNearbyMines)
        {
            case 1:
                tile->SetTexture(m_textures.GetTexture("One"));
                break;
            case 2:
                tile->SetTexture(m_textures.GetTexture("Two"));
                break;
            case 3:
                tile->SetTexture(m_textures.GetTexture("Three"));
                break;
            case 4:
                tile->SetTexture(m_textures.GetTexture("Four"));
                break;
            case 5:
                tile->SetTexture(m_textures.GetTexture("Five"));
                break;
            case 6:
                tile->SetTexture(m_textures.GetTexture("Six"));
                break;
            case 7:
                tile->SetTexture(m_textures.GetTexture("Seven"));
                break;
            case 8:
                tile->SetTexture(m_textures.GetTexture("Eight"));
                break;
            default:
                break;
        }
    }
    else
    {
        tile->SetTexture(m_textures.GetTexture("Empty"));
        for (int yOff = -1; yOff <= 1; ++yOff)
        {
            for (int xOff = -1; xOff <= 1; ++xOff)
            {
                // Boundary checks
                if (
                    (l_gridCoords.x + xOff) < 0 ||
                    (l_gridCoords.x + xOff) >= constants::k_numTiles.x ||
                    (l_gridCoords.y + yOff) < 0 ||
                    (l_gridCoords.y + yOff) >= constants::k_numTiles.y ||
                    (xOff == 0 && yOff == 0)
                ) { continue; }
                if (m_tileset[l_gridCoords.x + xOff][l_gridCoords.y + yOff]->IsHidden())
                {
                    ExploreTile(sf::Vector2u(l_gridCoords.x + xOff, l_gridCoords.y + yOff));
                }
            }
        }
    }
}

void Tileset::FlagTile(sf::Vector2u l_gridCoords)
{
    Tile *tile = m_tileset[l_gridCoords.x][l_gridCoords.y];
    if (tile->IsHidden())
    {
        tile->ToggleFlag();
        tile->SetTexture(tile->IsFlagged() ? m_textures.GetTexture("Flag") : m_textures.GetTexture("Default"));
    }
}

void Tileset::DrawTiles(sf::RenderWindow *l_wind)
{
    using namespace constants;
    sf::RectangleShape rect(sf::Vector2f(k_tileSize - k_tilePadding, k_tileSize - k_tilePadding));
    for (int x = 0; x < k_numTiles.x; ++x)
    {
        for (int y = 0; y < k_numTiles.y; ++y)
        {
            rect.setPosition(x * k_tileSize, k_panelHeight + (y * k_tileSize));
            rect.setTexture(m_tileset[x][y]->GetTexture());

            l_wind->draw(rect);
        } 
    }
}

void Tileset::ShowAllMines()
{
    for (auto &l_column : m_tileset)
    {
        for (auto &l_tile : l_column)
        {
            if (l_tile->IsMine())
            {
                l_tile->SetTexture(m_textures.GetTexture("Mine"));
                l_tile->Reveal();
            }
        }
    }
}

bool Tileset::MinefieldCleared()
{
    return m_tilesRecovered >= ((constants::k_numTiles.x * constants::k_numTiles.y) - constants::k_numMines);
}