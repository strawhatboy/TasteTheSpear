// we will put game hud in this layer, such as HP/MP bars, ability/buff icons and scores.
#pragma once
#include "cocos2d.h"
#include "myLib.h"
#include "MyListView.h"
#include "GameDirector.h"

USING_NS_CC;


class GameHudLayer :
	public CCLayer
{
private:

	// hero hud includes HP/MP bars, avatar and buffs.
	CCLayer* m_HeroHud;

	// same with hero hud, but position on screen.
	CCLayer* m_EnemyHud;

	// Abilities' hud. left of the screen.
	CCLayer* m_SpellsHud;

	// Item abilities' hud. right of the screen.
	CCLayer* m_ItemsSpellsHud;

	// label for score.
	CCLayer* m_ScoreHud;

	void initHeroHud();
	void initEnemyHud();
	void initSpellHud();
	void initItemsSpellHud();
	void initScoreHud();

public:
	virtual bool init();
	GameHudLayer(void);
	~GameHudLayer(void);
	
	void setLifePercentage(float fPercentage);

	CREATE_FUNC(GameHudLayer);
};

