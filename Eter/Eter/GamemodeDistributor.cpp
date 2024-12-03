#include "GameModeDistributor.h"

Gamemode GameModeDistributor::setGamemode(std::string_view modeName)
{
    AllGamemodes allModes;
    return allModes.getGamemode(modeName);
}
