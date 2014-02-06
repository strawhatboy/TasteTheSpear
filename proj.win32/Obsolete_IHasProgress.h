//#pragma once
//
//#include "cocos2d.h"
//#include "myLib.h"
//
//USING_NS_CC;
//
//class IHasProgress : public CCObject
//{
//protected:
//	int m_maxValue;
//	int m_currentValue;
//	int m_minValue;
//
//public:
//	IHasProgress(void);
//	~IHasProgress(void);
//
//	virtual void setMaxValue(int value);
//	virtual void setMinValue(int value);
//	virtual void setCurrentValue(int value);
//	virtual int getMaxValue() const;
//	virtual int getMinValue() const;
//	virtual int getCurrentValue() const;
//	virtual double getFinishPercentage() const;
//	
//	void addListener(SEL_BroadcastProgress);
//	void removeListener(void);
//
//private:
//	SEL_BroadcastProgress m_fp_BroadcastProgress;
//
//protected:
//	void onProgressBroadcasted(int, int, int);
//};
//
