#include "TutsauLayer.h"
TutsauLayer::TutsauLayer(void){}
TutsauLayer::TutsauLayer(const char* msg)
	: m_bIsInitWithMsgID(false), m_pszMsg(msg){}
	
TutsauLayer::TutsauLayer(const char* msgType, const char* msg)
	: m_bIsInitWithMsgID(false), m_pszMsg(msg), m_pszMsgType(msgType)
	{}
	
TutsauLayer::TutsauLayer(int msgID)
	: m_bIsInitWithMsgID(true), m_nMsgID(msgID)
	{}
	
TutsauLayer::TutsauLayer(int msgID, bool force)
	: m_bIsInitWithMsgID(true), m_nMsgID(msgID), m_bForced(force)
	{}
	
TutsauLayer::~TutsauLayer(void){
		CCLog("TutsauLayer disposed... and try to remove unused texture.");
		// clean image in texture cache
		CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
		CCTextureCache::sharedTextureCache()->removeUnusedTextures();
		CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
}
	
bool TutsauLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!this->initWithColor(ccc4(255, 0, 0, 50)));
		this->setTouchEnabled(true);
		this->setTouchPriority(TOUCH_PRIORITY_TUTSAULAYER);
		if (m_bIsInitWithMsgID)
		{
		}
		else
		{
			auto pDirector = CCDirector::sharedDirector();
			//auto pCurrentScene = pDirector->getRunningScene();
			//auto pLayer = CCLayerColor::create(ccc4(0, 0, 0, 50)); //grey
			//auto pChildLayer = CCLayerColor::create(ccc4(255, 255, 255, 254)); //white
			//pChildLayer->setCascadeColorEnabled(true);
			//pChildLayer->setCascadeOpacityEnabled(true);
			auto pChildLayer_Candidate = CCSprite::createWithTexture(getEmptyWhiteTexture());
			// stop all animations and all backgroud sounds
			// NO!! we can't call pDirector->stopAnimations() !!! pause() is fine.
			pDirector->pause();
			SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
			// we'll put image and msg into the childLayer
			auto visibleSize = pDirector->getVisibleSize();
			auto origin = pDirector->getVisibleOrigin();
			auto center = ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
			//this->setContentSize(visibleSize);
			//this->setPosition(origin);
			
			CCSprite* sprite = CCSprite::create(CCString::createWithFormat("%s/%s%s", FOLDER_TUTSAU, this->m_pszMsgType, STR_TUTSAU_FILE_SUFFIX)->getCString());
			// sprite and the words should occupy 4/5 of the width.
			auto childLayerContentWidth = 0.8 * visibleSize.width;
			auto spriteSize = sprite->getContentSize();
			auto wordsWidth = childLayerContentWidth - spriteSize.width;
			CCLabelTTF* label = CCLabelTTF::create(this->m_pszMsg, STR_TUTSAU_FONTS, FONT_SIZE_TUTSAU, CCSizeMake(wordsWidth, 0),
				CCTextAlignment::kCCTextAlignmentLeft, CCVerticalTextAlignment::kCCVerticalTextAlignmentTop);
			label->setColor(ccc3(0, 0, 0));
			auto childLayerContentHeight = MAX(spriteSize.height, label->getContentSize().height) + 20;

			auto spritePosition = ccp(center.x - childLayerContentWidth / 2 + spriteSize.width / 2,
				center.y - childLayerContentHeight / 2 + childLayerContentHeight / 2);
			auto wordsPosition = ccp(center.x + childLayerContentWidth / 2 - wordsWidth /2,
				center.y - childLayerContentHeight / 2 + childLayerContentHeight / 2);
			sprite->setPosition(spritePosition);
			label->setPosition(wordsPosition);
			auto pChildLayer_Candidate_Size = pChildLayer_Candidate->getContentSize();
			pChildLayer_Candidate->setScaleX(visibleSize.width / pChildLayer_Candidate_Size.width);
			pChildLayer_Candidate->setScaleY(childLayerContentHeight / pChildLayer_Candidate_Size.height);
			pChildLayer_Candidate->setPosition(center);
			//pChildLayer->setContentSize(CCSizeMake(visibleSize.width, childLayerContentHeight));
			//pChildLayer->addChild(sprite, 100);
			//pChildLayer->addChild(label, 100);
			//pChildLayer->setPosition(ccp(center.x - visibleSize.width / 2, center.y - childLayerContentHeight / 2));
			this->addChild(pChildLayer_Candidate);
			this->addChild(sprite);
			this->addChild(label);
			//auto anotherLayer = CCLayerColor::create(ccc4(60, 60, 60, 60));
			//anotherLayer->setPosition(center);
			//anotherLayer->setContentSize(CCSizeMake(20, 600));
			//this->addChild(anotherLayer);
		}
		bRet = true;
	} while(0);
	return bRet;
}
	
void TutsauLayer::onEnter()
{
	CCLayerColor::onEnter();
	
	//this->setCascadeColorEnabled(false);
	//CCDirector::sharedDirector()->resume();
	setEnableRecursiveCascading(this, true);
}
	
static void setEnableRecursiveCascading(CCNode* node, bool enable)
{
    CCRGBAProtocol* rgba = dynamic_cast<CCRGBAProtocol*>(node);
    if (rgba)
    {
		rgba->setCascadeColorEnabled(enable);
		rgba->setCascadeOpacityEnabled(enable);
    }
    
    CCObject* obj;
    CCArray* children = node->getChildren();
    CCARRAY_FOREACH(children, obj)
    {
		CCNode* child = (CCNode*)obj;
        setEnableRecursiveCascading(child, enable);
	}
}


void TutsauLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, TOUCH_PRIORITY_TUTSAULAYER, true);
	CCLayerColor::registerWithTouchDispatcher();
}

bool TutsauLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCLog("--------------");
	CCLog("Touch began");
	// always swallow all the other touches
	return true;
}

void TutsauLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCLog("--------------");
	CCLog("Touch ended");
	CCDirector::sharedDirector()->resume();
	this->runAction(CCSequence::create(CCFadeOut::create(.3f),
	CCCallFunc::create(this, callfunc_selector(TutsauLayer::delayRemoveSelf)), NULL));
	// remove this node from its parent;
	//this->getParent()->removeChild(this, true);
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}
	
void TutsauLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{}


void TutsauLayer::delayRemoveSelf()
{
	this->removeFromParentAndCleanup(true);
}
