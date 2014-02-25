#pragma once

#include "cocos-ext.h"
#include "TexturedGameObjectType.h"
#include "GameObject_Runtime.h"


class TexturedGameObject_Runtime
	: public GameObject_Runtime
{
public:
	TexturedGameObject_Runtime(void);
	~TexturedGameObject_Runtime(void);


	RUNTIME_OBJ_CREATE(TexturedGameObject_Runtime, TexturedGameObjectType);
};

