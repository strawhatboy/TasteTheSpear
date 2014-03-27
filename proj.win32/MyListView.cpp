#include "MyListView.h"

#define ANIMATION_INTERVAL 0.3f

MyListView::MyListView(void)
{
	m_Orientation = MyOrientationTopToBottom;
	m_Padding = 10.f;
	m_Alignment = MyAlignmentCenter;
	INIT_POINTER(m_SelectedChild);
	INIT_POINTER(m_pTarget);
	INIT_POINTER(m_callback);
}


MyListView::~MyListView(void)
{
}

bool MyListView::init()
{
	this->setTouchEnabled(true);
	return true;
}

void MyListView::addChild(CCNode* child)
{
	CCLayer::addChild(child);
	setChildren();
}

void MyListView::addChild(CCNode* child, int zOrder)
{
	CCLayer::addChild(child, zOrder);
	setChildren();
}

void MyListView::addChild(CCNode* child, int zOrder, int tag)
{
	CCLayer::addChild(child, zOrder, tag);
	setChildren();
}

void MyListView::setChildren()
{
	auto children = this->getChildren();
	unsigned int count = 0;
	float totalSize = 0;
	unsigned int totalCount = this->getChildrenCount();
	float maxOtherOrientationSize = 0;

	CCObject* obj = NULL;
	CCARRAY_FOREACH(children, obj)
	{
		CCNode* node = dynamic_cast<CCNode*>(obj);
		CC_CONTINUE_IF(node == NULL);
		auto contentSize = node->getContentSize();
		if (isHorizontal())
		{
			totalSize += contentSize.width;
			maxOtherOrientationSize = MAX(maxOtherOrientationSize, contentSize.height);
		}
		else
		{
			totalSize += contentSize.height;
			maxOtherOrientationSize = MAX(maxOtherOrientationSize, contentSize.width);
		}

		// will not add the padding at last element.
		if (count++ != totalCount - 1)
			totalSize += m_Padding;
	}

	CCPoint centerPoint;
	getCenterPoint(centerPoint, totalSize, maxOtherOrientationSize);
	
	count = 0;
	obj = NULL;
	CCPoint startPos;
	bool bSignFlag;
	if (isHorizontal())
	{
		bSignFlag = m_Orientation == MyOrientationLeftToRight;

		startPos = bSignFlag ? ccpSub(centerPoint, ccp(totalSize / 2.f, 0)) : 
			ccpAdd(centerPoint, ccp(totalSize / 2.f, 0));
	}
	else
	{
		bSignFlag = m_Orientation == MyOrientationBottomToTop;
		startPos = bSignFlag ? ccpSub(centerPoint, ccp(0, totalSize / 2.f))
			: ccpAdd(centerPoint, ccp(0, totalSize / 2.f));
	}

	CCARRAY_FOREACH(children, obj)
	{
		CCNode* node = dynamic_cast<CCNode*>(obj);
		CC_CONTINUE_IF(node == NULL);
		auto nodeSize = node->getContentSize();

		if (isHorizontal())
		{

			CCPoint childPos;

			if (m_Alignment == MyAlignmentLeftTop ||
				m_Alignment == MyAlignmentRightTop ||
				m_Alignment == MyAlignmentTopCenter)
			{
				childPos = bSignFlag ? ccpAdd(startPos, ccpMult(ccp(nodeSize.width, maxOtherOrientationSize - nodeSize.height), .5f))
					: ccpAdd(startPos, ccpMult(ccp(-nodeSize.width, maxOtherOrientationSize - nodeSize.height), .5f));
			}
			else if (m_Alignment == MyAlignmentLeftCenter ||
				m_Alignment == MyAlignmentRightCenter ||
				m_Alignment == MyAlignmentCenter)
			{
				childPos = bSignFlag ? ccpAdd(startPos, ccp(nodeSize.width / 2.f, 0))
					: ccpSub(startPos, ccp(nodeSize.width / 2.f, 0));
			}
			else 
			{
				childPos = bSignFlag ? ccpAdd(startPos, ccpMult(ccp(nodeSize.width, nodeSize.height - maxOtherOrientationSize), .5f))
					: ccpAdd(startPos, ccpMult(ccp(-nodeSize.width, nodeSize.height - maxOtherOrientationSize), .5f));
			}

			setChild(node, childPos);

			if (count++ != totalCount - 1)
				startPos = bSignFlag ? ccpAdd(startPos, ccp(nodeSize.width + m_Padding, 0))
					: ccpSub(startPos, ccp(nodeSize.width + m_Padding, 0));
		}
		else
		{

			CCPoint childPos;
			if (m_Alignment == MyAlignmentLeftCenter ||
				m_Alignment == MyAlignmentLeftTop ||
				m_Alignment == MyAlignmentLeftBottom)
			{
				childPos = bSignFlag ? ccpAdd(startPos, ccpMult(ccp(nodeSize.width - maxOtherOrientationSize, nodeSize.height), .5f))
					: ccpAdd(startPos, ccpMult(ccp(nodeSize.width - maxOtherOrientationSize, -nodeSize.height), .5f));
			}
			else if (m_Alignment == MyAlignmentTopCenter ||
				m_Alignment == MyAlignmentBottomCenter ||
				m_Alignment == MyAlignmentCenter)
			{
				childPos = bSignFlag ? ccpAdd(startPos, ccp(0, nodeSize.width / 2.f))
					: ccpSub(startPos, ccp(0, nodeSize.width / 2.f));
			}
			else
			{
				childPos = bSignFlag ? ccpAdd(startPos, ccpMult(ccp(maxOtherOrientationSize - nodeSize.width, nodeSize.height), .5f))
					: ccpAdd(startPos, ccpMult(ccp(maxOtherOrientationSize - nodeSize.width, -nodeSize.height), .5f));
			}

			setChild(node, childPos);

			if (count++ != totalCount - 1)
				startPos = bSignFlag ? ccpAdd(startPos, ccp(0, nodeSize.height + m_Padding))
					: ccpSub(startPos, ccp(0, nodeSize.height + m_Padding));
		}
	}
}

void MyListView::getCenterPoint(CCPoint& point, float totalSize, float anotherOrientationSize)
{
	auto size = this->getContentSize();
	auto _isHorizontal = isHorizontal();
	switch (m_Alignment)
	{
	case MyAlignmentLeftCenter:
		point = _isHorizontal ? (ccpMult(ccp(totalSize, size.height), .5f))
			: (ccpMult(ccp(anotherOrientationSize, size.height), .5f));
		break;
	case MyAlignmentLeftTop:
		point = _isHorizontal ? (ccp(totalSize / 2.f, size.height - anotherOrientationSize / 2.f))
			: (ccp(anotherOrientationSize / 2.f, size.height - totalSize / 2.f));
		break;
	case MyAlignmentLeftBottom:
		point = _isHorizontal ? (ccpMult(ccp(totalSize, anotherOrientationSize), .5f))
			: (ccpMult(ccp(anotherOrientationSize, totalSize), .5f));
		break;
	case MyAlignmentRightCenter:
		point = _isHorizontal ? (ccp(size.width - totalSize / 2.f, size.height / 2.f))
			: (ccp(size.width - anotherOrientationSize / 2.f, size.height / 2.f));
		break;
	case MyAlignmentRightTop:
		point = _isHorizontal ? (ccp(size.width - totalSize / 2.f, size.height - anotherOrientationSize / 2.f))
			: (ccp(size.width - anotherOrientationSize / 2.f, size.height - totalSize / 2.f));
		break;
	case MyAlignmentRightBottom:
		point = _isHorizontal ? (ccp(size.width - totalSize / 2.f, anotherOrientationSize / 2.f))
			: (ccp(size.width - anotherOrientationSize / 2.f, totalSize / 2.f));
		break;
	case MyAlignmentTopCenter:
		point = _isHorizontal ? (ccp(size.width / 2.f, size.height - anotherOrientationSize / 2.f))
			: (ccp(size.width / 2.f, size.height - totalSize / 2.f));
		break;
	case MyAlignmentBottomCenter:
		point = _isHorizontal ? (ccpMult(ccp(size.width, anotherOrientationSize), .5f))
			: (ccpMult(ccp(size.width, totalSize), .5f));
		break;
	case MyAlignmentCenter:
	default:
		point = ccpMult(size, .5f);
		break;
	}
}

void MyListView::setChild(CCNode* child, const CCPoint& point)
{
	CCLog("before move the child's location is (%.3f:%.3f).", child->getPositionX(), child->getPositionY());
	child->stopActionByTag(100);
	auto moveAnimation = CCMoveTo::create(ANIMATION_INTERVAL, point);
	moveAnimation->setTag(100);
	child->runAction(moveAnimation);
	//child->setPosition(point);
}

MyOrientation MyListView::getOrientation()
{
	return this->m_Orientation;
}

void MyListView::setOrientation(MyOrientation value)
{
	this->m_Orientation = value;
	this->setChildren();
}

MyAlignment MyListView::getAlignment()
{
	return this->m_Alignment;
}

void MyListView::setAlignment(MyAlignment alignment)
{
	this->m_Alignment = alignment;
	this->setChildren();
}

float MyListView::getPadding()
{
	return this->m_Padding;
}

void MyListView::setPadding(float value)
{
	this->m_Padding = value;
	this->setChildren();
}

bool MyListView::isHorizontal(void)
{
	if (m_Orientation == MyOrientationLeftToRight ||
		m_Orientation == MyOrientationRightToLeft)
		return true;
	return false;
}

void MyListView::registerSelectEvent(CCObject* target, SEL_CallFuncN callback)
{
	this->m_pTarget = target;
	this->m_callback = callback;
}

void MyListView::onSelect(CCNode* child)
{
	if (this->m_pTarget != NULL && this->m_callback != NULL)
	{
		(this->m_pTarget->*m_callback)(child);
	}
}


void MyListView::registerWithTouchDispatcher(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

bool MyListView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCLog("ListView Touch Began");
	auto location = pTouch->getLocation();
	CCObject* obj = NULL;
	auto children = this->getChildren();
	auto count = 0;
	CCARRAY_FOREACH(children, obj)
	{
		CCNode* child = dynamic_cast<CCNode*>(obj);
		CC_CONTINUE_IF(child == NULL);

		if (child->boundingBox().containsPoint(location))
		{
			CCLog("[MyListView] Location (%.3f:%.3f) is in boundingBox of the %dth element in MyListView", location.x, location.y, count);
			m_SelectedChild = child;
		}
		count++;
	}
	return true;
}

void MyListView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	do
	{
		CC_BREAK_IF(m_SelectedChild == NULL);
		auto location = pTouch->getLocation();
		if (m_SelectedChild->boundingBox().containsPoint(location))
			onSelect(m_SelectedChild);

		// just set NULL.
		m_SelectedChild = NULL;
	} while (0);
}

void MyListView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	do
	{
		CC_BREAK_IF(m_SelectedChild == NULL);
		auto location = pTouch->getLocation();
		if (!m_SelectedChild->boundingBox().containsPoint(location))
		{
			// just set NULL.
			m_SelectedChild = NULL;
			CCLog("[MyListView] The touch move out of the element, cancel the select operation.");
		}

	} while (0);
}