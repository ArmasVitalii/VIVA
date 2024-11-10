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
		int choice_v, choice_i, choice_j;

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

		//WIN CASE 2
		if (m_numberOfCardsAdded == 9)
		{
			std::cout << "Game Won by PLAYER " << !currentPlayer + 1 << "! THE LAST SQUARE WAS FILLED\n";
			break;
		}

		std::cout << "\nCurrently Playing As PLAYER " << currentPlayer + 1;
		m_players[currentPlayer].printPlayableCards();


		std::cout << "Enter (x,y) value: ";
		std::cin >> choice_i >> choice_j >> choice_v; // READ POSITION AND VALUE

		if (!m_players[currentPlayer].removeCard({ choice_v,currentPlayer }))
		{
			std::cout << "Value not available.\n";
			continue;
		}

		//WIN CASE 3
		if (m_players[currentPlayer].getCards().empty())
		{
			std::cout << "\nGame Won by PLAYER " << !currentPlayer + 1 << "! Reasone: No more cards!";
			break;
		}


		if (validPositions.find({ choice_i, choice_j }) != validPositions.end())
		{
			// VALIDATE STACK RULE
			if (choice_v <= m_gameBoard[choice_i][choice_j].top().getValue())
			{
				std::cout << "Incorrect value for stacking!\n";
				m_players[currentPlayer].getCards().push_back(choice_v);
				continue;
			}
			m_numberOfCardsAdded++;

			if (lockCase < 3)
			{
				if (lockCase != 0)
				{
					switch (lockCase)//TODO: DELETE OPTIONS FROM VALIDATION LIST
					{
					case 2:
						if (choice_i < m_gridMiddle.first - 1 || choice_i > m_gridMiddle.first + 1)
						{// ENSURE VALID COLUMN
							m_numberOfCardsAdded--;
							std::cout << "Invalid position! Not in a valid COLUMN\n";
							m_players[currentPlayer].getCards().push_back(choice_v);
							continue;
						}
						break;//BREAK SWITCH
					case 1:
						if (choice_j < m_gridMiddle.second - 1 || choice_j > m_gridMiddle.second + 1)
						{ //ENSURE VALID ROW
							m_numberOfCardsAdded--;
							std::cout << "Invalid position! Not in a valid ROW\n";
							m_players[currentPlayer].getCards().push_back(choice_v);
							continue;
						}
						break;
					}

					//VERIFY IF I CAN MOVE THE GRID
					m_gridMiddle.first += (choice_i - m_gridMiddle.first) / 2; // NEW GRID CENTER X
					m_gridMiddle.second += (choice_j - m_gridMiddle.second) / 2; // NEW GRID CENTER Y
					if (!validatePositionInGrid())
					{
						m_gridMiddle.first -= (choice_i - m_gridMiddle.first) / 2;
						m_gridMiddle.second -= (choice_j - m_gridMiddle.second) / 2;
						m_players[currentPlayer].getCards().push_back(choice_v);
						m_numberOfCardsAdded--;
						std::cout << "Invalid insert position => GRID\n";
						continue;
					}
					//END VALIDATION 
				}//std::cout << "\n" << m_gridMiddle.first << " " << m_gridMiddle.second << "\n";//DISPLAY GRID MIDDLE FOR DEBUG
			}




		}


	}  while (true);
}

int Game::verifyLockCase(bool playerNumber)
{
	//TODO: DONT KEEP THE MATRIX SAVED, JUST TRANSFER THE COORDONATES OF THE LAST INSERION INTO THE "POKET" OF THE PLAYER IT PLACED
	//REFER TO M_COLUMNVECTOR AND M_ROWVECTOR
	//DO THE SAME FOR WINCONDITON


	std::vector<std::vector<bool>> g(3, std::vector<bool>(3)); // Will not need this if we normalize coordinates
	int count = 0, options_checked = 0;

	// Populate the real grid
	for (int i = m_gridMiddle.first - 1; i <= m_gridMiddle.first + 1; i++)
	{
		for (int j = m_gridMiddle.second - 1; j <= m_gridMiddle.second + 1; j++)
		{
			if (i >= 0 && i < m_gameBoard.size() && j >= 0 && j < m_gameBoard[i].size() && !m_gameBoard[i][j].empty())
			{
				g[i - (m_gridMiddle.first - 1)][j - (m_gridMiddle.second - 1)] = (m_gameBoard[i][j].top().getValue() != -1) ? 1 : 0;
			}
		}
	}

	std::vector<int> vec_linii(3, 0);
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			vec_linii[j] += (int)g[i][j];
		}
	}

	std::vector<int> vec_coloane(3, 0);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			vec_coloane[i] += (int)g[i][j];
		}
	}

	std::cout << "\nvec linii: ";
	for (const auto& x : vec_linii)std::cout << x << " ";

	std::cout << "vec coloane: ";
	for (const auto& x : vec_coloane)std::cout << x << " ";
	std::cout << "\n";

	int conditions = 0;

	bool control = true;
	for (const auto& x : vec_linii)
	{
		if (x == 0) { control = false; break; }
	}
	if (control) conditions += 1;


	control = true;
	for (const auto& x : vec_coloane)
	{
		if (x == 0) { control = false; break; }
	}
	if (control) conditions += 2;


	for (int i = 0; i < 3; i++)
	{
		if (vec_linii[i] == 0 || vec_coloane[i] == 0)
		{
			control = false; break;
		}
	}

	if (control) conditions += 3;

	return conditions;

}

bool Game::winCondition(bool currentPlayer)
{
	std::vector<std::vector<bool>> g(3, std::vector<bool>(3));
	// -> Will not need this if we normalize coordinates

	int count = 0, options_checked = 0;

	//Populating the real grid
	for (int i = m_gridMiddle.first - 1;i <= m_gridMiddle.first + 1;i++)
	{
		for (int j = m_gridMiddle.second - 1; j <= m_gridMiddle.second + 1; j++)
		{
			if (i >= 0 && i < m_gameBoard.size() && j >= 0 && j < m_gameBoard[i].size() && !m_gameBoard[i][j].empty())
			{
				g[i - (m_gridMiddle.first - 1)][j - (m_gridMiddle.second - 1)] =
					(m_gameBoard[i][j].top().getValue() != -1 && m_gameBoard[i][j].top().getWhoPlayed() == currentPlayer) ? 1 : 0;
			}
		}
	}





	return false;
}

