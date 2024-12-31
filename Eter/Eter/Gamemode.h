#pragma once

#include <list>
#include <vector>
#include <cstdint>
#include <memory>
#include "AbstractMage.h"
#include "AbstractMagic.h"

class Gamemode
{
private:
    bool                                                m_is4x4{ false };
    std::list<uint8_t>                                  m_cardList{};
    uint8_t                                             m_maxNumberOfGames{ 0 };
    std::vector<std::shared_ptr<AbstractMage>>          m_mages{};
    std::vector<std::shared_ptr<AbstractMagic>>         m_magicPowers{};
    bool                                                m_hasIlusions{ false };
    bool                                                m_hasExplosions{ false };
    bool                                                m_hasTimer{ false };

public:
    Gamemode(bool is4x4,
        const std::list<uint8_t>& cardList,
        uint8_t maxNumberOfGames,
        const std::vector<std::shared_ptr<AbstractMage>>& mages,
        const std::vector<std::shared_ptr<AbstractMagic>>& magicPowers,
        bool hasIlusions,
        bool hasExplosions,
        bool hasTimer);

    bool                                                getIs4x4() const;
    const std::list<uint8_t>&                           getCardList() const;
    uint8_t                                             getMaxNumberOfGames() const;
    const std::vector<std::shared_ptr<AbstractMage>>&   getMages() const;
    const std::vector<std::shared_ptr<AbstractMagic>>&  getMagicPowers() const;
    bool                                                getHasIlusions() const;
    bool                                                getHasExplosions() const;
    bool                                                getHasTimer() const;

    void                                                setHasIlusions(bool value);
    void                                                setHasExplosions(bool value);

    void                                                printSetup() const;
};
