#include "Game.h"

void Game::start()
{

}

gameboard& Game::getGameBoard()
{
	return m_gameBoard;
}

const Player& Game::getPlayer1() const
{
	return m_players[1];
}

const Player& Game::getPlayer2() const
{
	return m_players[2];
}

std::pair<int, int> Game::getGridMiddle()
{
	return m_gridMiddle;
}

void Game::printGameboard()
{
	for (int i = 0; i < m_gameBoard.size(); ++i)
	{
		for (int j = 0; j < m_gameBoard.size(); ++j)
		{
			const Card& topCard = m_gameBoard[i][j].top();
			if (m_gameBoard[i][j].top().getValue() == -1)
			{
				std::cout << "( , ) ";
			}
			else
			{
				std::cout << "(" << topCard.getValue() << "," << topCard.getWhoPlayed() + 1 << ") ";
			}
		}
		std::cout << std::endl;
	}
}


