#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>

class Tile
{
public:
    Tile(sf::Texture *l_defaultTexture, bool l_isMine = false, bool l_isHidden = true, bool l_flagged = false) : m_texture { l_defaultTexture }, m_isMine { l_isMine }, m_hidden { l_isHidden }, m_flagged { l_flagged } {}

    bool IsMine() { return m_isMine; }
    bool IsHidden() { return m_hidden; }
    bool IsFlagged() { return m_flagged; }

    void Reveal() { m_hidden = false; }
    void Arm() { m_isMine = true; }
    void ToggleFlag() { m_flagged = !m_flagged; }
    void SetTexture(sf::Texture *l_newTexture) { m_texture = l_newTexture; }
    sf::Texture* GetTexture() { return m_texture; }
    
private:
    bool m_isMine;
    bool m_hidden;
    bool m_flagged;
    sf::Texture *m_texture;
};

#endif