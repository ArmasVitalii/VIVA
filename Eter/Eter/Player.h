#pragma once
#include <list>
#include <stdint.h>
#include "Gamemode.h"
#include "Bridge.h"

class Player
{
private:
    std::reference_wrapper<const Gamemode>  m_gamemode;
    std::reference_wrapper<const Bridge>    m_bridge;

    std::list<uint8_t>                      m_cards;
    uint8_t                                 m_numberOfGamesWon;

    bool                                    mtest_hasUsedMage;
    bool                                    mtest_hasUsedMagicPower;

public:
    explicit Player(const std::reference_wrapper<const Gamemode>& gamemode, const std::reference_wrapper<const Bridge>& bridge);

    void                                    initialisePlayerCards();
    void                                    printPlayerCards() const;
    uint8_t&                                getNumberOfGamesWon();
    void                                    incrementGamesWon();

    void                                    addCard(uint8_t card);
    bool                                    removeCard(uint8_t cardValue);


    bool                                    hasUsedAllCards() const;
    bool                                    hasUsedMage() const;
    bool                                    hasUsedMagic() const;
    const Gamemode&                         getGamemode() const;


    void                                    markMageUsed();
    void                                    resetPlayer();
};
