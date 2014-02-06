#include "MyLayerOpacity.h"


MyLayerOpacity::MyLayerOpacity(void)
{
}


MyLayerOpacity::~MyLayerOpacity(void)
{
}

void MyLayerOpacity::setColor(const ccColor3B& color)
{
	CCLayerColor::setColor(color);
	CCObject* child;
	CCARRAY_FOREACH(this->getChildren(), child)
	{
		CCNode* node = dynamic_cast<CCNode*>(child);
		CCRGBAProtocol* protocol = dynamic_cast<CCRGBAProtocol*>(node);
		if (protocol)
		{
			protocol->setColor(color);
		}
	}
}

void MyLayerOpacity::setOpacityModifyRGB(bool bValue)
{
	CCLayerColor::setOpacityModifyRGB(bValue);
	CCObject* child;
	CCARRAY_FOREACH(this->getChildren(), child)
	{
		CCNode* node = dynamic_cast<CCNode*>(child);
		CCRGBAProtocol* protocol = dynamic_cast<CCRGBAProtocol*>(node);
		if (protocol)
		{
			protocol->setOpacity(bValue | protocol->isOpacityModifyRGB());
		}
	}
}

void MyLayerOpacity::setOpacity(GLubyte opacity)
{
	CCLayerColor::setOpacity(opacity);
	CCObject* child;
	CCARRAY_FOREACH(this->getChildren(), child)
	{
		CCNode* node = dynamic_cast<CCNode*>(child);
		CCRGBAProtocol* protocol = dynamic_cast<CCRGBAProtocol*>(node);
		if (protocol)
		{
			protocol->setOpacity(opacity * protocol->getOpacity());
		}
	}
}