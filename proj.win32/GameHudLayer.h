// we will put game hud in this layer, such as HP/MP bars, ability/buff icons and scores.
#pragma once
#include "cocos2d.h"
#include "myLib.h"
#include "MyListView.h"
#include "GameDirector.h"

USING_NS_CC;

#define TAG_HERO_HUD		10000
#define TAG_ENEMY_HUD		10001
#define TAG_SPELLS_HUD		10002
#define TAG_ITEMS_HUD		10003
#define TAG_SCORE_HUD		10004
//#define TAG_HERO_HP_HUD		10005
//#define TAG_HERO_MP_HUD		10006
//#define TAG_ENEMY_HP_HUD	10007

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

