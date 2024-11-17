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
		std::cout << "Removing a row\n";
		int row;
		
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
		}
		return false;
	}
};

//TO BE CONTINUED: EARTH MASTERS; AIR MASTERS; WATER MASTERS

