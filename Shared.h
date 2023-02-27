#pragma once

class GameWindow; class TextureManager; class StateManager; class Map;

struct Shared
{
	GameWindow* m_window;
	TextureManager* m_texMgr;
	StateManager* m_stateMgr;
	Map* m_gameMap;
};