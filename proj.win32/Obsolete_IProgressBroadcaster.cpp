//#include "IProgressBroadcaster.h"
//
//
//IProgressBroadcaster::IProgressBroadcaster(void)
//{
//}
//
//
//IProgressBroadcaster::~IProgressBroadcaster(void)
//{
//}
//
//
//void IProgressBroadcaster::Notify()
//{
//	auto thisPointer = this;
//	for_each(this->listeners->begin(),
//		this->listeners->end(),
//		[&thisPointer](IListener* listener){
//			((IProgressListener*)listener)->Handle(thisPointer);
//	});
//}
//
//
//	void IProgressBroadcaster::setMaxValue(int value)
//	{
//		this->m_maxValue = value;
//	}
//	void IProgressBroadcaster::setMinValue(int value)
//	{
//		this->m_minValue = value;
//	}
//	void IProgressBroadcaster::setCurrentValue(int value)
//	{
//		if (this->m_currentValue != value)
//		{
//			this->m_currentValue = value;
//			this->Notify();
//		}
//	}
//	double IProgressBroadcaster::getFinishPercentage() const
//	{
//		return (double)this->m_currentValue / (double)(this->m_maxValue - this->m_minValue);
//	}
//
//	int IProgressBroadcaster::getMaxValue() const
//	{
//		return this->m_maxValue;
//	}
//
//	int IProgressBroadcaster::getMinValue() const
//	{
//		return this->m_minValue;
//	}
//
//	int IProgressBroadcaster::getCurrentValue() const
//	{
//		return this->m_currentValue;
//	}