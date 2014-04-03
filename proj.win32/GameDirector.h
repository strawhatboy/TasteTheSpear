#pragma once
#include "myLib.h"
#include "cocos2d.h"
#include "GameObjectTypesLoader.h"
#include "MenuScene.h"
#include "MyLoadingLayer.h"
#include "TexturedGameObject_Runtime.h"
#include "FightingUnit_Runtime.h"
#include "Hero_Runtime.h"
#include "Missile_Runtime.h"

enum GameState : int
{
	MAIN_MENU = 1,
	PRE_GAME = 2,
	GAMING = 4,
	GAME_PAUSED = 8,
	GAME_OVER = 16
};

typedef void (CCObject::*SEL_CallFuncInt)(int);
#define callfuncInt_selector(_SELECTOR) (SEL_CallFuncInt)(&_SELECTOR)

class ElapsedEvent : public CCObject
{
	CC_SYNTHESIZE(int, m_Count, Count);
	CC_SYNTHESIZE(float, m_Interval, Interval);
	CC_SYNTHESIZE(int, m_LuaCallback, LuaCallback);
	CC_SYNTHESIZE(SEL_CallFuncInt, m_Callback, Callback);
	CC_SYNTHESIZE(CCObject*, m_Target, Target);
	CC_SYNTHESIZE(bool, m_IsLuaEvent, IsLuaEvent);
	CREATE_FUNC(ElapsedEvent);

public:
	inline bool operator == (const ElapsedEvent& anotherEvent) const
	{
		if (this->getCallback() == anotherEvent.getCallback()
			&& this->getCount() == anotherEvent.getCount()
			&& this->getInterval() == anotherEvent.getInterval()
			&& this->getLuaCallback() == anotherEvent.getLuaCallback()
			&& this->getIsLuaEvent() == anotherEvent.getIsLuaEvent()
			&& this->getTarget() == anotherEvent.getTarget())
			return true;
		return false;
	}

	inline bool init(){return true;}

	inline void trigger()
	{
		m_Count--;
		if (m_IsLuaEvent)
		{
			auto luaStack = CCLuaEngine::defaultEngine()->getLuaStack();
			luaStack->pushInt(m_Count);
			luaStack->executeFunctionByHandler(m_LuaCallback, 1);
		}
		else
		{
			if (m_Target && m_Callback)
			{
				(m_Target->*m_Callback)(m_Count);
			}
		}
	}

	inline ElapsedEvent* clone()
	{
		ElapsedEvent* clonedEvent = ElapsedEvent::create();
		if (!clonedEvent)
			return NULL;

		clonedEvent->setCallback(this->getCallback());
		clonedEvent->setCount(this->getCount());
		clonedEvent->setInterval(this->getInterval());
		clonedEvent->setLuaCallback(this->getLuaCallback());
		clonedEvent->setIsLuaEvent(this->getIsLuaEvent());
		clonedEvent->setTarget(this->getTarget());
		return clonedEvent;
	}
};

class GameDirector :
	public CCObject
{
	CC_SYNTHESIZE(uint, m_GameState, GameState);
	CC_SYNTHESIZE(uint, m_LastGameState, LastGameState);
	CC_SYNTHESIZE(string, m_CurrentDistrict, CurrentDistrict);
	CC_SYNTHESIZE(string, m_CurrentLevel, CurrentLevel);
	CC_SYNTHESIZE(uint, m_CurrentDifficulty, CurrentDifficulty);
	CC_SYNTHESIZE(string, m_CurrentHero, CurrentHero);
	CC_SYNTHESIZE_READONLY(float, m_GameElapsedTime, GameElapsedTime);
	CC_SYNTHESIZE_READONLY(CCDictionary*, m_StateChangeParams, StateChangeParams);
	CC_SYNTHESIZE_READONLY(CCDictionary*, m_ElapsedEvents, ElapsedEvents);
	CC_SYNTHESIZE_READONLY(CCDictionary*, m_ElapsedEventsTriggeredFlag, ElapsedEventsTriggeredFlag);
	CC_SYNTHESIZE_READONLY(bool, m_IsClockTicking, IsClockTicking);

private:
	void setElapsedEvents(float elapsedTime, ElapsedEvent* _event);
	void initEventSystem();

	CCArray* m_EventTargets;

public:
	~GameDirector(void);

	string getUIStringByID(int nID);

	void changeState(int gameState, CCDictionary* dictParams = NULL);

	// these obj creation functions only available when gamestate == gaming
	TexturedGameObject_Runtime* createGameObject_Runtime(const char* pszID);
	FightingUnit_Runtime* createFightingUnit_Runtime(const char* pszID);
	Hero_Runtime* createHero_Runtime(const char* pszID);
	Missile_Runtime* createMissile_Runtime(const char* pszID);

	// WARNING: The reg functions below only works when Game is running. DONOT use it in other game state.

	// for in-script usage.
	void regGameElapsedEvent(float elapsedTime, int luaFunc);
	void regGameElapsedEvent(float elapsedTime, CCObject* target, SEL_CallFuncInt callback);	

	// multi-times call.
	void regGameElapsedEvent(float elapsedTime, int count, float interval, int luaFunc);
	void regGameElapsedEvent(float elapsedTime, int count, float interval, CCObject* target, SEL_CallFuncInt callback);

	void regGameEvent(const char* eventName, int luaFunc);
	void regGameEvent(const char* eventName, CCObject* target, SEL_CallFuncO callback);

	virtual void update(float dt);
	
    CCLayer* getGameLayer();

	CC_SHARED_CREATE_FUNC(GameDirector);

};

