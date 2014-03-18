#include "HeroSelectScene.h"


HeroSelectScene::HeroSelectScene(void)
{
}


HeroSelectScene::~HeroSelectScene(void)
{
}

bool HeroSelectScene::init()
{
	this->addChild(HeroSelectLayer::create());
	return true;
}

	bool HeroSelectScene::loadResources(void)
	{
		this->m_progress->setMaxValue(1);
		this->m_progress->setCurrentValue(1);
		LoadingScene::sharedInstance()->setProgress(this->m_progress);
		return true;
	}
	bool HeroSelectScene::drawContents(void)
	{
		//this->addChild(LevelSelectLayer::create());
		return true;
	}