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


/*
void FireMasters::UsePower2(Game& game)
{

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
	MarkUsedPower(2);
}

bool FireMasters::IsValidRow(Game& game, int row)
{
	int cards = 0;
	bool hasOwnCard = false;
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
	return cards >= 3 && hasOwnCard;
}

bool FireMasters::IsOwnCard(Game& game, int row, int col)
{
	std::stack<Card>& cardStack = game.getGameboard()[row][col];
	if (!cardStack.empty())
	{
		Card topCard = cardStack.top();
		//Add an function to get the current player's index
		//return topCard.getWhoPlayed() = game.getCurrentPlayer;
		if (topCard.getWhoPlayed() == game.getCurrentPlayer())
		{
			return true;
		}
	}
	return false;
}

EarthMasters::EarthMasters()
{
	m_name = "Earth Masters";
}

void EarthMasters::Activate(Game& game)
{
	if (!power1Used)
	{
		//First power: cover opponent's card
		UsePower1(game);
	}
	else if (!power2Used)
	{
		//Second power: create pit
		UsePower2(game);
	}

}

void EarthMasters::UsePower1(Game& game)
{
	std::cout << "Covering opponent's card with a lower card.\n";
	int row, col;

	std::cout << "Enter the row and column of the opponent's card: ";
	std::cin >> row >> col;

	if (!game.getGameboard()[row][col].empty())
	{
		std::cout << "No card at this position.\n";
		return;
	}

	Card opponentCard = game.getGameboard()[row][col].top();

	if (opponentCard.getWhoPlayed() == game.getCurrentPlayer())
	{
		std::cout << "This is your card, not an opponent's.\n";
		return;
	}

	int newCardValue;
	std::cout << "Enter a card value from your hand that is lower than the oppnent's card: ";
	std::cin >> newCardValue;

	if (newCardValue >= opponentCard.getValue())
	{
		std::cout << "Card value must be strictly lower than the oppenent's card.\n";
		return;
	}

	game.getGameboard()[row][col].push(Card(newCardValue, game.getCurrentPlayer()));
	MarkUsedPower(1);

}

void EarthMasters::UsePower2(Game& game)
{
	std::cout << "Creating a pit\n";
	int row, col;

	std::cout << "Enter the row and column where you want to create a pit: ";
	std::cin >> row >> col;

	if (row < 0 || row >= game.getGameboard().size() || col < 0 || col >= game.getGameboard()[row].size())
	{
		std::cout << "Invalid position. Please enter valid coordinates.\n";
		return;
	}

	if (!game.getGameboard()[row][col].empty()) {
		std::cout << "This space is not empty! Please choose an empty space to create a pit.\n";
		return;
	}

	game.getGameboard()[row][col].push(Card(-1, false));
	std::cout << "A pit has been created at (" << row << ", " << col << ").\n";

	MarkUsedPower(2);
}

AirMasters::AirMasters()
{
	m_name = "Air Masters";
}

void AirMasters::Activate(Game& game)
{
	if (!power1Used)
	{
		//First power: move stack of cards
		UsePower1(game);
	}
	else if (!power2Used)
	{
		//Second power: get an eter card
		UsePower2(game);
	}

}

void AirMasters::UsePower1(Game& game)
{
	std::cout << "Move your stack to another position\n";
	int row, col;

	std::cout << "Enter the row and column where you want to move your stack: ";
	std::cin >> row >> col;

	if (row < 0 || row >= game.getGameboard().size() || col < 0 || col >= game.getGameboard()[row].size())
	{
		std::cout << "Invalid position. Please enter valid coordinates.\n";
		return;
	}

	if (!game.getGameboard()[row][col].empty())
	{
		std::cout << "This position is not empty. Please choose an empty space.\n";
		return;
	}

	for (int i = 0; i < game.getGameboard().size(); i++)
	{
		for (int j = 0; j < game.getGameboard()[i].size(); j++)
		{
			if (!game.getGameboard()[i][j].empty() && game.getGameboard()[i][j].top().getWhoPlayed() == true)
			{
				std::stack<Card>stackToMove = game.getGameboard()[i][j];
				game.getGameboard()[i][j] = std::stack<Card>();

				game.getGameboard()[row][col] = stackToMove;
				std::cout << "Your stack has been moved to position (" << row << ", " << col << ").\n";
				return;
			}
		}
	}
	std::cout << "No stack with your card found on the board.\n";

	MarkUsedPower(1);
}

void AirMasters::UsePower2(Game& game)
{
	std::cout << "You can place an ETER card \n";
	int row, col;

	std::cout << "Enter the position where to place it: ";
	std::cin >> row >> col;

	if (row < 0 || row >= game.getGameboard().size() || col < 0 || col >= game.getGameboard()[row].size())
	{
		std::cout << "Invalid position! \n";
		return;
	}

	if (!game.getGameboard()[row][col].empty())
	{
		std::cout << "This position is occupied! You cannot place an ETER card. \n";
		return;
	}

	Card ETERcard(1, false);

	game.getGameboard()[row][col].push(ETERcard);
	MarkUsedPower(2);
}

WaterMasters::WaterMasters()
{
	m_name = "Water Masters";
}

void WaterMasters::Activate(Game& game)
{
	if (!power1Used)
	{
		//First power: move opponent's card
		UsePower1(game);
	}
	else if (!power2Used)
	{
		//Second power: move a row
		UsePower2(game);
	}
}

void WaterMasters::UsePower1(Game& game)
{
	int row, col;
	std::cout << "Where do you want to place the stack of cards? /n";
	std::cin >> row >> col;

	if (row < 0 || row >= game.getGameboard().size() || col < 0 || col >= game.getGameboard()[row].size())
	{
		std::cout << "Invalid positions! \n";
		return;
	}

	if (!game.getGameboard()[row][col].empty())
	{
		std::cout << "The position is occupied! Choose an empty space \n ";
		return;
	}

	for (int i = 0; i < game.getGameboard().size(); i++)
	{
		for (int j = 0; j < game.getGameboard()[i].size(); j++)
		{
			if (!game.getGameboard()[i][j].empty())
			{
				Card topCard = game.getGameboard()[i][j].top();
				if (!topCard.getWhoPlayed())
				{
					std::stack<Card> opponentStack = game.getGameboard()[i][j];

					game.getGameboard()[i][j] = std::stack<Card>();
					game.getGameboard()[row][col] = opponentStack;

					MarkUsedPower(1);
					return;
				}

			}
		}
	}
}

void WaterMasters::UsePower2(Game& game)
{
	int row, targetRow;
	std::cout << "Enter the row you want to move: ";
	std::cin >> row;
	std::cout << "Enter the row where you want to move it the chosen row: ";
	std::cin >> targetRow;

	if (row < 0 || row >= game.getGameboard().size() || targetRow < 0 || targetRow >= game.getGameboard().size())
	{
		std::cout << "Invalid rows! \n";
		return;
	}

	if (row == targetRow)
	{
		std::cout << "The rows cannot be the same! \n";
		return;
	}

	int occupiedPos = 0;
	for (const auto& col : game.getGameboard()[row])
	{
		if (!col.empty())
			occupiedPos++;
	}

	if (occupiedPos < 3)
	{
		std::cout << "The source row must have at least 3 occupied positions.\n";
		return;
	}

	for (const auto& col : game.getGameboard()[targetRow])
	{
		if (!col.empty())
		{
			std::cout << "The target row is not occupied! Please choose another row.\n";
			return;
		}
	}

	for (int col = 0; col < game.getGameboard()[row].size(); col++)
	{
		game.getGameboard()[targetRow][col] = game.getGameboard()[row][col];
		game.getGameboard()[row][col] = std::stack<Card>(); //change?
	}

	MarkUsedPower(2);
}*/
