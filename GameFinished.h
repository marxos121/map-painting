#pragma once

#include "BaseState.h"

#include <SFML/Graphics/Text.hpp>

class GameFinished : public BaseState
{
public:
	GameFinished(Shared*);

	void handleInput() override;
	void update() override;
	void render() override;
	void activate() override;

private:
	sf::Font m_font;
	sf::Text m_text;

	bool m_playAgain;
};