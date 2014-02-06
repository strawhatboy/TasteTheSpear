#include "PreloadedScene.h"


PreloadedScene::PreloadedScene(void)
{
	INIT_POINTER(this->m_progress);
	this->m_progress = new ProgressEntity();
}


PreloadedScene::~PreloadedScene(void)
{
	CC_SAFE_DELETE(this->m_progress);
}
