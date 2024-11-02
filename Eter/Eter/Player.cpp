#include "Player.h"

Player::Player(bool playerNumber /*,const std::list<Card>& playerCards*/) : m_playerNumber(playerNumber)
{}

std::list<int>& Player::getCards()
{
	return m_playerCards;
}

void Player::addCard(const Card& card)
{
	m_playerCards.push_back(card.getValue());
}

bool Player::removeCard(const Card& card)
{
	auto it = std::find(m_playerCards.begin(), m_playerCards.end(), card.getValue());
	if (it != m_playerCards.end())
	{
		m_playerCards.erase(it);
		return true;
	}
	return false;
}

bool& Player::getPlayerNumber()
{
	return m_playerNumber;
}

std::vector<int> Player::getColumnVector()
{
	return m_columnVector;
}

std::vector<int> Player::getRowVector()
{
	return m_rowVector;
}

void Player::printPlayableCards() const
{
	std::cout << "\n Playable values: ";
	for (const auto& x : m_playerCards)
	{
		std::cout << x << " ";
	}
	std::cout << "\n";
}
