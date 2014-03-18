#include "LevelSelectScene.h"


bool LevelSelectScene::init(const char* districtTypeID)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCScene::init());

		this->addChild(LevelSelectLayer::create(districtTypeID));
		bRet = true;
	} while(0);

	return bRet;
}

LevelSelectScene::LevelSelectScene(void)
{
}


LevelSelectScene::~LevelSelectScene(void)
{
}

	bool LevelSelectScene::loadResources(void)
	{
		this->m_progress->setMaxValue(1);
		this->m_progress->setCurrentValue(1);
		LoadingScene::sharedInstance()->setProgress(this->m_progress);
		return true;
	}
	bool LevelSelectScene::drawContents(void)
	{
		//this->addChild(LevelSelectLayer::create());
		return true;
	}