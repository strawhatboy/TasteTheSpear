#include "GameScene.h"


GameScene::GameScene(void)
{
}


GameScene::~GameScene(void)
{
}

bool GameScene::init()
{
	INIT_START

	CC_BREAK_IF(!CCScene::create());
	this->addChild(GameLayer::create(), 0, TAG_GAMELAYER);
	
	// add hero to the layer.
	//auto director = GameDirector::sharedInstance();
	//auto hero = director->createHero_Runtime(director->getCurrentHero().c_str());
	//hero->getTextureNode()->setPosition(400, 400);
	INIT_TRUE
	INIT_END
}