#include "Mage.h"

const std::string& Mage::getName() const
{
	return m_name;
}

void Mage::MarkUsedPower(int powerNumber)
{
	if (powerNumber == 1)
		power1Used = true;
	else if (powerNumber == 2)
		power2Used = true;
}

bool Mage::UsedPower(int powerNumber)
{
	if (powerNumber == 1)
		return power1Used;
	if (power2Used == 2)
		return power2Used;

	return false;
}
