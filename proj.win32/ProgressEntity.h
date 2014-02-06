#pragma once
#include "cocos2d.h"

USING_NS_CC;

class ProgressEntity : 
	public CCObject
{
protected:
	int m_maxValue;
	int m_currentValue;
	int m_minValue;
public:
	ProgressEntity(void);
	~ProgressEntity(void);

	void setMaxValue(int value);
	void setMinValue(int value);
	void setCurrentValue(int value);
	int getMaxValue() const;
	int getMinValue() const;
	int getCurrentValue() const;
	float getFinishPercentage() const;
};

