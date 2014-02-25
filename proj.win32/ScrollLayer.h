#pragma once

#include "cocos2d.h"
#include "myLib.h"

USING_NS_CC;

class ScrollLayer :
	public CCLayer
{
private:
	CCPoint m_touchBeganPoint;
	bool m_bHorizontal;
	CCSize m_size;
	CCSize m_point;
	CCLayer* m_pContentLayer;
	CCArray* m_pLayers;
	CCObject* m_pTarget;
	CCLayer* m_pLayerCovered;
	bool m_bMoved;
	// true for positive.
	bool m_bFirstSign;
	SEL_CallFuncO m_callback;

	float getMovedDis(CCPoint currentPoint);

	CC_SYNTHESIZE_READONLY(int, m_nIndex, Index);

public:

	// [Default] size = CCSizeZero;
	// [Default] point = CCPointZero;
	// [Default] horizonal = true;
	// size: the contentSize of the each of the layers
	// point: location of the layers, bottom left.
	// horizontal:...
	ScrollLayer(CCArray* layers, const CCSize& size, const CCPoint& point, bool horizontal);
	~ScrollLayer(void);

	virtual bool init(void);
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	// [Default] size = CCSizeZero; Will use the design resolution instead.
	// [Default] point = CCPointZero; 
	// [Default] horizonal = true;
	// size: the contentSize of the layers container.
	// point: location of the layers container, bottom left.
	// horizontal:...
	static ScrollLayer* createWithLayers(CCArray* layers, 
		const CCSize& size = CCSizeZero, 
		const CCPoint& point = CCPointZero, 
		bool horizontal = true)
	{
		auto pRet = new ScrollLayer(layers, size, point, horizontal);
		if (pRet && pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		else
		{
			CC_SAFE_DELETE(pRet);
			return NULL;
		}
	}

	void registerSelectEvent(CCObject* target, SEL_CallFuncO callback);
};

