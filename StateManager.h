#pragma once
#include "BaseState.h"
#include "StatePlay.h"
#include "StatePause.h"
#include "GameFinished.h"
#include "StateMainMenu.h"
#include "StateDesign.h"

#include <unordered_set>
#include <vector>

class StateManager
{
	friend void GameFinished::update();
public:
	StateManager(Shared* shared) : m_shared(shared) { }
	~StateManager();

	template <typename T> void addState()
	{
		m_states.emplace_back(new T(m_shared));
	}

	void swapState(StateType newState);

	void handleInput();
	void update();
	void render();

	StateType getCurrentState() const;
	void togglePause();
private:
	std::vector<BaseState*> m_states;
	Shared* m_shared;
};

