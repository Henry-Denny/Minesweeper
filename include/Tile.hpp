#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>

class Tile
{
public:
    Tile(sf::Texture *l_defaultTexture, bool l_isMine = false, bool l_isHidden = false) : m_texture { l_defaultTexture }, m_isMine { l_isMine }, m_hidden { l_isHidden } {}

    bool IsMine() { return m_isMine; }
    bool IsHidden() { return m_hidden; }

    void Reveal() { m_hidden = true; }
    void Arm() { m_isMine = true; }
    void SetTexture(sf::Texture *l_newTexture) { m_texture = l_newTexture; }
    sf::Texture* GetTexture() { return m_texture; }
    
private:
    bool m_isMine;
    bool m_hidden;
    sf::Texture *m_texture;
};

#endif