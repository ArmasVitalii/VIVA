#include "Game.h"
#include <numeric>
#include <algorithm>

Game::Game(Bridge& bridge, const Board& board, std::array<Player, 2>& players)
	:m_bridge{ bridge },
	m_board{ board },
	m_players{ players }
{
}

void Game::Input::readInput()
{
	int value;
	std::cout << "\nEnter xPos yPos Value for insert: ";
	std::cin >> this->position.first >> this->position.second >> value;
	this->value = static_cast<uint8_t>(value);
}

void Game::printLogic() const
{
	std::cout << "\n> Currently playing as Player " << static_cast<int>(m_currentPlayer) + 1;
	m_board.printGameboard();
	std::cout << "\n> Valid positions for insert: ";
	m_board.printValidPositions();
	std::cout << "\n> Current cards held by player: ";
	m_players[static_cast<size_t>(m_currentPlayer)].printPlayerCards();

	auto mage = getMage(m_currentPlayer);
	if (mage != nullptr)
	{
		std::cout << "\n> Mage: \n";
		mage.get()->getDescription();
	}

	auto magicPowers = getMagicPowers(m_currentPlayer);
	if (!magicPowers.empty())
	{
		std::cout << "\n> Magic Powers: \n";
		for (const auto& magicPower : magicPowers)
		{
			magicPower.get()->getDescription();
			std::cout << "\n";
		}
	}
}

Player& Game::getCurrentPlayer()
{
	return m_players[static_cast<size_t>(m_currentPlayer)];
}

bool Game::checkWinCase1(PlayerEnum currentPlayer) const
{
	if (verifySum(currentPlayer) && verifyNullPresence(currentPlayer))
	{
		if (verifyRowOrColumnWin(currentPlayer) || verifyDiagonalWin(currentPlayer))
		{
			return true;
		}
		return false;
	}
	return false;
}

bool Game::checkWinCase2(PlayerEnum currentPlayer) const
{
	return m_board.checkWinCase2(currentPlayer);
}

bool Game::checkWinCase3(PlayerEnum currentPlayer) const
{
	return m_players[static_cast<size_t>(m_currentPlayer)].hasUsedAllCards();
}

bool Game::checkIfWin(PlayerEnum currentPlayer) const
{
	if (!m_board.isFirstMove())
	{
		if (checkWinCase1(currentPlayer))
			return true;

		if (checkWinCase2(currentPlayer) || checkWinCase3(currentPlayer))
			return true;


		//win case 4 somehow
		return false;
	}

	return false;
}

const std::shared_ptr<AbstractMage>& Game::getMage(PlayerEnum currentPlayer) const
{
	if (!m_players[static_cast<size_t>(currentPlayer)].hasUsedMage())
	{
		size_t playerIndex = (currentPlayer == PlayerEnum::Player1) ? 0 : 1;

		const Gamemode& gamemode = m_players[playerIndex].getGamemode();

		return gamemode.getMages().at(playerIndex);
	}

	return nullptr;
}

const std::vector<std::shared_ptr<AbstractMagic>> Game::getMagicPowers(PlayerEnum currentPlayer) const
{
	std::vector<std::shared_ptr<AbstractMagic>> unusedMagicPowers;
	if (!m_players[static_cast<size_t>(currentPlayer)].hasUsedMagic())
	{
		size_t playerIndex = (currentPlayer == PlayerEnum::Player1) ? 0 : 1;

		const Gamemode& gamemode = m_players[playerIndex].getGamemode();

		for (const auto& magicPower : gamemode.getMagicPowers())
		{
			if (!magicPower->hasBeenUsed())
			{
				unusedMagicPowers.push_back(magicPower);
			}
		}

		return unusedMagicPowers;
	}

	return unusedMagicPowers;
}

bool Game::verifySum(PlayerEnum currentPlayer) const
{
	auto& gamemode = m_players[static_cast<size_t>(m_currentPlayer)].getGamemode();
	uint8_t columnSum = std::accumulate(m_bridge.getColumnPocket().begin(), m_bridge.getColumnPocket().end(), 0,
		[currentPlayer](uint8_t sum, const std::pair<uint8_t, uint8_t>& pocket) {
			return sum + (currentPlayer == PlayerEnum::Player1 ? pocket.first : pocket.second);
		});

	return columnSum >= 3 + gamemode.getIs4x4();
}

bool Game::verifyNullPresence(PlayerEnum currentPlayer) const
{
	bool columnHasNoZeros = !std::any_of(m_bridge.getColumnPocket().begin(), m_bridge.getColumnPocket().end(),
		[currentPlayer](const std::pair<uint8_t, uint8_t>& pocket) {
			return (currentPlayer == PlayerEnum::Player1 ? pocket.first : pocket.second) == 0;
		});

	bool rowHasNoZeros = !std::any_of(m_bridge.getRowPocket().begin(), m_bridge.getRowPocket().end(),
		[currentPlayer](const std::pair<uint8_t, uint8_t>& pocket) {
			return (currentPlayer == PlayerEnum::Player1 ? pocket.first : pocket.second) == 0;
		});

	return columnHasNoZeros || rowHasNoZeros;
}

bool Game::verifyRowOrColumnWin(PlayerEnum currentPlayer) const
{
	auto& gamemode = m_players[static_cast<size_t>(m_currentPlayer)].getGamemode();
	uint8_t targetValue = 3 + gamemode.getIs4x4();

	bool columnWin = std::any_of(m_bridge.getColumnPocket().begin(), m_bridge.getColumnPocket().end(),
		[targetValue, currentPlayer](const std::pair<uint8_t, uint8_t>& pocket) {
			return (currentPlayer == PlayerEnum::Player1 ? pocket.first : pocket.second) == targetValue;
		});

	bool rowWin = std::any_of(m_bridge.getRowPocket().begin(), m_bridge.getRowPocket().end(),
		[targetValue, currentPlayer](const std::pair<uint8_t, uint8_t>& pocket) {
			return (currentPlayer == PlayerEnum::Player1 ? pocket.first : pocket.second) == targetValue;
		});

	return columnWin || rowWin;
}

bool Game::verifyDiagonalWin(PlayerEnum currentPlayer) const
{
	return std::equal(m_bridge.getColumnPocket().begin(), m_bridge.getColumnPocket().end(), m_bridge.getRowPocket().begin(),
		[currentPlayer](const std::pair<uint8_t, uint8_t>& col, const std::pair<uint8_t, uint8_t>& row) {
			return (currentPlayer == PlayerEnum::Player1 ? col.first : col.second) == (currentPlayer == PlayerEnum::Player1 ? row.first : row.second);
		});
}

void Game::switchPlayer()
{
	m_currentPlayer = (m_currentPlayer == PlayerEnum::Player1 ? PlayerEnum::Player2 : PlayerEnum::Player1);
	//std::cout << "\nSwitch player to Player " << static_cast<int>(m_currentPlayer) + 1;
}

std::string_view Game::getPlayerChoice() const
{
	auto& player = m_players[static_cast<size_t>(m_currentPlayer)];
	auto& gamemode = player.getGamemode();

	auto hasUsedMage = player.hasUsedMage();
	auto hasUsedMagic = player.hasUsedMagic();

	std::cout << "\n> Possible available listed below. Please type what you choose:\n";
	std::cout << " > Card\n";

	if (!gamemode.getMages().empty())
	{
		std::cout << " > Mage\n";
	}
	if (!gamemode.getMagicPowers().empty())
	{
		std::cout << " > Magic\n";
	}
	if (gamemode.getHasIlusions())
	{
		std::cout << " > Illusion\n";
	}
	if (gamemode.getHasExplosions())
	{
		std::cout << " > Explosion\n";
	}
	std::cout << " > Save\n";

	static std::string choice;
	std::cout << "Your choice: ";
	std::cin >> choice;
	std::cout << '\n';


	std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

	if (choice == "card" ||
		(choice == "mage" && !gamemode.getMages().empty() && !hasUsedMage) ||
		(choice == "magic" && !gamemode.getMagicPowers().empty() && !hasUsedMagic) ||
		(choice == "illusion" && gamemode.getHasIlusions()) ||
		(choice == "explosion" && gamemode.getHasExplosions()) ||
		choice == "save")
	{
		return choice;
	}
	else
	{
		std::cout << "Invalid choice. Please try again.\n";
		return getPlayerChoice();
	}
}

void Game::handleChoice(std::string_view choice)
{
	if (choice == "card")
	{
		placeCard();
	}
	else if (choice == "mage")
	{
		//mage();
	}
	else if (choice == "magic")
	{
		//magic();
	}
	else if (choice == "ilusion")
	{
		//illusion();
	}
	else if (choice == "explosion")
	{
		//explosion();
	}
	else if (choice == "save")
	{
		std::cout << "Game progress saved.\n";
		//save progress
		getPlayerChoice();
	}
}

void Game::placeCard()
{
	m_input.readInput();

	//first ring of verification
	if (!m_board.validateInsertPosition(m_input.position))
	{
		std::cout << "wrong!\n";
		return placeCard(); /*restart loop*/
	}
	if (!m_board.validateValue(m_input.value))
	{
		std::cout << "value wrong!\n";
		return placeCard(); /*restart loop*/
	}
	if (!getCurrentPlayer().removeCard(m_input.value))
	{
		std::cout << "value available wrong!\n"; /*if card exists also delete it*/
		return placeCard(); /*restart loop*/
	}
	if (!m_board.validateStackRule(m_input.position, m_input.value))
	{
		std::cout << "value stack wrong!\n";
		return placeCard(); /*restart loop*/
	}

	//second ring of verification
	if (!m_board.isFirstMove() && !m_board.tryGridShiftForInsertPosition(m_input.position))
	{
		std::cout << "grid wrong\n";
		return placeCard();
	}

	m_board.insertCard(Card{ m_input.value,m_currentPlayer }, m_input.position);

	if (m_board.getLockcase() < m_board.getMinLockcaseValue())
	{
		m_board.addPositionToValid(m_input.position);
		m_board.setLockcase();
	}


	std::cout << "\n==============================================================\n";
}

PlayerEnum Game::playGame()
{
	while (true)
	{
		printLogic();
		handleChoice(getPlayerChoice());


		//instead of one function, let them be and handle them here
		if (checkIfWin(m_currentPlayer))
		{
			std::cout << "won";
			break;
		}

		switchPlayer();
	}
	return m_currentPlayer;
}