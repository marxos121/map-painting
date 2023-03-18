#pragma once

#include "BaseState.h"
#include "HUD.h"
#include "SheetAnimation.h"

#include <SFML/System/Clock.hpp>
#include <vector>

class Map;

enum class Step
{
	Up, Down, Left, Right
};

class StatePlay : public BaseState
{
public:

	StatePlay(Shared* shared);
	~StatePlay();

	void handleInput() override;
	void update() override;
	void render() override;
	void activate() override;
	void onResize() override;

	void resetPlayer();
	void updateTime();
	void restartClock();
	void resetTimer();

private:
	SheetAnimation m_playerSheet;
	std::vector<sf::Vector2i> m_player;	//.back() -> player's head
	Step m_nextStep;

	sf::Clock m_clock;
	sf::Time m_elapsed;
	sf::Time m_elapsedTotal;

	Map* m_gameMap;

	bool m_reset = false;

	HUD m_hud;
};