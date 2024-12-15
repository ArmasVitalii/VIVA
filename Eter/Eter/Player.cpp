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
	//need for EXPLOSION CARD
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
	//return all cards with the specified number to the respective players
	int countCards = std::count(m_playerCards.begin(), m_playerCards.end(), number);

	if (countCards >= 2)
	{
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
		std::cout << "Lava activated! Cards with the number " << number << " are returned to their owners!" << std::endl;

	}
	else
		std::cout << "Cannot use Lava Power! Not enough cards with the chosen number: " << number;
	
}

void Player::FromAshes(int cardValue)
{
	//...
	//addCard(Card(cardValue));  //need a constructor for Card
	std::cout << "Card " << cardValue << " has been played from the ashes!" << std::endl;
}

void Player::Sparks(Player& opponent, int cardValue)
{
	std::cout << "The opponent's covered card has been moved to another position!" << std::endl;
	//opponent.removeCard(Card(cardValue)); //need a constructor for Card
	//addCard(Card(cardValue)); // need a constructor for Card
}

void Player::Blizzard(Player& opponent)
{
	//move the last visibile card from the opponent to their hand
	if (!opponent.m_playerCards.empty())
	{
		int cardValue = opponent.m_playerCards.back();
		opponent.m_playerCards.pop_back();
		//addCard(Card(cardValue)); //need a constructor for Card
		std::cout << " A card has been returned to the opponent's hand!" << std::endl;
	}
}

void Player::Storm()
{
	//return all covered cards on the board to the players' hands
	for (auto& value : m_playerCards)
	{
		//logic for returning covered cards to the player
		std::cout << "Card returned to the player's hand!" << std::endl;
	}
}

void Player::Hurricane(int row)
{
	std::cout << "Hurricane has shifted row " << row << "!" << std::endl;

	//logic for shifting a complete row on the board 
}

void Player::Gale(int visibileCard)
{
	
	std::cout << "Card" << visibileCard << " has been moved to an adjacent position!" << std::endl;
	//move the card to an adjacent position with a smaller value
}

void Player::Mirage()
{
	//logic to replace the illusion
}

void Player::StormSurge(Game& game) 
{
	//eliminate any stack of cards that has 2/more cards
	int row, col;
	std::cout << "Choose stack to eliminate (row and col): ";
	std::cin >> row >> col;

	if (row < 0 || row >= game.getGameboard().size() || col < 0 || col >= game.getGameboard()[row].size())
	{
		std::cout << "Invalid position of stack";
		return;
	}

	if (game.getGameboard()[row][col].size() >= 2)
	{
		game.getGameboard()[row][col].pop();
		std::cout << "Storm power activated. Stack at the positions: (" << row << ", " << col << ") was eliminated\n";
	}
	else
		std::cout << "The stack must have at least 2 cards!";
}

void Player::Tide(Game &game)
{
	auto Gameboard = game.getGameboard();
	int row1, col1;
	int row2, col2;
	std::cout << "The coordinates of the first stack of cards (row, col): ";
	std::cin >> row1 >> col1;

	std::cout << "The coordinates of the second stack of cards which you want to swap: ";
	std::cin >> row2 >> col2;

	if (row1 < 0 || row1 >= Gameboard.size() || col1 < 0 || row1 >= Gameboard[row1].size() ||
		row2 < 0 || row2 >= Gameboard.size() || col2 < 0 || col2 >= Gameboard[row2].size())
	{
		std::cout << "Invalid coordinates! You cannot swap stacks.";
		return;
	}

	std::swap(Gameboard[row1][col1], Gameboard[row2][col2]);
	std::cout << "Tide power activated!";

}

void Player::Fog()
{
	//need for illusions!
}

void Player::WaterVortex()
{
	//...
}


