#pragma once
#include <vector>
#include <iostream>
#include <list>
#include "Card.h"


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


};

