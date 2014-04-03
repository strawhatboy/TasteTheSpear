#include "TexturedGameObject_Runtime.h"
#include "GameObjectTypesLoader.h"

TexturedGameObject_Runtime::TexturedGameObject_Runtime(void)
{
	INIT_POINTER(m_Armature);
	INIT_POINTER(m_Sprite);
	INIT_POINTER(m_TexturedObjectType);
}


TexturedGameObject_Runtime::~TexturedGameObject_Runtime(void)
{
	CC_SAFE_RELEASE(m_Armature);
	CC_SAFE_RELEASE(m_Sprite);
}

bool TexturedGameObject_Runtime::initWithGameObjectType(GameObjectType* type)
{
	if (!GameObject_Runtime::initWithGameObjectType(type))
		return false;

	INIT_START

	m_TexturedObjectType = dynamic_cast<TexturedGameObjectType*>(type);
	CC_BREAK_IF(!m_TexturedObjectType);

	auto loader = GameObjectTypesLoader::sharedInstance();
	auto id = m_TexturedObjectType->getTypeID();
	if (m_TexturedObjectType->getIsArmature())
	{
		m_Armature = loader->createArmatureByID(id.c_str());
		m_Armature->retain();
	}
	else
	{
		m_Sprite = loader->createSpriteByID(id.c_str());
		m_Sprite->retain();
	}

	INIT_TRUE
	INIT_END
}

void TexturedGameObject_Runtime::playAnimation(const char* animationName,
	int durationTo, int durationTween, int loop, int tweenEasing)
{
	if (m_TexturedObjectType)
	{
		if (m_TexturedObjectType->getIsArmature())
		{
			m_Armature ? m_Armature->getAnimation()->play(animationName,
				durationTo, durationTween, loop, tweenEasing) : 0;
		}
		else
		{
			CCLog("This textured game object '%s' is not armature-based, no animation to play.",
				m_TexturedObjectType->getTypeID().c_str());
		}
	}
}
void TexturedGameObject_Runtime::playAnimation(int index, int durationTo, int durationTween, int loop, int tweenEasing)
{
	if (m_TexturedObjectType)
	{
		if (m_TexturedObjectType->getIsArmature())
		{
			m_Armature ? m_Armature->getAnimation()->playWithIndex(index, durationTo, durationTween, loop, tweenEasing) : 0;
		}
		else
		{
			CCLog("This textured game object '%s' is not armature-based, no animation to play.",
				m_TexturedObjectType->getTypeID().c_str());
		}
	}
}

CCNodeRGBA* TexturedGameObject_Runtime::getTextureNode(void)
{
	if (m_TexturedObjectType)
	{
		if (m_TexturedObjectType->getIsArmature())
		{
			return m_Armature;
		}
		else
		{
			return m_Sprite;
		}
	}

	return NULL;
}
//
//CCArmature* TexturedGameObject_Runtime::getArmature(void)
//{
//	if (this->m_GameObjectType != NULL)
//	{	
//		auto texturedObjectType = dynamic_cast<TexturedGameObjectType*>(this->m_GameObjectType);
//		if (texturedObjectType != NULL)
//		{
//			CCArmatureDataManager::sharedArmatureDataManager()->ad
//			CCArmature* armature = CCArmature::create(
//		}
//	}
//
//	return NULL;
//}