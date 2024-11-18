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
		
		//not complete!

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
	void usePower1(Game& game);
	void usePower2(Game& game);
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
	void usePower1(Game& game);
	void usePower2(Game& game);
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