#pragma once
#include "Game.h"
#include <string>

class Mage
{
public:
	virtual ~Mage() = default;
	virtual void Activate(Game& game) = 0;
	const std::string& getName() const;

protected:
	std::string m_name;
	bool powerUsed = false;

	void MarkUsedPower();
	bool IsUsedPower();
};