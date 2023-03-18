#pragma once

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>

struct Shared;

class GameWindow
{
public:
	GameWindow(const std::string& l_name, unsigned int l_x, unsigned int l_y, bool l_fullscreen = false);
	~GameWindow();
	void initShared(Shared* shr);
	void create();
	void destroy();

	sf::RenderWindow* getRenderWindow();

	void toggleFullscreen();
	bool isOpen() const;
	sf::Vector2f getScale() const;


private:
	Shared* m_shared;
	sf::RenderWindow m_window;

	std::string m_name;
	unsigned int m_x;
	unsigned int m_y;
	bool m_fullscreen;
};

