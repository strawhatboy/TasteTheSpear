#include "GameDirector.h"

CC_SHARED_CREATE_IMPL(GameDirector);

GameDirector::GameDirector(void)
{
}


GameDirector::~GameDirector(void)
{
}

string GameDirector::getUIStringByID(int nID)
{
	return GameObjectTypesLoader::sharedInstance()->getStringResourceTypeByID("S002")->getStringByKey(nID);
}

void GameDirector::changeState(uint state, CCDictionary* dictParams)
{
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
		// pause the running game.
		break;
	case GAME_OVER:
		// show game over layer.
		break;
	default:
		// error
		break;
	}
}