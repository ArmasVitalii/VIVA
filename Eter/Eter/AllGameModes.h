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
    std::array<GameMode, static_cast<size_t>(gModes::Count)> m_allGamemodes;
    static std::array<GameMode, static_cast<size_t>(gModes::Count)> initializeGamemodes();
public:
    AllGamemodes();
    GameMode& getGamemode(gModes mode);                 /*dont knwo if we will need this*/
    GameMode& getGamemode(std::string_view modeName);

    static gModes stringToGameMode(std::string_view modeName);
};

