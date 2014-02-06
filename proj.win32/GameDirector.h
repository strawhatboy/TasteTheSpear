#pragma once
#include "myLib.h"
#include "cocos2d.h"

enum GameState
{
	MAIN_MENU = 1,
	PRE_GAME = 2,
	GAMING = 4,
	GAME_PAUSED = 8,
	GAME_OVER = 16
};

class GameDirector
{
	CC_SYNTHESIZE(int, m_GameState, GameState);

public:
	~GameDirector(void);

	CC_SHARED_CREATE_FUNC(GameDirector);
};

