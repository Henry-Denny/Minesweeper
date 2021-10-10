#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <unordered_map>
#include <string>

#include <SFML/Graphics.hpp>

class Textures
{
public:
    Textures(const std::string &l_pathname);
    ~Textures();

    sf::Texture* GetTexture(const std::string &l_textName);
    bool LoadFromFile(const std::string &l_pathname);

private:
    std::unordered_map<std::string, sf::Texture> m_textures;
};

#endif