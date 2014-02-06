#include "Fighter.h"


Fighter::Fighter(void)
{
}


Fighter::~Fighter(void)
{
}

bool Fighter::init(void)
{
	return this->initWithFile("fighter.png", CCRect(0.f, 0.f, 111.f, 111.f));
}