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


		MarkUsedPower(1);
	}
	void usePower2(Game& game)
	{

	}
};

