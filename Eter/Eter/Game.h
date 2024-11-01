#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_set>
#include "Card.h"
#include <Player.h>

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
	bool					m_is4x4 = 0;
	int						m_gamePlay;
	int						m_NumberOfGames;

	gameboard				m_gameBoard{ 5, std::vector<std::stack<Card>>{ 5, std::stack<Card>({Card(-1, 0)})} };
	std::vector<Player>		m_players{ {0/*PLayer 1*/}, {1 /*Player 2*/} }; //Maybe would be better to make it array?
	std::pair<int, int>		m_gridMiddle{ 2, 2 };
	int						m_numberOfCardsAdded;

private:

	gameboard&				getGameBoard();
	const Player&			getPlayer1() const;
	const PLayer&			getPlayer2() const;
	std::pair<int, int>		getGridMiddle();
	void					printGameboard();
	bool					validatePositionInGrid() const;		//Verify if the gridmiddle is in the grid and if all inserted elements are inside the grid
	bool					winCondition(bool currentPlayer);	//Returns a bool wich decides who won the game
	int						verifyLockCase(bool player);		//Verify if we are in a lock case

public:
	void					start();
};