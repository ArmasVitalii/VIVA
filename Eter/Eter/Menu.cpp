#include "Menu.h"
#include <cstdlib>

bool Menu::askBooleanOption(const std::string& question)
{
    char choice;
    std::cout << question;
    std::cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

Gamemode Menu::showMenu()
{
    std::string selectedMode;

    std::cout << "Choose a gamemode (Training, Mage, Magic, MageAndMagic): ";
    std::cin >> selectedMode;

    Gamemode selectedGamemode = GamemodeDistributor::generateGamemode(selectedMode,
        askBooleanOption("Do you want illusions in the game? (y/n): "), 
        askBooleanOption("Do you want explosions in the game? (y/n): "));


    std::system("cls");

    return selectedGamemode;
}

void Menu::handleMatch()
{
    Match eterMatch(showMenu());
    eterMatch.test_start();
}
