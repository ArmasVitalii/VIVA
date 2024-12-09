#include "Player.h"

Player::Player(bool playerNumber /*,const std::list<Card>& playerCards*/) : m_playerNumber{ playerNumber }
{
}

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

void Player::ControlledExplosion()
{
	//need for EPLOSION CARD
	std::cout << "Controlled Explosion activated!" << std::endl;
}

void Player::Destruction(Player& opponent)
{
	std::list<int>& opponentCards = opponent.getCards();
	int lastCardValue = opponentCards.back();
	opponentCards.pop_back();
	std::cout << "Distroyed opponent's last card :" << lastCardValue << "\n";
}

void Player::Flames(Player& opponent, int playedCard)
{
	std::cout << "The opponent's illusionhas been flipped!" << std::endl;
	//need for ILLUSIONS
	//addCard(playedCard);
}

void Player::Lava(int number)
{
	//...
	std::cout << "Lava activated! Cards with the number " << number << " are returned to their owners!" << std::endl;
	//return all cards with the specified number to the respective players
	for (auto it = m_playerCards.begin(); it != m_playerCards.end();)
	{
		if (*it == number)
		{
			it = m_playerCards.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Player::FromAshes(int cardValue)
{
	//...
}


