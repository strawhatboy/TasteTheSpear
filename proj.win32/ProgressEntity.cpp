#include "ProgressEntity.h"


ProgressEntity::ProgressEntity(void)
{
	this->setMaxValue(1);
	this->setMinValue(0);
	this->setCurrentValue(0);
}


ProgressEntity::~ProgressEntity(void)
{
}

	void ProgressEntity::setMaxValue(int value)
	{
		if (this->m_maxValue != value)
		{
			this->m_maxValue = value;
		}
	}
	void ProgressEntity::setMinValue(int value)
	{
		if (this->m_minValue != value)
		{
			this->m_minValue = value;
		}
	}
	void ProgressEntity::setCurrentValue(int value)
	{
		if (this->m_currentValue != value)
		{
			this->m_currentValue = value;
		}
	}
	float ProgressEntity::getFinishPercentage() const
	{
		return (float)this->m_currentValue / (float)(this->m_maxValue - this->m_minValue);
	}

	int ProgressEntity::getMaxValue() const
	{
		return this->m_maxValue;
	}

	int ProgressEntity::getMinValue() const
	{
		return this->m_minValue;
	}

	int ProgressEntity::getCurrentValue() const
	{
		return this->m_currentValue;
	}