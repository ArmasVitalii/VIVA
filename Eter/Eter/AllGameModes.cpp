#include "AllGamemodes.h"

std::array<Gamemode, static_cast<size_t>(AllGamemodes::gModes::Count)> AllGamemodes::initializeGamemodes()
{
    constexpr uint8_t ETER = 5;

    return {
        /*			is4x4		cardList		noOfGames	Mage  Magic  Exp.	Ilus.	Timer			*/
             Gamemode(false, {1,1,2,2,3,3,4},			3, false, false, false, false, false),			//TRAINING
             Gamemode(true,	{1,1,2,2,2,3,3,3,4,ETER},	5, true, false, false, false, false),			//MAGE DUEL
             Gamemode(true,	{1,2,2,2,3,3,3,4,ETER},		5, false, true, false, false, false),			//MAGIC DUEL
             Gamemode(false, {},						0, false, false, false, false, true)			//TODO:TIMER
    };
}

AllGamemodes::AllGamemodes() :m_allGamemodes(initializeGamemodes())
{
}

Gamemode& AllGamemodes::getGamemode(gModes mode)
{
    return m_allGamemodes.at(static_cast<size_t>(mode));
}

Gamemode& AllGamemodes::getGamemode(std::string_view modeName)
{
    gModes mode = stringToGameMode(modeName);
    return getGamemode(mode);
}

AllGamemodes::gModes AllGamemodes::stringToGameMode(std::string_view modeName)
{
    if (modeName == "training") return gModes::training;
    if (modeName == "mage")     return gModes::mage;
    if (modeName == "magic")    return gModes::magic;
    if (modeName == "speed")    return gModes::speed;
    throw std::invalid_argument("Invalid game mode!");  //ONLY FOR CONSOLE TEST
}
