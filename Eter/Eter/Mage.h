#pragma once
#include "Game.h"
#include <string>

class Mage
{
public:
	virtual ~Mage() = default;
	virtual void activate(Game& game) = 0;
	const std::string& getName() const { return m_name; }
	
protected:
	std::string m_name;
	bool power1Used = false;
	bool power2Used = false;

	void MarkUsedPower(int powerNumber)
	{
		if (powerNumber == 1)
			power1Used = true;
		else if(powerNumber==2)
			power2Used = true;
	}

	bool UsedPower(int powerNumber)
	{
		if (powerNumber == 1)
			return power1Used;
		if (power2Used == 2)
			return power2Used;

		return false;
	}
};