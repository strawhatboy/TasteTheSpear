//#include "IHasProgress.h"
//
//
//IHasProgress::IHasProgress(void)
//{
//	INIT_POINTER(this->m_fp_BroadcastProgress);
//}
//
//
//IHasProgress::~IHasProgress(void)
//{
//}
//
//	void IHasProgress::setMaxValue(int value)
//	{
//		this->m_maxValue = value;
//	}
//	void IHasProgress::setMinValue(int value)
//	{
//		this->m_minValue = value;
//	}
//	void IHasProgress::setCurrentValue(int value)
//	{
//		if (this->m_currentValue != value)
//		{
//			this->m_currentValue = value;
//			this->onProgressBroadcasted(this->getMinValue(),
//				this->getMaxValue(),
//				this->getCurrentValue());
//		}
//	}
//	double IHasProgress::getFinishPercentage() const
//	{
//		return (double)this->m_currentValue / (double)(this->m_maxValue - this->m_minValue);
//	}
//
//	int IHasProgress::getMaxValue() const
//	{
//		return this->m_maxValue;
//	}
//
//	int IHasProgress::getMinValue() const
//	{
//		return this->m_minValue;
//	}
//
//	int IHasProgress::getCurrentValue() const
//	{
//		return this->m_currentValue;
//	}
//	
//void IHasProgress::onProgressBroadcasted(int minValue, int maxValue, int currentValue)
//{
//	if (this->m_fp_BroadcastProgress)
//		(this->*m_fp_BroadcastProgress)(minValue, maxValue, currentValue);
//}
//
//void IHasProgress::addListener(SEL_BroadcastProgress listener)
//{
//	this->m_fp_BroadcastProgress = listener;
//}
//
//void IHasProgress::removeListener()
//{
//	this->m_fp_BroadcastProgress = NULL;
//}