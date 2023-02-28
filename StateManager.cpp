#include "StateManager.h"

StateManager::~StateManager()
{
	for (auto state : m_states)
	{
		delete state;
	}
}

void StateManager::swapState(StateType newState)
{
	auto it = std::find_if(m_states.begin(), m_states.end(),
		[newState](BaseState* st) { return st->getType() == newState; });

	if (!m_states.empty()) {
		m_states.back()->deactivate();
	}

	BaseState* temp = nullptr;
	if (it == m_states.end())
	{
		switch (newState)
		{
		case StateType::Play: addState<StatePlay>(); break;
		case StateType::Pause: addState<StatePause>(); break;
		case StateType::GameComplete: addState<GameFinished>(); break;
		//case StateType::Intro: addState<StateIntro>(); break;
		case StateType::MainMenu: addState<StateMainMenu>(); break;
		}
	}
	else
	{
		temp = *it;
		m_states.erase(it);
		m_states.emplace_back(temp);
	}
	m_states.back()->activate();
}

void StateManager::handleInput()
{
	if(!m_states.empty())
		m_states.back()->handleInput();
}

void StateManager::update()
{
	if (!m_states.empty() && m_states.back()->isActive())
		m_states.back()->update();
}

void StateManager::render()
{
	if (m_states.empty())
	{
		return;
	}

	auto it = m_states.end() - 1;
	
	while (it != m_states.begin())
	{
		if ((*it)->getTransparent())
		{
			--it;
		}
		else
		{
			break;
		}
	}

	while (it != m_states.end())
	{
		(*it)->render();
		++it;
	}
}

void StateManager::togglePause()
{
	if (m_states.back()->getType() == StateType::Pause)
	{
		swapState(StateType::Play);
	}
	else if (m_states.back()->getType() == StateType::Play)
	{
		swapState(StateType::Pause);
	}
}

StateType StateManager::getCurrentState() const
{ 
	return m_states.empty() ? StateType(-1) : m_states.back()->getType(); 
}
