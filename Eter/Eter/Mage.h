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
	bool powerUsed = false;

};