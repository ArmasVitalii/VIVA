#pragma once
#include <array>
#include "Player.h"
#include "Bridge.h"
#include "Board.h"

class Game
{
private:
    const	PlayerEnum k_baseFirstPlayer{ PlayerEnum::Player1 };
    struct	Input
    {
        std::pair<size_t, size_t> position;
        uint8_t value;
        void readInput();
    };


    Input					                            m_input;

    Bridge& m_bridge;
    Board                                               m_board;
    std::array<Player, 2>& m_players;

    PlayerEnum				                            m_currentPlayer{ k_baseFirstPlayer };

    const std::shared_ptr<AbstractMage>& getMage(PlayerEnum currentPlayer) const;
    const std::vector<std::shared_ptr<AbstractMagic>>   getMagicPowers(PlayerEnum currentPlayer) const;

    bool                                                verifySum(PlayerEnum currentPlayer) const;
    bool                                                verifyNullPresence(PlayerEnum currentPlayer) const;
    bool                                                verifyRowOrColumnWin(PlayerEnum currentPlayer) const;
    bool                                                verifyDiagonalWin(PlayerEnum currentPlayer) const;

    bool                                                checkWinCase1(PlayerEnum currentPlayer) const;
    bool                                                checkWinCase2(PlayerEnum currentPlayer) const;
    bool                                                checkWinCase3(PlayerEnum currentPlayer) const;
    bool                                                checkIfWin(PlayerEnum currentPlayer) const;

    void                                                printLogic() const;
    Player& getCurrentPlayer();
    void                                                switchPlayer();

    std::string_view                                    getPlayerChoice() const;
    void                                                handleChoice(std::string_view choice);

    PlayerEnum                                          placeCard();

public:
    explicit Game(Bridge& bridge, const Board& board, std::array<Player, 2>& players);

    PlayerEnum playGame();
};