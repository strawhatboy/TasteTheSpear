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