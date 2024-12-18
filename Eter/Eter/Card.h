#pragma once
class Card
{
private:
	//TOBE: CONTINUED
	int					m_value;
	bool				m_whoPlayed;
public:
	Card(int value, bool whoPlayer);
	Card(int value);
	//Card(type, value, whoPlayed); -> maybe enums for values and type of cards?
	bool				operator==(const Card& other) const;
	const int&			getValue() const;
	const bool&			getWhoPlayed() const;
};
