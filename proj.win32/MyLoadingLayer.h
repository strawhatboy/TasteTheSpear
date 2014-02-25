#pragma once
#include "myLib.h"
#include "loadinglayer.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;

#define LOADING_BAR_FILE_NAME "loadingbar.png"

class MyLoadingLayer :
	public LoadingLayer
{
private:
	bool m_bIsDefaultLoadingImage;
	string m_pszLoadingImagePath;
public:
	virtual bool init(void);
	MyLoadingLayer(void);
	MyLoadingLayer(const char* pszLoadingImagePath);
	~MyLoadingLayer(void);
	virtual void setProgress(ProgressEntity* progress);
	CC_CREATE_FUNC(MyLoadingLayer);
};

