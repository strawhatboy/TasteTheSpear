#include "GameHudLayer.h"


bool GameHudLayer::init()
{
	INIT_START

	CC_BREAK_IF(!CCLayer::init());
	initSpellHud();
	initHeroHud();
	initEnemyHud();
	initItemsSpellHud();
	initScoreHud();

	INIT_TRUE
	INIT_END
}

GameHudLayer::GameHudLayer(void)
{
	INIT_POINTER(m_HeroHud);
	INIT_POINTER(m_EnemyHud);
	INIT_POINTER(m_SpellsHud);
	INIT_POINTER(m_ItemsSpellsHud);
}


GameHudLayer::~GameHudLayer(void)
{
}

void GameHudLayer::initSpellHud()
{
	//// for testing
	//MyListView* view = MyListView::create();
	//view->setContentSize(CCVisibleSize);
	//view->setAlignment(MyAlignmentLeftCenter);
	//view->setOrientation(MyOrientationTopToBottom);
	//view->setPadding(5.f);
	//this->addChild(view);
	//for (int i = 0; i < 5; i++)
	//{
	//	CCSprite* sprite = CCSprite::create("logo.png");
	//	view->addChild(sprite);
	//}


}

void GameHudLayer::initHeroHud()
{
	// protrait/avatar
	auto heroHud = CCSprite::createWithSpriteFrameName("HeroHud.png");
	heroHud->setPosition(ccpMult(heroHud->getContentSize(), .5f));
	this->addChild(heroHud, 0, TAG_HERO_HUD);

	auto heroID = GameDirector::sharedInstance()->getCurrentHero();

	// 60 * 60
	auto armature = GameObjectTypesLoader::sharedInstance()->createArmatureByID(heroID.c_str());
	armature->setScaleX(60.f / armature->getContentSize().width);
	armature->setScaleY(60.f / armature->getContentSize().height);
	
	armature->setPosition(44.f, 44.f);
	this->addChild(armature);
}

void GameHudLayer::initEnemyHud()
{
	// protrait/avatar
	auto enemyHud = CCSprite::createWithSpriteFrameName("EnemyHud.png");
	auto texture = enemyHud->getTexture();
	
	auto halfHudSize = ccpMult(enemyHud->getContentSize(), .5f);
	auto visibleSize = CCVisibleSize;
	enemyHud->setPosition(ccp(halfHudSize.x, visibleSize.height - halfHudSize.y));
	this->addChild(enemyHud, 0, TAG_ENEMY_HUD);
}

void GameHudLayer::initItemsSpellHud()
{
}

void GameHudLayer::initScoreHud()
{
}

void GameHudLayer::setLifePercentage(float fPercentage)
{
}