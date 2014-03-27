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
	this->addChild(GameLayer::create());

	INIT_TRUE
	INIT_END
}