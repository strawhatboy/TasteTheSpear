#include "GameObject_Runtime.h"


GameObject_Runtime::GameObject_Runtime(void)
{
}


GameObject_Runtime::~GameObject_Runtime(void)
{
	this->removeAllChildrenWithCleanup(true);
}


bool GameObject_Runtime::initWithGameObjectType(GameObjectType* type)
{
	if (!type)
	{
		CCLOGERROR("Type cannot be null when initialize a GameObject");
	}

	CC_ASSERT(type);
	this->m_GameObjectType = type;
	this->addChild(this->m_GameObjectType);

	return true;
}