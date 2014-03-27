#pragma once
#include "cocos2d.h"
#include "myLib.h"

USING_NS_CC;

enum MyAlignment{
	MyAlignmentLeftCenter,
	MyAlignmentLeftTop,
	MyAlignmentLeftBottom,
	MyAlignmentRightCenter,
	MyAlignmentRightTop,
	MyAlignmentRightBottom,
	MyAlignmentTopCenter,
	MyAlignmentBottomCenter,
	MyAlignmentCenter
};

enum MyOrientation{
	MyOrientationLeftToRight,
	MyOrientationRightToLeft,
	MyOrientationTopToBottom,
	MyOrientationBottomToTop
};

// kind of StackPanel
class MyListView :
	public CCLayer
{
	CC_SYNTHESIZE_READONLY(CCDictionary*, m_IndexedChildren, IndexedChildren);
	CC_PROPERTY(MyOrientation, m_Orientation, Orientation);
	CC_PROPERTY(float, m_Padding, Padding);
	CC_PROPERTY(MyAlignment, m_Alignment, Alignment);

private:

	CCObject* m_pTarget;
	SEL_CallFuncN m_callback;
	CCNode* m_SelectedChild;

	void setChild(CCNode* child, const CCPoint& point);
	void setChildren();
	void getCenterPoint(CCPoint& point, float totalSize, float anotherOrientationSize);
	void onSelect(CCNode* child);

public:
	MyListView(void);
	~MyListView(void);

	virtual bool init(void);
	
	virtual void addChild(CCNode* child);
	virtual void addChild(CCNode* child, int zOrder);
	virtual void addChild(CCNode* child, int zOrder, int tag);

	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	bool isHorizontal(void);

	void registerSelectEvent(CCObject* target, SEL_CallFuncN callback);

	CREATE_FUNC(MyListView);
};

