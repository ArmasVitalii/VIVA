#pragma once
#include <list>
class Gamemode
{
private:
	bool						m_is4x4{ false };
	std::list<uint8_t>			m_cardList{};
	uint8_t						m_maxNumberOfGames{ 0 };
	bool						m_hasMage{ false }; /*MAYBE CHANGE WITH ARRAY?*/
	bool						m_hasMagic{ false };
	bool						m_hasExplosions{ false };
	bool						m_hasIlusions{ false };
	bool						m_hasTimer{ false };

public:
	bool						getIs4x4()				const;
	const std::list<uint8_t>&	getCardList()			const;
	uint8_t						getMaxNumberOfGames()	const;
	bool						gethasMage()			const;
	bool						gethasMagical()			const;
	bool						gethasExplosions()		const;
	bool						gethasIlusions()		const;
	bool						gethasTimer()			const;

	Gamemode() = default;
	Gamemode(bool			is4x4,
		std::list<uint8_t>	cardList,
		uint8_t				maxNumberOfGames,
		bool				hasMage,
		bool				hasMagic,
		bool				hasExplosions,
		bool				hasIlusions,
		bool				hasTimer);
};

