#include "FireMage.h"
#include "Game.h"

FireMage::FireMage()
{
    m_description = "FireMage: Removes a row or column of cards from the board containing at least 3 positions and one own card.";
}

void FireMage::getDescription() const
{
    std::cout << m_description << std::endl;
}

bool FireMage::usePower(Game& game) const
{
    std::cout << "FireMage uses power to remove a row of cards!" << std::endl;
    auto is4x4 = game.accessBoard();
    auto gb = game.accessBoard();

    int choice;
    std::cout << "\nPlease input if you'd like to remove a column or a row: \n1.Row\n2.Column\n";
    std::cin >> choice;
    if (choice == 1)
    {
        size_t row;
        std::cout << "\nPlease enter the row you want to erase: ";
        std::cin >> row;
        bool conditionMet{ false };
        int noOfPositions{ 0 };
        for (int j = gb.getGridMiddle().second - 1 - 0.5 * gb.getis4x4(); j <= gb.getGridMiddle().second + 1 + 0.5 * gb.getis4x4(); j++)
        {
            if (game.accessGameboardAPI()[row][j].has_value())
                noOfPositions++;
            if (gb.containsOwnCard({ row,j }, game.getCurrentPlayerEnum()))
                conditionMet = true;
        }

        if (conditionMet && noOfPositions >= 3)
        {
            for (int j = gb.getGridMiddle().second - 1 - 0.5 * gb.getis4x4(); j <= gb.getGridMiddle().second + 1 + 0.5 * gb.getis4x4(); j++)
            {
                auto& stack = game.accessGameboardAPI()[row][j].value();
                while (!stack.empty())
                {
                    game.accessBoard().removeCard({ row,j });
                }
            }
            return true;
        }
        else
        {
            std::cout << "\nCannot remove row!\n";
            return false;
        }
    }
    else if (choice == 2)
    {
        size_t col;
        std::cout << "\nPlease enter the column you want to erase: ";
        std::cin >> col;
        bool conditionMet{ false };
        int noOfPositions{ 0 };
        for (int i = gb.getGridMiddle().first - 1 - 0.5 * gb.getis4x4(); i <= gb.getGridMiddle().first + 1 + 0.5 * gb.getis4x4(); i++)
        {
            if (game.accessGameboardAPI()[i][col].has_value())
                noOfPositions++;
            if (gb.containsOwnCard({ i,col }, game.getCurrentPlayerEnum()))
                conditionMet = true;
        }
        if (conditionMet && noOfPositions >= 3)
        {
            for (int i = gb.getGridMiddle().first - 1 - 0.5 * gb.getis4x4(); i <= gb.getGridMiddle().first + 1 + 0.5 * gb.getis4x4(); i++)
            {
                auto& stack = game.accessGameboardAPI()[i][col].value();
                while (!stack.empty())
                {
                    game.accessBoard().removeCard({ i,col });
                }
            }
            return true;
        }
        else
        {
            std::cout << "\nCannot remove row!\n";
            return false;
        }
    }
    else
    {
        std::cout << "\nInvalid choice!";
    }



    return false;
}
