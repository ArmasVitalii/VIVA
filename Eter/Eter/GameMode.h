#pragma once
#include <list>
class GameMode
{
private:
	bool						m_is4x4{ 0 };
	std::list<uint8_t>			m_cardList{};
	uint8_t						m_maxNumberOfGames{ 0 };
	bool						m_hasMage{ 0 };
	bool						m_hasMagic{ 0 };
	bool						m_hasExplosions{ 0 };
	bool						m_hasIlusions{ 0 };
	bool						m_hasTimer{ 0 };

public:
	
};

