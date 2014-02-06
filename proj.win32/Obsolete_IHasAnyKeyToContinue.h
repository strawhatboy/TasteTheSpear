//#pragma once
//
//#include "cocos2d.h"
//#include "myLib.h"
//
//USING_NS_CC;
//
//typedef void (CCObject::*SEL_Finish)(void);
//typedef void (CCObject::*SEL_Continue)(void);
//#define FINISH_SELECTOR(_SELECTOR) SEL_Finish(&_SELECTOR)
//#define CONTINUE_SELECTOR(_SELECTOR) SEL_Continue(&_SELECTOR)
//
//class IHasAnyKeyToContinue : public CCObject
//{
//protected:
//	SEL_Finish Finish;
//	SEL_Continue Continue;
//	bool m_bAnyKeyToContinueEnabled;
//public:
//	IHasAnyKeyToContinue(void);
//	~IHasAnyKeyToContinue(void);
//	virtual void OnFinish(void);
//	virtual void OnContinue(void);
//	virtual void AddFinishListener(SEL_Finish);
//	virtual void AddContinueListener(SEL_Continue);
//	virtual void EnableAnyKeyToContinue(bool enable);
//	virtual bool IsAnyKeyToContinueEnabled();
//};
//
