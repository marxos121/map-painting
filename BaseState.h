#pragma once
#include "Shared.h"

class GameWindow;

enum class StateType
{
	Intro, MainMenu, Play, Pause, GameOver, GameComplete, Design
};

class BaseState
{
public:
	BaseState(StateType type, Shared* shared = nullptr, bool transcendent = false, bool transparent = false) 
		: m_type(type), m_shared(shared), m_bIsTranscendent(transcendent), m_bIsTransparent(transparent), m_isActive(false) { }
	virtual ~BaseState() = default;

	virtual void handleInput() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void activate() { m_isActive = true; }
	virtual void deactivate() { m_isActive = false; }
	virtual void onResize() {}

	StateType getType() const { return m_type; }
	bool getTranscendent() const { return m_bIsTranscendent; }
	bool getTransparent() const { return m_bIsTransparent; }

	bool isActive() const { return m_isActive; }
private:
	StateType m_type;
	bool m_bIsTranscendent;
	bool m_bIsTransparent;

protected:
	Shared* m_shared;
	bool m_isActive;
};