#include "Game.h"


gameboard& Game::getGameboard()
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
	Game_UI* game = new Game_UI();
	game->HandleEvents();
	game->Update();
	game->Render();
	/*
	while (game is running)
	{
		handle any user input
		update all object eg. position etc
		render changes to the display
	}
	*/


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

			firstMove = false;

			//TOBE OBSEVED
			lockCase = verifyLockCase(currentPlayer);

			printGameboard();
			std::cout << '\n';

			//TOBE OBSEVED
			for (const auto& x : validPositions)
			{
				printf("(%d,%d), ", x.first, x.second);
			}
			std::cout << "\n";

			currentPlayer = !currentPlayer;
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
			// IF IT IS NULL
			if (m_gameBoard[choice_i][choice_j].top().getValue() == -1)
			{
				m_gameBoard[choice_i][choice_j].pop();
			}
			else m_numberOfCardsAdded--;

			m_gameBoard[choice_i][choice_j].push(Card(choice_v, currentPlayer));

			if (forInsert && winCondition(currentPlayer))
			{
				std::cout << "\nGame Won by PLAYER " << currentPlayer + 1 << "\n";
				printGameboard();
				break;
			}

			printGameboard();

			if (forInsert)
			{
				if (choice_i - 1 >= 0) validPositions.insert({ choice_i - 1, choice_j });
				if (choice_i + 1 <= 5) validPositions.insert({ choice_i + 1, choice_j });
				if (choice_j - 1 >= 0) validPositions.insert({ choice_i, choice_j - 1 });
				if (choice_j + 1 <= 5) validPositions.insert({ choice_i, choice_j + 1 });
				if (choice_i - 1 >= 0 && choice_j - 1 >= 0) validPositions.insert({ choice_i - 1, choice_j - 1 });
				if (choice_i + 1 <= 5 && choice_j + 1 <= 5) validPositions.insert({ choice_i + 1, choice_j + 1 });
				if (choice_i - 1 >= 0 && choice_j + 1 <= 5) validPositions.insert({ choice_i - 1, choice_j + 1 });
				if (choice_i + 1 <= 5 && choice_j - 1 >= 0) validPositions.insert({ choice_i + 1, choice_j - 1 });
			}

			lockCase = verifyLockCase(currentPlayer);
			if (lockCase >= 3 && forInsert)
			{
				std::cout << "THE GAME BOARD HAS BEEN SET!\n";
				validPositions.clear();
				forInsert = false;
				for (int i = m_gridMiddle.first - 1; i <= m_gridMiddle.first + 1; i++)
				{
					for (int j = m_gridMiddle.second - 1; j <= m_gridMiddle.second + 1; j++) {
						validPositions.insert({ i,j });
					}
				}
			}

			if (!forInsert && winCondition(currentPlayer))
			{
				std::cout << "\n Game Won by PLAYER " << currentPlayer + 1 << "\n";
				break;
			}

			std::cout << "\n";
			for (const auto& x : validPositions)
			{
				printf("(%d, %d), ", x.first, x.second);
			}
			std::cout << "\n";

			currentPlayer = !currentPlayer;

			game->HandleEvents();
			game->Update();
			game->Render();
		}
		else
		{
			std::cout << "Invalid position!\n";
			m_players[currentPlayer].getCards().push_back(choice_v);
			game->HandleEvents();
			game->Update();
			game->Render();
		}
	}  while (game->Running());

	game->Clean();
}

void Game::removeOpponentCard(int row, int col)
{
	if (!m_gameBoard[row][col].empty())
	{
		m_gameBoard[row][col].pop();
		std::cout << "Card removed on the position: " << row << " " << col << "\n";
	}
}

void Game::removeRow(int row)
{
	for (int col = 0;col < m_gameBoard[row].size();col++)
	{
		while (!m_gameBoard[row][col].empty())
		{
			m_gameBoard[row][col].pop();
		}
	}
	std::cout << "Row " << row << " removed. \n";
}

int Game::getCurrentPlayer() const
{
	return currentPlayer;
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

	std::vector<int> vec_rows(3, 0);
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			vec_rows[j] += (int)g[i][j];
		}
	}

	std::vector<int> vec_cols(3, 0);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			vec_cols[i] += (int)g[i][j];
		}
	}

	std::cout << "\nvec linii: ";
	for (const auto& x : vec_rows)std::cout << x << " ";

	std::cout << "vec coloane: ";
	for (const auto& x : vec_cols)std::cout << x << " ";
	std::cout << "\n";

	int conditions = 0;
	bool allRowsFilled = std::all_of(vec_rows.begin(), vec_rows.end(), [](int x) { return x > 0; });
	bool allColsFilled = std::all_of(vec_cols.begin(), vec_cols.end(), [](int x) { return x > 0; });

	if (allRowsFilled) conditions += 1;
	if (allColsFilled) conditions += 2;
	if (allRowsFilled && allColsFilled) conditions += 3;

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

	std::vector<int> vec_rows(3, 0);
	for (int j = 0;j < 3;j++)
	{
		for (int i = 0; i < 3; i++)
		{
			vec_rows[j] += (int)g[i][j];
		}
	}

	std::vector<int> vec_cols(3, 0);
	for (int i = 0;i < 3;i++)
	{
		for (int j = 0; j < 3; j++)
		{
			vec_cols[i] += (int)g[i][j];
		}
	}
	
	int sum = 0;
	for (const auto& x : vec_rows) sum += x;
	if (sum < 3) return false;

	//NOT A FINAL SOLUTION - JUST FOR TEST PURPOSES ONLY
	std::sort(vec_rows.begin(), vec_rows.end());
	std::sort(vec_cols.begin(), vec_cols.end());

	//NOT A FINAL SOLUTION - JUST FOR TEST PURPOSES ONLY
	if (vec_rows[0] == 0 && vec_cols[0] == 0) return false;

	bool condition1 = true;
	for (int i = 0; i < 3; i++)
	{
		if (vec_rows[i] != vec_cols[i])
		{
			condition1 = false;
			break;
		}
	}

	if (condition1) return true;


	bool lineWin = false;
	bool columnWin = false;


	for (int i = 0; i < 3; i++)
	{
		if (vec_rows[i] > 0 && vec_rows[i] == 3)
		{
			lineWin = true;
			break;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (vec_cols[i] > 0 && vec_cols[i] == 3)
		{
			columnWin = true;
			break;
		}
	}

	if (lineWin || columnWin) return true;

	return false;
}

