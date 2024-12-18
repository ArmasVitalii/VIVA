#pragma once
#include <vector>
#include <iostream>
#include <list>
#include "Card.h"
#include "Game.h"


class Player
{
private:
	bool						m_playerNumber;
	std::list<int>				m_playerCards;				//RETHINK FOR LIST OF CARDS
	std::vector<int>			m_columnVector{ 0,0,0 };
	std::vector<int>			m_rowVector{ 0,0,0 };  //RETHINK/ FIND WAY FOR 4X4, MAYBE SET FUNCTION

public:
	Player(bool playerNumber);		//, const std::list<Card>& playerCards = {});

	std::list<int>&				getCards();
	void						addCard(const Card& card);
	bool						removeCard(const Card& card);//MAYBE WITH NUMBERS, NOT CARDS

	bool& getPlayerNumber();
	std::vector<int>			getColumnVector();
	std::vector<int>			getRowVector();

	
	void						printPlayableCards() const;
	//LIST OF POWERS
	void                        ControlledExplosion();
	void                        Destruction(Player& opponent);
	void                        Flames(Player& opponent, int playedCard);
	void                        Lava(int number);
	void                        FromAshes(int cardValue);
	void                        Sparks(Player& opponent, int cardValue);
	void                        Blizzard(Player& opponent);
	void                        Storm();
	void                        Hurricane(int row);
	void                        Gale(int visibileCard);
	void                        Mirage();
	void                        StormSurge(Game& game);
	void                        Tide(Game& game);
	void                        Fog();
	void                        Wave();
	void                        WaterVortex();
	void                        Tsunami(int row);
	void                        Cascade(int row);
	void                        Support(int cardValue);
	void                        Earthquake();
	void                        Crack(int cardValue);
	void                        Borders();
	void                        Avalanche();
	void                        Boulder();

};

