#include "DistrictSelectScene.h"

bool DistrictSelectScene::init()
{
	bool bRet = false;
	do 
	{

		this->addChild(DistrictSelectLayer::create());
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
