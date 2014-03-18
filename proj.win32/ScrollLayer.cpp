#include "ScrollLayer.h"
#include "AppMacros.h"

ScrollLayer::ScrollLayer(CCArray* layers, 
	const CCSize& size = CCSizeZero, 
	const CCPoint& point = CCPointZero, 
	bool horizontal = true) : 
	m_pLayers(layers),
	m_size(size),
	m_point(point),
	m_bHorizontal(horizontal)
{
	CCLog("ScrollLayer created?!");
	this->m_pLayers->retain();
	this->m_nIndex = 0;

	INIT_POINTER(m_pContentLayer);
	//INIT_POINTER(m_pLayers);
	INIT_POINTER(m_pLayerCovered);
	INIT_POINTER(m_pTarget);
	INIT_POINTER(m_callback);
}


ScrollLayer::~ScrollLayer(void)
{
	CCLog("ScrollLayer deleted?!");
	this->m_pLayers->release();
}


void ScrollLayer::registerWithTouchDispatcher(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

bool ScrollLayer::init()
{
	if (!CCLayer::init())
		return false;

	this->setTouchEnabled(true);
	this->setTouchMode(kCCTouchesOneByOne);
	if (this->m_size.equals(CCSizeZero))
	{
		// use the design size
		this->m_size = designResolutionSize;
	}

	// just use the CCPointZero
	//if (this->m_point.equals(CCPointZero))
	//{
	//	// mid of the screen
	//	this->m_point = CCPCenterScreen;
	//}

	
	this->m_pContentLayer = CCLayer::create();
	//this->m_pContentLayer->setPosition(ccpSub(this->m_point, ccpMult(this->m_size, 0.5f)));
	
	int count = 0;

	CCObject* obj = NULL;
	CCARRAY_FOREACH(this->m_pLayers, obj)
	{
		CCLayer* layer = dynamic_cast<CCLayer*>(obj);
		CC_CONTINUE_IF(layer == NULL);

		// add layers to contentLayer
		if (this->m_bHorizontal)
		{
			layer->setPosition(this->m_size.width * count, 0);
		}
		else
		{
			layer->setPosition(0, this->m_size.height * count);
		}
		layer->setContentSize(this->m_size);
		this->m_pContentLayer->addChild(layer);
		count++;
	}

	if (this->m_bHorizontal)
		this->m_pContentLayer->setContentSize(CCSizeMake(this->m_size.width * count, this->m_size.height));
	else
		this->m_pContentLayer->setContentSize(CCSizeMake(this->m_size.width, this->m_size.height * count));

	this->m_pContentLayer->setPosition(CCPointZero);

	// put the contentLayer into a clipping node
	CCDrawNode* stencil = CCDrawNode::create();
	CCPoint rect[4];
	rect[0] = ccp(0, 0);
	rect[1] = ccp(this->m_size.width, 0);
	rect[2] = ccp(this->m_size.width, this->m_size.height);
	rect[3] = ccp(0, this->m_size.height);
	ccColor4F white = {1, 1, 1, 1};
	stencil->drawPolygon(rect, 4, white, 0, white);
	CCClippingNode *clipper= CCClippingNode::create(stencil);
	clipper->addChild(this->m_pContentLayer);
	clipper->setPosition(this->m_point);
	//clipper->setPosition(ccpAdd(this->m_point, ccpSub(CCPCenterScreen, ccpMult(this->m_size, 0.5f))));

	// TODO: Add another 2 Gradient layer to left and right/top and bottom


	this->addChild(clipper);
	return true;
}

float ScrollLayer::getMovedDis(CCPoint currentPoint)
{
	if (this->m_bHorizontal)
		return currentPoint.x - this->m_touchBeganPoint.x;
	else
		return currentPoint.y - this->m_touchBeganPoint.y;
}

bool ScrollLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	this->m_bMoved = false;
	this->m_touchBeganPoint = pTouch->getLocation();
	//CCLog("ScrollLayer touch began, point: %f, %f", this->m_touchBeganPoint.x, this->m_touchBeganPoint.y);

	this->m_pLayerCovered = CCLayerColor::create(ccc4(0, 0, 0, 50));
	this->addChild(this->m_pLayerCovered);

	return true;
}

void ScrollLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	//CCLog("ScrollLayer touch ended, point: %f, %f", pTouch->getLocation().x, pTouch->getLocation().y);
	//CCLog("View point: %f, %f", pTouch->getLocationInView().x, pTouch->getLocationInView().y);

	// we can start change page when moveDis is larger than 2/5 of the page size.
	auto moveDis = getMovedDis(pTouch->getLocation());
	float moveDisAbs = abs(moveDis);
	if (this->m_bMoved)
	{
		auto index = this->getIndex();
			if (moveDisAbs > 0.4 * (this->m_bHorizontal ? this->m_size.width : this->m_size.height))
			{
				// switch to next page.
				//CCEaseSineOut::create(CCMoveTo::create(0.2, 
				if (moveDis > 0 && index > 0)
					// move to the left one.
					index--;

				if (moveDis < 0 && index < this->m_pLayers->count() - 1)
					// move to the right one.
					index++;

			}

		this->m_pContentLayer->runAction(
			CCEaseSineOut::create(
				CCMoveTo::create(0.2f, this->m_bHorizontal ? 
					ccp(-1-index * this->m_size.width, 0) :
					ccp(0, -1-index * this->m_size.height))));
		this->m_nIndex = index;
	}
	else
	{
		if (this->m_pTarget && this->m_callback)
			(this->m_pTarget->*(this->m_callback))(this->m_pLayers->objectAtIndex(this->m_nIndex));
		if (this->m_pLayerCovered)
			this->removeChild(this->m_pLayerCovered);
	}

	this->m_bMoved = false;
}

void ScrollLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	float moveDis = getMovedDis(pTouch->getLocation());
	float moveDisAbs = abs(moveDis);
	if (moveDisAbs > 50 && this->m_bMoved == false)
	{
		this->m_bMoved = true;
		this->m_bFirstSign = moveDis > 0 ? true : false;
		if (this->m_pLayerCovered)
			this->removeChild(this->m_pLayerCovered);
	}

	if (this->m_bMoved)
	{
		auto maxIndex = this->m_pLayers->count() - 1;

		auto newPos = this->m_bFirstSign ? moveDis - 50 : moveDis + 50;

		auto unitLength = (this->m_bHorizontal ? this->m_size.width : this->m_size.height);

		//auto newIndex = this->getIndex() - static_cast<int>(newPos / unitLength);
		//if (newIndex >=0 && newIndex <= maxIndex)
		//	this->m_nIndex = newIndex;

		auto currentIndex = this->getIndex();

		if ((currentIndex <= 0 || currentIndex >= maxIndex) && maxIndex != 1)
		{
			// will never move more than 2/5 of the size;
			newPos = newPos * 0.4; //* (this->m_bHorizontal ? this->m_size.width : this->m_size.height);
		}
		if (this->m_bHorizontal)
		{
			this->m_pContentLayer->setPositionX(newPos - currentIndex * unitLength);
		}
		else
		{
			this->m_pContentLayer->setPositionY(newPos - currentIndex * unitLength);
		}
	}
}

void ScrollLayer::registerSelectEvent(CCObject* target, SEL_CallFuncO callback)
{
	this->m_pTarget = target;
	this->m_callback = callback;
}