#include "Game.hpp"

Game::Game(sf::Vector2u l_winSize, const std::string &l_title)
    : m_done(false), m_winSize(l_winSize), m_tileset("./res/textures.cfg"), m_title("Minesweeper", m_font)
{
    m_font.loadFromFile("./res/otomanopee.ttf");
    m_title.setCharacterSize(150);

    sf::FloatRect boundingBox = m_title.getLocalBounds();
    m_title.setOrigin(sf::Vector2f(boundingBox.left + (boundingBox.width / 2.0f), boundingBox.top + (boundingBox.height / 2.0f)));

    m_title.setPosition({(l_winSize.x / 2.0f), (constants::k_panelHeight / 2.0f)});
    m_title.setFillColor(sf::Color::Red);
    
    Setup(l_title);
    Reset();
}

void Game::Setup(const std::string &l_title)
{
    m_window.create({m_winSize.x, m_winSize.y}, l_title);
}

void Game::Reset()
{
    m_tileset.ResetMinefield(constants::k_numMines);
}

void Game::ProcessInput()
{
    sf::Event ev;
    while (m_window.pollEvent(ev))
    {
        switch(ev.type)
        {
            case (sf::Event::Closed):
                m_done = true;
                break;

            case (sf::Event::MouseButtonReleased):
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
                    if (mousePos.x < 0 || mousePos.x >= m_window.getSize().x || mousePos.y < constants::k_panelHeight || mousePos.y >= m_window.getSize().y) { continue; }
                    sf::Vector2u tilePos = GetGridCoord(mousePos);
                    
                    if (ev.mouseButton.button == sf::Mouse::Left)
                    {
                        if (!m_tileset.IsMine(tilePos))
                        {
                            m_tileset.ExploreTile(tilePos);
                            if (m_tileset.MinefieldCleared())
                            {
                                // Present win screen
                                m_done = true;
                            }
                        }
                        else
                        {
                            m_tileset.ShowAllMines();
                            // Present lose screen
                        }
                    }
                    else if (ev.mouseButton.button == sf::Mouse::Right)
                    {
                        m_tileset.FlagTile(tilePos);
                    }
                }
                break;
            
            case (sf::Event::KeyPressed):
                if (ev.key.code == sf::Keyboard::Space)
                {
                    m_tileset.ShowAllMines();
                }

            default:
                break;
        }
    }
}

void Game::Draw()
{
    m_window.clear(sf::Color::Black);

    m_tileset.DrawTiles(&m_window);
    DrawUI();

    m_window.display();
}

void Game::DrawUI()
{
    m_window.draw(m_title);
}

sf::Vector2u Game::GetGridCoord(sf::Vector2i l_worldPos)
{
    return sf::Vector2u(l_worldPos.x / constants::k_tileSize, (l_worldPos.y - constants::k_panelHeight) / constants::k_tileSize);
}

bool Game::IsDone() { return m_done; }