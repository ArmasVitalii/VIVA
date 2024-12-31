#pragma once
#include "PlayerEnum.h"
#include <stdint.h>
class Card
{
private:
	uint8_t		m_cardValue;
	PlayerEnum	m_playerID;

public:
	Card(uint8_t value, PlayerEnum playerID);
	bool operator==(const Card& card) const;

	uint8_t		getValue() const;
	PlayerEnum	getPlayerID() const;
};

