#include "Textures.hpp"

Textures::Textures(const std::string &l_pathname)
{
    LoadFromFile(l_pathname);
}

Textures::~Textures()
{
    DestroyTextures();
}

void Textures::DestroyTextures()
{
    for (auto &texture : m_textures)
    {
        if (texture.second)
        {
            delete texture.second;
            texture.second = nullptr;
        }
    }
}

sf::Texture* Textures::GetTexture(const std::string &l_textName)
{
    sf::Texture *texture = m_textures.at(l_textName);
    return texture;
}

bool Textures::LoadFromFile(const std::string &l_pathname)
{
    std::ifstream textures;
    textures.open(l_pathname);
    if (!textures.is_open())
    {
        std::cout << "Failed to load file: " << l_pathname << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(textures, line))
    {
        std::stringstream keystream(line);
        std::string stringID, fileName;
        keystream >> stringID;
        keystream >> fileName;

        sf::Texture *texture = new sf::Texture();
        if(!texture->loadFromFile(fileName))
        {
            delete texture;
            return false;
        }

        m_textures.emplace(stringID, texture);
    }

    textures.close();
}