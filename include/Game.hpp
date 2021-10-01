#ifndef GAME_HPP
#define GAME_HPP

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Game
{
public:
    Game(sf::Vector2u l_winSize, const std::string &l_title);

    void ProcessInput();
    void Update();
    void Draw();
    void RestartClock();

    bool IsDone();

private:
    sf::Vector2u m_winSize;
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    float m_deltaTime;

    bool m_done;

    void Setup(const std::string &l_title);
};

#endif