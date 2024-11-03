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

bool Game::validatePositionInGrid() const
{
	int counter = 0;
	bool containsGridMiddle = false;
	for (int i = m_gridMiddle.first - 1; i <= m_gridMiddle.first + 1; i++)
	{
		for (int j = m_gridMiddle.second - 1; j <= m_gridMiddle.second + 1; j++)
		{
			if (i >= 0 && i < m_gameBoard.size() && j >= 0 && j < m_gameBoard[i].size())
			{
				if (m_gameBoard[i][j].top().getValue() != -1)
					counter++;
				if (i == m_gridMiddle.first && j == m_gridMiddle.second)
					containsGridMiddle = true;
			}
		}
	}

	return containsGridMiddle && counter == m_numberOfCardsAdded - 1;
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


	do
	{
		if (firstMove)//LOGIC FOR THE FIRST MOVE
		{
			std::cout << "Currently Playing As PLAYER " << currentPlayer + 1;
			m_players[currentPlayer].printPlayableCards();
			std::cout << "Enter 1st choice: ";
			std::cin >> choice_v;

			if (!m_players[currentPlayer].removeCard({ choice_v,currentPlayer }))
			{
				std::cout << "Value not available.\n";
				continue;
			}

			//DELETE THIS AFTER GUI
			if (choice_v <= 0 || choice_v > 5)
			{
				std::cout << "Value too high!\n";
				continue;
			}

			//MAYBE MAKE THIS INTO A FUNCTION?
			m_gameBoard[m_gridMiddle.first][m_gridMiddle.second].pop();
			m_gameBoard[m_gridMiddle.first][m_gridMiddle.second].push({ choice_v,currentPlayer });
			m_numberOfCardsAdded++;
		}


	} while (true);


}

