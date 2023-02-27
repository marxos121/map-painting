#pragma once

#include "BaseState.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class StatePause : public BaseState
{
public:
	StatePause(Shared* shared);
	~StatePause() = default;

	void handleInput() override;
	void update() override;
	void render() override;

private:
	sf::RectangleShape m_fill;
	sf::Font font;
	sf::Text text;
};