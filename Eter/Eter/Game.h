#pragma once
#include <vector>
#include <unordered_set>
#include <stack>
#include "Card.h"
#include "Player.h"
#include <iostream>
#include <algorithm>
import Game_UI;

using gameboard = std::vector<std::vector<std::stack<Card>>>;
struct pairHash
{
	std::size_t operator()(const std::pair<int, int>& p) const
	{
		std::size_t h1 = std::hash<int>{}(p.first);
		std::size_t h2 = std::hash<int>{}(p.second);
		return h1 ^ (h2 << 1);
	}
};


class Game
{
private:
	bool						m_is4x4 = 0;//TODO: MODIFY THE GAMEBOARD DIMENSION BASED ON 5 + 2* IS4X4
	int							m_gamePlay;
	int							m_NumberOfGames;

	gameboard					m_gameBoard{ 5, std::vector<std::stack<Card>>{5,std::stack<Card>({Card(-1,0)})} };
	std::vector<Player>			m_players{ {0/*Player1*/},{1/*Player2*/} };	//MAYBE ARRAY?
	std::pair<int, int>			m_gridMiddle{ 2,2 };
	int							m_numberOfCardsAdded = 0;
	bool                        currentPlayer;

private:
	//gameboard&					getGameboard();
	const Player&				getPlayer1() const;							//CONST COULD BE A PROBLEM FOR WHEN WE UPDATE THE "POKET"
	const Player&				getPlayer2() const;
	std::pair<int, int>			getGridMiddle();
	void						printGameboard();

	bool						validatePositionInGrid() const;			//VERIFY IF THE GRIDMIDDLE IS IN GRID AND IF ALL INSETED ELEMENTS ARE INSIDE THE GRID
	int							verifyLockCase(bool player);			//VERIFY LOCK CASE
	bool						winCondition(bool currentPlayer);

public:
	void						start(); //WILL RETURN A BOOL DEPICTING WHO WON

	void						removeOpponentCard(int row, int col); //FOR FIREMASTERS (1st power)
	void						removeRow(int row); //FOR FIREMASTERS (2nd power)
	int                         getCurrentPlayer() const;
	gameboard& getGameboard();
};



