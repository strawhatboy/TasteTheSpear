#pragma once
#include "ProgressEntity.h"

class IHasProgress
{

public:
	IHasProgress(void);
	~IHasProgress(void);

	virtual void setProgress(ProgressEntity* progress) = 0;
};

