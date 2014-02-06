//#include "IBroadcaster.h"
//
//
//IBroadcaster::IBroadcaster(void)
//{
//	INIT_POINTER(this->listeners);
//	this->listeners = new vector<IListener*>();
//}
//
//
//IBroadcaster::~IBroadcaster(void)
//{
//	CC_SAFE_DELETE(this->listeners);
//}
//
//void IBroadcaster::AddListener(IListener* listener)
//{
//	auto iter = find(this->listeners->begin(), this->listeners->end(), listener);
//	if (iter == this->listeners->end())
//	{
//		// not found
//		this->listeners->push_back(listener);
//	}
//}
//
//void IBroadcaster::RemoveListener(IListener* listener)
//{
//	auto iter = find(this->listeners->begin(), this->listeners->end(), listener);
//	if (iter == this->listeners->end())
//	{
//		// not found
//	} 
//	else
//	{
//		remove(this->listeners->begin(), this->listeners->end(), listener);
//	}
//}