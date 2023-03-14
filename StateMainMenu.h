#pragma once

#include "BaseState.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class StateMainMenu : public BaseState
{
public:
	StateMainMenu(Shared* shared);

	void handleInput() override;
	void update() override { };
	void render() override;
	void activate() override;

private:
	sf::Font m_font;
	sf::Text m_startGameText;
	sf::Text m_designText;
	sf::Text m_exitText;
	sf::RectangleShape m_rectangles[3];
};