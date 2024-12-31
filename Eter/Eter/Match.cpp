#include "Match.h"

Match::Match(Gamemode gamemode)
    : m_gamemode(std::move(gamemode)),
    m_bridge(Bridge(m_gamemode)),
    m_board(m_gamemode, m_bridge),
    m_players{ { Player{m_gamemode, m_bridge},
                Player{m_gamemode, m_bridge} } }
{
}

void Match::test_start()
{
    Game ownGame(m_bridge, m_board, m_players);
    ownGame.playGame();
}

std::reference_wrapper<const Gamemode> Match::getGamemode() const
{
    return std::cref(m_gamemode);
}