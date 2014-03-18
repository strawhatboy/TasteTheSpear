#include "DistrictSelectScene.h"

bool DistrictSelectScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());

		bRet = true;
	} while (0);

	return bRet;
}


DistrictSelectScene::DistrictSelectScene(void)
{
	CCLog("DistrictSelectScene created?!");
}


DistrictSelectScene::~DistrictSelectScene(void)
{
	CCLog("DistrictSelectScene deleted?!!");
}

	bool DistrictSelectScene::loadResources(void)
	{
		this->m_progress->setMaxValue(1);
		this->m_progress->setCurrentValue(1);
		LoadingScene::sharedInstance()->setProgress(this->m_progress);
		return true;
	}
	bool DistrictSelectScene::drawContents(void)
	{
		this->addChild(DistrictSelectLayer::create());
		return true;
	}