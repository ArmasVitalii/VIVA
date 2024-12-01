#include "Mages.h"

RemoveCardMage::RemoveCardMage(const std::string& name)
{
	m_name = "RemoveCardMage";
}

void RemoveCardMage::Activate(Game& game)
{
	if (IsUsedPower())
	{
		std::cout << "Power already used! ";
		return;
	}
	std::cout << "Removing opponent's card \n";
	bool cardRemoved = false;
	int row, col;

	std::cout << "Introduce the row and column for removing a card: ";
	std::cin >> row >> col;

	game.removeOpponentCard(row, col);
	MarkUsedPower();
}

RemoveRowMage::RemoveRowMage(const std::string& name)
{
	m_name = "Remove Row Mage";
}

void RemoveRowMage::Activate(Game& game)
{
	if (IsUsedPower())
	{
		std::cout << "Power already used! ";
		return;
	}

	std::cout << "Removing a row of cards.\n";
	int row;

	std::cout << "Enter the row to remove: ";
	std::cin >> row;

	if (!IsValidRow(game, row))
	{
		std::cout << "Invalid row. Row must have at least 3 cards and contain your own card.\n";
		return;
	}

	game.removeRow(row);
	MarkUsedPower();
}

bool RemoveRowMage::IsValidRow(Game& game, int row)
{
	int cards = 0;
	bool hasOwnCard = false;

	// Parcurge fiecare coloană din rândul respectiv
	for (int col = 0; col < game.getGameboard()[row].size(); col++)
	{
		if (!game.getGameboard()[row][col].empty())
		{
			cards++;
			if (IsOwnCard(game, row, col))
			{
				hasOwnCard = true;
			}
		}
	}
	return false; //fix!
}