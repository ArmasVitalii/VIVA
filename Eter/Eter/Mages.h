#pragma once
#include "Mage.h"
#include "Game.h"

class FireMasters : public Mage //Mage 1: MASTERS OF FIRE
{
public:
	FireMasters() { m_name = "Fire Masters"; }
	void activate(Game& game) override
	{
		if (!power1Used)
		{
			//First power: remove opponent's card
			usePower1(game);
		}
		else if (!power2Used)
		{
			//Second power: remove one row
			usePower2(game);
		}
		
	}
private:
	void usePower1(Game& game)
	{
		std::cout << "Removing opponent's card \n";
		bool cardRemoved = false;
		int row, col;
		std::cout << "Introduce the row and column for removing a card: "; 
		std::cin >> row >> col;
		game.removeOpponentCard(row, col);

		MarkUsedPower(1);
	
	}
	void usePower2(Game& game)
	{
		std::cout << "Removing a row of cards.\n";
		int row;
		
		std::cout << "Enter the row to remove: ";
		std::cin >> row;

		if (!isValidRow(game, row)) 
		{
			std::cout << "Invalid row. Row must have at least 3 cards and contain your own card.\n";
			return;
		}

		game.removeRow(row);
		MarkUsedPower(2);
	}
	bool isValidRow(Game& game, int row)
	{
		int cards = 0;
		bool hasOwnCard = false;
		for (int col=0; col < game.getGameboard()[row].size(); col++)
		{
			if (!game.getGameboard()[row][col].empty())
			{
				cards++;
				if (isOwnCard(game, row, col))
				{
					hasOwnCard = true;
				}
			}
		}
		return cards >= 3 && hasOwnCard;
	}
	bool isOwnCard(Game& game, int row, int col)
	{
		std::stack<Card>& cardStack = game.getGameboard()[row][col];
		if (!cardStack.empty())
		{
			Card topCard = cardStack.top();
			//Add an function to get the current player's index
			//return topCard.getWhoPlayed() = game.getCurrentPlayer;
			if (topCard.getWhoPlayed() == game.getCurrentPlayer())
			{
				return true;
			}
		}
		return false;
	}
};

//TO BE CONTINUED: EARTH MASTERS; AIR MASTERS; WATER MASTERS

class EarthMasters : public Mage
{
public:
	EarthMasters() { m_name = "Earth Masters"; }
	void activate(Game& game) override
	{
		if (!power1Used)
		{
			//First power: cover opponent's card
			usePower1(game);
		}
		else if (!power2Used)
		{
			//Second power: create pit
			usePower2(game);
		}
	}
private:
	void usePower1(Game& game)
	{
		std::cout << "Covering opponent's card with a lower card.\n";
		int row, col;
		std::cout << "Enter the row and column of the opponent's card: ";
		std::cin >> row >> col;

		if (!game.getGameboard()[row][col].empty())
		{
			std::cout << "No card at this position.\n";
			return;
		}

		Card opponentCard = game.getGameboard()[row][col].top();
		if (opponentCard.getWhoPlayed() == game.getCurrentPlayer())
		{
			std::cout << "This is your card, not an opponent's.\n";
			return;
		}

		int newCardValue;
		std::cout << "Enter a card value from your hand that is lower than the oppnent's card: ";
		std::cin >> newCardValue;

		if (newCardValue >= opponentCard.getValue())
		{
			std::cout << "Card value must be strictly lower than the oppenent's card.\n";
			return;
		}
		game.getGameboard()[row][col].push(Card(newCardValue, game.getCurrentPlayer()));
		MarkUsedPower(1);
	}
	void usePower2(Game& game)
	{
		std::cout << "Creating a pit\n";
		int row, col;
		std::cout << "Enter the row and column where you want to create a pit: ";
		std::cin >> row >> col;

		if (row < 0 || row >= game.getGameboard().size() || col < 0 || col >= game.getGameboard()[row].size())
		{
			std::cout << "Invalid position. Please enter valid coordinates.\n";
			return;
		}

		if (!game.getGameboard()[row][col].empty()) {
			std::cout << "This space is not empty! Please choose an empty space to create a pit.\n";
			return;
		}

		game.getGameboard()[row][col].push(Card(-1, false)); 
		std::cout << "A pit has been created at (" << row << ", " << col << ").\n";

		MarkUsedPower(2);
	}
};

class AirMasters : public Mage
{
public:
	AirMasters() { m_name = "Air Masters"; }
	void activate(Game& game) override
	{
		if (!power1Used)
		{
			//First power: move stack of cards
			usePower1(game);
		}
		else if (!power2Used)
		{
			//Second power: get an eter card
			usePower2(game);
		}
	}
private:
	void usePower1(Game& game)
	{
		std::cout << "Move your stack to another position\n";
		int row, col;
		std::cout << "Enter the row and column where you want to move your stack: ";
		std::cin >> row >> col;

		if (row < 0 || row >= game.getGameboard().size() || col < 0 || col >= game.getGameboard()[row].size())
		{
			std::cout << "Invalid position. Please enter valid coordinates.\n";
			return;
		}

		if (!game.getGameboard()[row][col].empty())
		{
			std::cout << "This position is not empty. Please choose an empty space.\n";
			return;
		}

		for (int i = 0; i < game.getGameboard().size(); i++)
		{
			for (int j = 0; j < game.getGameboard()[i].size(); j++)
			{
				if (!game.getGameboard()[i][j].empty() && game.getGameboard()[i][j].top().getWhoPlayed() == true)
				{
					std::stack<Card>stackToMove = game.getGameboard()[i][j];
					game.getGameboard()[i][j] = std::stack<Card>();

					game.getGameboard()[row][col] = stackToMove;
					std::cout << "Your stack has been moved to position (" << row << ", " << col << ").\n";
					return;
				}
			}
		}
		std::cout << "No stack with your card found on the board.\n";

		MarkUsedPower(1);
	}
	void usePower2(Game& game)
	{
		std::cout << "You can place an ETER card \n";
		int row, col;
		std::cout << "Enter the position where to place it: ";
		std::cin >> row >> col;

		if (row < 0 || row >= game.getGameboard().size() || col < 0 || col >= game.getGameboard()[row].size())
		{
			std::cout << "Invalid position! \n";
			return;
		}

		if (!game.getGameboard()[row][col].empty())
		{
			std::cout << "This position is occupied! You cannot place an ETER card. \n";
			return;
		}

		Card ETERcard(1, false);
		game.getGameboard()[row][col] = ETERcard;
		MarkUsedPower(2);
	}
};

class WaterMasters : public Mage
{
public:
	WaterMasters() { m_name = "Water Masters"; }
	void activate(Game& game) override
	{
		if (!power1Used)
		{
			//First power: move opponent's card
			usePower1(game);
		}
		else if (!power2Used)
		{
			//Second power: move a row
			usePower2(game);
		}
	}
private:
	void usePower1(Game& game);
	void usePower2(Game& game);
};
