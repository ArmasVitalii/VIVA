#include "Game.h"

void Game::start()
{

}

gameboard& Game::getGameBoard()
{
	return m_gameBoard;
}

const Player& Game::getPlayer1() const
{
	return m_players[1];
}

const Player& Game::getPlayer2() const
{
	return m_players[2];
}
