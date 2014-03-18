#pragma once
#include "myLib.h"
#include "cocos2d.h"
#include "GameObjectTypesLoader.h"
#include "MenuScene.h"
#include "MyLoadingLayer.h"

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
	CC_SYNTHESIZE(uint, m_GameState, GameState);
	CC_SYNTHESIZE(uint, m_LastGameState, LastGameState);
	CC_SYNTHESIZE(string, m_CurrentDistrict, CurrentDistrict);
	CC_SYNTHESIZE(string, m_CurrentLevel, CurrentLevel);
	CC_SYNTHESIZE(uint, m_CurrentDifficulty, CurrentDifficulty);
	CC_SYNTHESIZE(string, m_CurrentHero, CurrentHero);

public:
	~GameDirector(void);

	string getUIStringByID(int nID);

	void changeState(uint gameState, CCDictionary* dictParams = NULL);


	CC_SHARED_CREATE_FUNC(GameDirector);

};

