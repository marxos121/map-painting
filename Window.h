#pragma once

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>

struct Shared;

class GameWindow : public sf::RenderWindow
{
public:
	GameWindow(sf::VideoMode  	mode,
		const sf::String& title,
		sf::Uint32  	style = sf::Style::Default);

	~GameWindow() = default;

	void toggleFullscreen();
	void updateWindowedSize();

	bool isFullscreen() const;
	sf::Vector2u getWindowedSize() const;
	sf::Vector2f getScale() const;

private:
	bool m_bIsFullscreen;
	sf::Vector2u m_windowedSize;
};

