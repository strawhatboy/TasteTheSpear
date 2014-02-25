#include "MyLoadingLayer.h"

#define TAG_PROGRESSBAR 20

bool MyLoadingLayer::init()
{
	//CCLog("MyLoadingLayer initializing...");
	//CCLabelTTF* pLabel = CCLabelTTF::create("Loading...", "Arial", 100);
 //   
 //   CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
 //   CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
 //   // position the label on the center of the screen
 //   pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
 //                           origin.y + visibleSize.height - pLabel->getContentSize().height));

 //   // add the label as a child to this layer
 //   this->addChild(pLabel, 1);

	// loading progressbar
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	const char* loadingImageFile;
	if (this->m_bIsDefaultLoadingImage)
	{
		auto fileUtil = CCFileUtils::sharedFileUtils();
		auto plistDic = CCDictionary::createWithContentsOfFile(BG_LOADING_CONFIG_FILE_NAME);
		int count = plistDic->valueForKey("count")->intValue();
		int index = (CCRANDOM_0_1() * count + 1);
		auto bgFileName = CCString::createWithFormat("bg_loading_%03d.png",
			index);
		loadingImageFile = bgFileName->getCString();
	}
	else
	{
		loadingImageFile = this->m_pszLoadingImagePath.c_str();
	}

	auto point_center = ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);

	CCSprite* sprite = CCSprite::create(loadingImageFile);
    sprite->setPosition(point_center);
	this->addChild(sprite, 0);

	CCSprite* loadingBar = CCSprite::create(LOADING_BAR_FILE_NAME);
	//loadingBar->setScaleY(visibleSize.height / loadingBar->getContentSize().height);
	//loadingBar->setPositionX(origin.x + 20);
	//loadingBar->setPositionY(visibleSize.height / 2 + origin.y);
	//loadingBar->setPosition(point_center);

	auto loadingBarSize = loadingBar->getContentSize();

	CCProgressTimer* progressbar = CCProgressTimer::create(loadingBar);
	//progressbar->setType(CCProgressTimerType::kCCProgressTimerTypeBar);
	progressbar->setType(kCCProgressTimerTypeBar);
	
	progressbar->setScaleY(visibleSize.height / loadingBarSize.height);
	progressbar->setBarChangeRate(ccp(0, 1));
	progressbar->setMidpoint(ccp(0.5, 0));
	progressbar->setPositionX(origin.x + loadingBarSize.width / 2);
	progressbar->setPositionY(visibleSize.height / 2 + origin.y);
	
	this->addChild(progressbar, 1, TAG_PROGRESSBAR);
	return true;
}

MyLoadingLayer::MyLoadingLayer(void)
	:m_bIsDefaultLoadingImage(true)
{
}


MyLoadingLayer::MyLoadingLayer(const char* pszLoadingImagePath)
	:m_bIsDefaultLoadingImage(false),
	m_pszLoadingImagePath(pszLoadingImagePath)
{
}


MyLoadingLayer::~MyLoadingLayer(void)
{

}

void MyLoadingLayer::setProgress(ProgressEntity* progress)
{
	CCProgressTimer* progressbar = dynamic_cast<CCProgressTimer*>(this->getChildByTag(TAG_PROGRESSBAR));

	CCProgressFromTo* fromToAction = CCProgressFromTo::create(0.2f, progressbar->getPercentage(),
		progress->getFinishPercentage() * 100.f);
	progressbar->runAction(fromToAction);

	//progressbar->setPercentage(progress->getFinishPercentage() * 100);
	if (progress->getFinishPercentage() == 1)
		CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_LOADING_LAYER_LOADING_COMPLETE);
}