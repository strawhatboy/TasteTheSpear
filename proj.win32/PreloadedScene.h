#pragma once
#include "cocos2d.h"
#include "ProgressEntity.h"
#include "myLib.h"
//#include "IProgressBroadcaster.h"

USING_NS_CC;

class PreloadedScene :
	public CCScene
	//, public IProgressBroadcaster
{
protected:
	ProgressEntity* m_progress;

public:
	PreloadedScene(void);
	~PreloadedScene(void);

	// use CCTextureCache to load images and use preloadEffect to load audios
	virtual bool loadResources(void) = 0;
	virtual bool drawContents(void) = 0;
};

