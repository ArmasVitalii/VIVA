#include "Mage.h"

const std::string& Mage::getName() const
{
	return m_name;
}

void Mage::MarkUsedPower()
{
	 powerUsed = true;
}

bool Mage::IsUsedPower()
{
	 return powerUsed; 
}
