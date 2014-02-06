#include "GameObject_Runtime.h"


GameObject_Runtime::GameObject_Runtime(void)
{
}


GameObject_Runtime::~GameObject_Runtime(void)
{
}


bool GameObject_Runtime::initWithGameObjectType(GameObjectType* type)
{
	if (!type)
	{
		CCLOGERROR("Type cannot be null when initialize a GameObject");
	}

	this->m_GameObjectType = type;

	return true;
}