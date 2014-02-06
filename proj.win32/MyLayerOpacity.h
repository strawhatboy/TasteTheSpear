#pragma once
#include "cocos2d.h"
USING_NS_CC;
class MyLayerOpacity
	: public CCLayerColor
{
	//CC_PROPERTY(GLubyte, m_nOpacity, Opacity)
	//CC_PROPERTY_PASS_BY_REF(cocos2d::ccColor3B, m_sColor, Color)

public:
	MyLayerOpacity(void);
	~MyLayerOpacity(void);

	virtual void setOpacityModifyRGB(bool bValue); 
	virtual void setColor(const ccColor3B& color);
	//virtual bool isOpacityModifyRGB(void);  
	virtual void setOpacity(GLubyte opacity);

	static MyLayerOpacity* create()
	{
		MyLayerOpacity *pLayer = new MyLayerOpacity();
        if (pLayer && pLayer->init())
		{
			pLayer->autorelease();
			//pRet->initWithColor(ccc4(255, 255, 255, 255));
			//pRet->setOpacityModifyRGB(true);
			return pLayer;
		}
		else
		{
			CC_SAFE_DELETE(pLayer);
			return NULL;
		}
	}

	static MyLayerOpacity* create(const ccColor4B& color, GLfloat width, GLfloat height)
	{
		MyLayerOpacity * pLayer = new MyLayerOpacity();
		if( pLayer && pLayer->initWithColor(color,width,height))
		{
			pLayer->autorelease();
			return pLayer;
		}
		CC_SAFE_DELETE(pLayer);
		return NULL;
	}

	static MyLayerOpacity* create(const ccColor4B& color)
	{
		MyLayerOpacity * pLayer = new MyLayerOpacity();
		if(pLayer && pLayer->initWithColor(color))
		{
			pLayer->autorelease();
			return pLayer;
		}
		CC_SAFE_DELETE(pLayer);
		return NULL;
	}
};

