#include "GameLayer.h"


GameLayer::GameLayer(void)
{
	INIT_POINTER(m_Touches);
	m_Touches = CCDictionary::create();
	m_Touches->retain();
}


GameLayer::~GameLayer(void)
{
	CC_SAFE_RELEASE(m_Touches);
}

bool GameLayer::init()
{
	INIT_START

	CC_BREAK_IF(!CCLayer::init());
	this->setTouchEnabled(true);
	this->addChild(GameHudLayer::create());

	INIT_TRUE
	INIT_END
}

void GameLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCLog("GameLayer Touches Began.");
	auto touches = m_Touches;
	for_each(pTouches->begin(), pTouches->end(), [&touches](CCObject* obj){
		auto touch = dynamic_cast<CCTouch*>(obj);
		touches->setObject(touch, touch->getID());
		CCDictionary* params = CCDictionary::create();
		params->setObject(touch, EVENT_CONTROL_TOUCH_PARAMS_TOUCH);
		CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_CONTROL_TOUCH_BEGAN, params);
	});
}
void GameLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{	
	auto touches = m_Touches;
	for_each(pTouches->begin(), pTouches->end(), [&touches](CCObject* obj){
		auto touch = dynamic_cast<CCTouch*>(obj);
		CCDictionary* params = CCDictionary::create();
		params->setObject(touch, EVENT_CONTROL_TOUCH_PARAMS_TOUCH);
		CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_CONTROL_TOUCH_MOVED, params);
	});
}
void GameLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	auto touches = m_Touches;
	for_each(pTouches->begin(), pTouches->end(), [&touches](CCObject* obj){
		auto touch = dynamic_cast<CCTouch*>(obj);
		CCDictionary* params = CCDictionary::create();
		params->setObject(touch, EVENT_CONTROL_TOUCH_PARAMS_TOUCH);
		CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_CONTROL_TOUCH_ENDED, params);
	});
}
void GameLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
	ccTouchesEnded(pTouches, pEvent);
}