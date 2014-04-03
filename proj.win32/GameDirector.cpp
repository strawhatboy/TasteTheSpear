#include "GameDirector.h"
#include "GameTextureBatchCenter.h"

CC_SHARED_CREATE_IMPL(GameDirector);

#define GAMESTATE_GAMING_PRE_CHECK 	if (m_GameState != GAMING)\
	{\
		CCLog("Cannot do operations when it's not in the game.");\
		return NULL;\
	}

GameDirector::GameDirector(void)
{
	INIT_POINTER(m_StateChangeParams);
	INIT_POINTER(m_ElapsedEvents);
	INIT_POINTER(m_ElapsedEventsTriggeredFlag);
	INIT_POINTER(m_EventTargets);
	m_ElapsedEvents = CCDictionary::create();
	m_ElapsedEventsTriggeredFlag = CCDictionary::create();
	m_EventTargets = CCArray::create();
	CC_SAFE_RETAIN(m_ElapsedEvents);
	CC_SAFE_RETAIN(m_ElapsedEventsTriggeredFlag);
	CC_SAFE_RETAIN(m_EventTargets);
	CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
}


GameDirector::~GameDirector(void)
{
	CC_SAFE_RELEASE(m_StateChangeParams);
	CC_SAFE_RELEASE(m_ElapsedEvents);
	CC_SAFE_RELEASE(m_ElapsedEventsTriggeredFlag);
	CC_SAFE_RELEASE(m_EventTargets);
}

string GameDirector::getUIStringByID(int nID)
{
	return GameObjectTypesLoader::sharedInstance()->getStringResourceTypeByID("S002")->getStringByKey(nID);
}

void GameDirector::changeState(int state, CCDictionary* dictParams)
{
	auto notificationCenter = CCNotificationCenter::sharedNotificationCenter();
	CCDictionary* params = CCDictionary::create();
	params->setObject(CCString::createWithFormat("%d", m_GameState), EVENT_GAME_STATE_CHANGE_PARAMS_LAST_STATE);
	params->setObject(CCString::createWithFormat("%d", state), EVENT_GAME_STATE_CHANGE_PARAMS_STATE);

	// value cannot be NULL in CCDictionary, oh shit, wtf!!
	dictParams ? params->setObject(dictParams, EVENT_GAME_STATE_CHANGE_PARAMS_PARAMS) : 0;
	notificationCenter->postNotification(EVENT_GAME_STATE_CHANGED, params);

	
	// msg hijacking is allowedd
	m_LastGameState = ((CCString*)params->objectForKey(EVENT_GAME_STATE_CHANGE_PARAMS_LAST_STATE))->intValue();
	m_GameState = ((CCString*)params->objectForKey(EVENT_GAME_STATE_CHANGE_PARAMS_STATE))->intValue();
	CC_SAFE_RELEASE(m_StateChangeParams);
	m_StateChangeParams = dynamic_cast<CCDictionary*>(params->objectForKey(EVENT_GAME_STATE_CHANGE_PARAMS_PARAMS));
	CC_SAFE_RETAIN(m_StateChangeParams);

	switch (state)
	{
	case MAIN_MENU:
		// move to main menu		
		{
		auto menu = MenuScene::create();
		LoadingScene::sharedInstance()->SetLoadingLayer(MyLoadingLayer::create());
		//pDirector->replaceScene(LoadingScene::sharedInstance());
		SceneManager::sharedInstance()->loadScene(menu);
		}
		break;
	case PRE_GAME:
		// move to district select scene
		{
		auto districtScene = DistrictSelectScene::create();
		LoadingScene::sharedInstance()->SetLoadingLayer(MyLoadingLayer::create());
		//pDirector->replaceScene(LoadingScene::sharedInstance());
		SceneManager::sharedInstance()->loadScene(districtScene);
		}
		break;
	case GAMING:
		// move to game stage, execute stage script


		break;
	case GAME_PAUSED:
		// pause the running game. show main menu layer.
		break;
	case GAME_OVER:
		// show game over layer.
		break;
	default:
		// error
		break;
	}
}

TexturedGameObject_Runtime* GameDirector::createGameObject_Runtime(const char* pszID)
{
	GAMESTATE_GAMING_PRE_CHECK;
	auto loader = GameObjectTypesLoader::sharedInstance();
	auto objType = loader->getGameObjectTypeByID(pszID);
	if (!objType) 
		return NULL;

	TexturedGameObject_Runtime* ret = NULL;
	string objTypeString = objType->getObjectType();
	if (objTypeString == STR_FIGHTINGUNIT)
	{
		ret = FightingUnit_Runtime::createWithFightingUnitType((FightingUnitType*)objType);
	}
	else if (objTypeString == STR_HERO || STR_BOSS)
	{
		ret = Hero_Runtime::createWithHeroType((HeroType*)objType);
	}
	else if (objTypeString == STR_MISSILE)
	{
		ret = Missile_Runtime::createWithMissileType((MissileType*)objType);
	}
	else 
	{
		ret = TexturedGameObject_Runtime::createWithTexturedGameObjectType((TexturedGameObjectType*)objType);
	}

	GameTextureBatchCenter::sharedInstance()->catchNewTexturedGameObject_Runtime(ret);

	return ret;
}

FightingUnit_Runtime* GameDirector::createFightingUnit_Runtime(const char* pszID)
{
	//GAMESTATE_GAMING_PRE_CHECK;
	return dynamic_cast<FightingUnit_Runtime*>(createGameObject_Runtime(pszID));
}

Hero_Runtime* GameDirector::createHero_Runtime(const char* pszID)
{
	//GAMESTATE_GAMING_PRE_CHECK;
	return dynamic_cast<Hero_Runtime*>(createGameObject_Runtime(pszID));
}

Missile_Runtime* GameDirector::createMissile_Runtime(const char* pszID)
{
	//GAMESTATE_GAMING_PRE_CHECK;
	return dynamic_cast<Missile_Runtime*>(createGameObject_Runtime(pszID));
}

CCLayer* GameDirector::getGameLayer()
{
	GAMESTATE_GAMING_PRE_CHECK;
	auto gameLayer = dynamic_cast<CCLayer*>(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_GAMELAYER));
	return gameLayer;
}

void GameDirector::initEventSystem()
{
	m_GameElapsedTime = 0.f;
	m_ElapsedEvents->removeAllObjects();
	m_ElapsedEventsTriggeredFlag->removeAllObjects();
	m_EventTargets->removeAllObjects();
	m_IsClockTicking = true;
}
// Game events handlers

void GameDirector::regGameElapsedEvent(float elapsedTime, int luaFunc)
{
	regGameElapsedEvent(elapsedTime, 1, 0, luaFunc);
}

void GameDirector::regGameElapsedEvent(float elapsedTime, CCObject* target, SEL_CallFuncInt callback)
{
	regGameElapsedEvent(elapsedTime, 1, 0, target, callback);
}

void GameDirector::regGameElapsedEvent(float elapsedTime, int count, float interval, int luaFunc)
{
	auto _event = ElapsedEvent::create();
	_event->setIsLuaEvent(true);
	_event->setCount(count);
	_event->setInterval(interval);
	_event->setLuaCallback(luaFunc);
	_event->setCallback(NULL);
	_event->setTarget(NULL);

	setElapsedEvents(elapsedTime, _event);
}

void GameDirector::regGameElapsedEvent(float elapsedTime, int count, float interval, CCObject* target, SEL_CallFuncInt callback)
{	
	auto _event = ElapsedEvent::create();
	_event->setIsLuaEvent(false);
	_event->setCount(count);
	_event->setInterval(interval);
	_event->setLuaCallback(0);
	_event->setCallback(callback);
	_event->setTarget(target);

	setElapsedEvents(elapsedTime, _event);
}


void GameDirector::regGameEvent(const char* eventName, int luaFunc)
{
	//CCNotificationCenter::sharedNotificationCenter()->registerScriptObserver(
	auto tmpLayer = CCLayer::create();
	m_EventTargets->addObject(tmpLayer);
	CCNotificationCenter::sharedNotificationCenter()->registerScriptObserver(tmpLayer, luaFunc, eventName);
}

void GameDirector::regGameEvent(const char* eventName, CCObject* target, SEL_CallFuncO callback)
{
	if (!m_EventTargets->containsObject(target))
	{
		m_EventTargets->addObject(target);
		CCNotificationCenter::sharedNotificationCenter()->addObserver(target, callback, eventName, NULL);
	}
}

void GameDirector::setElapsedEvents(float elapsedTime, ElapsedEvent* _event)
{
	auto key = string(CCString::createWithFormat("%f", elapsedTime)->getCString());
	if (m_ElapsedEvents->objectForKey(key) == NULL)
	{
		CCArray* arr = CCArray::create();
		arr->addObject(_event);
		m_ElapsedEvents->setObject(arr, key);
		m_ElapsedEventsTriggeredFlag->setObject(CCString::createWithFormat("%d", 0), key);
	}
	else
	{
		CCArray* arr = dynamic_cast<CCArray*>(m_ElapsedEvents->objectForKey(key));
		if (arr == NULL)
		{
			CCLog("Unknown error caused m_ElapsedEvents contains non-array element");
		}
		else
		{
			arr->addObject(_event);
		}
	}
}

void GameDirector::update(float dt)
{
	CCObject::update(dt);

	if (m_IsClockTicking)
	{
		m_GameElapsedTime += dt;
		CCDictElement* el = NULL;
		CCDICT_FOREACH(m_ElapsedEvents, el)
		{
			auto key = CCString::create(string(el->getStrKey()))->floatValue();
			bool isTriggered = m_ElapsedEventsTriggeredFlag->valueForKey(key)->boolValue();
			if (m_GameElapsedTime >= key && !isTriggered)
			{
				// got the shoot
				auto events = dynamic_cast<CCArray*>(el->getObject());
				if (events)
				{
					CCObject* obj = NULL;
					CCARRAY_FOREACH(events, obj)
					{
						ElapsedEvent* _event = dynamic_cast<ElapsedEvent*>(obj);
						CC_CONTINUE_IF(!_event);
						if (_event->getInterval() <= 0)
						{
							while (_event->getCount() > 0)
							{
								_event->trigger();	//count-- in this func.
							}
						}
						else
						{
							_event->trigger();
							if (_event->getCount() > 0)
							{
								setElapsedEvents(_event->getInterval() + m_GameElapsedTime, _event->clone());
							}
						}
					}
				}

				m_ElapsedEventsTriggeredFlag->setObject(CCString::createWithFormat("%d", 1), key);
			}
		}
	}
	//CCLog("game director updated - %f", dt);
}