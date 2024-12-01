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
	bool						getIs4x4()				const;
	const std::list<uint8_t>&	getCardList()			const;
	uint8_t						getMaxNumberOfGames()	const;
	bool						gethasMage()			const;
	bool						gethasMagical()			const;
	bool						gethasExplosions()		const;
	bool						gethasIlusions()		const;
	bool						gethasTimer()			const;

	GameMode() = default;
	GameMode(bool			is4x4,
		std::list<uint8_t>	cardList,
		uint8_t				maxNumberOfGames,
		bool				hasMage,
		bool				hasMagic,
		bool				hasExplosions,
		bool				hasIlusions,
		bool				hasTimer);
};

