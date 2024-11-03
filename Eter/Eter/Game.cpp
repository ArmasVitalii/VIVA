#include "Game.h"


gameboard& Game::getGameBoard()
{
	return m_gameBoard;
}

const Player& Game::getPlayer1() const
{
	return m_players[0];
}

const Player& Game::getPlayer2() const
{
	return m_players[1];
}

void Game::start()
{
	//ADD THIS AS PARAMETER { 1,1,2,2,3,3,4 }
	m_players[0].getCards() = { 1,1,2,2,3,3,4 };
	m_players[1].getCards() = { 1,1,2,2,3,3,4 };


	std::unordered_set < std::pair<int, int>, pairHash> validPositions;
	std::vector<std::pair<int, int>> valid = { {1,0},{0,1},{1,1},{0,0},{-1,0},{0,-1},{-1,-1},{1,-1},{-1,1} };
	for (const auto& x : valid)
	{
		validPositions.insert(std::make_pair(m_gridMiddle.first + x.first, m_gridMiddle.second + x.second));
	}


	bool firstMove = true, forInsert = true, currentPlayer = 0;
	int lockCase = -1;
}