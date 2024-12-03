#pragma once
#include <stdint.h>
#include <string_view>
#include <stdexcept>
#include <array>
#include <string>
#include "GameMode.h"
class AllGamemodes
{
private:
    enum class gModes : uint8_t
    {
        training,
        mage,
        magic,
        speed,

        Count
    };
    std::array<Gamemode, static_cast<size_t>(gModes::Count)> m_allGamemodes;
    static std::array<Gamemode, static_cast<size_t>(gModes::Count)> initializeGamemodes();
public:
    AllGamemodes();
    Gamemode& getGamemode(gModes mode);                 /*dont knwo if we will need this*/
    Gamemode& getGamemode(std::string_view modeName);

    static gModes stringToGameMode(std::string_view modeName);
};

