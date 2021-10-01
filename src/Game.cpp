#include "Game.hpp"

Game::Game(sf::Vector2u l_winSize, const std::string &l_title)
    : m_done(false), m_winSize(l_winSize)
{
    Setup(l_title);
}

void Game::Setup(const std::string &l_title)
{
    m_window.create({m_winSize.x, m_winSize.y}, l_title);
}

void Game::ProcessInput()
{
    sf::Event ev;
    while (m_window.pollEvent(ev))
    {
        // Process Input
    }
}

void Game::Update()
{
    // Update
}

void Game::Draw()
{
    m_window.clear(sf::Color::Black);

    m_window.display();
}

void Game::RestartClock()
{
    m_deltaTime = m_clock.restart().asSeconds();
}

bool Game::IsDone() { return m_done; }