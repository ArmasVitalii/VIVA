#include "GameMode.h"

GameMode::GameMode(bool is4x4, std::list<uint8_t> cardList, uint8_t maxNumberOfGames, bool hasMage, bool hasMagic, bool hasExplosions, bool hasIlusions, bool hasTimer)
	:m_is4x4{ is4x4 },
	m_cardList{ cardList },
	m_maxNumberOfGames{ maxNumberOfGames },
	m_hasMage{ hasMage },
	m_hasMagic{ hasMagic },
	m_hasExplosions{ hasExplosions },
	m_hasIlusions{ hasIlusions },
	m_hasTimer{ hasTimer }
{
}

bool GameMode::getIs4x4() const
{
	return m_is4x4;
}

const std::list<uint8_t>& GameMode::getCardList() const
{
	return m_cardList;
}

uint8_t GameMode::getMaxNumberOfGames() const
{
	return m_maxNumberOfGames;
}

bool GameMode::gethasMage() const
{
	return m_hasMage;
}

bool GameMode::gethasMagical() const
{
	return m_hasMagic;
}

bool GameMode::gethasExplosions() const
{
	return m_hasExplosions;
}

bool GameMode::gethasIlusions() const
{
	return m_hasIlusions;
}

bool GameMode::gethasTimer() const
{
	return m_hasTimer;
}
