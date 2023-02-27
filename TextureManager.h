#pragma once
#include <unordered_map>
#include <string>

#include <SFML/Graphics/Texture.hpp>


class TextureManager
{
public:
	sf::Texture* getTexture(const std::string& filename)
	{
		if (m_textures.find(filename) != m_textures.end())
		{
			return &m_textures[filename];
		}
		m_textures.emplace(filename, sf::Texture());
		std::string name = "./Graphics/Textures/" + filename + ".png";
		int a = 10;
		m_textures[filename].loadFromFile("./Graphics/Textures/" + filename + ".png");

		return &m_textures[filename];
	}


private:
	std::unordered_map<std::string, sf::Texture> m_textures;
};