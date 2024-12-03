#pragma once
#include "AllGamemodes.h"
class GameModeDistributor
{
public:
	static Gamemode setGamemode(std::string_view modeName);
};

