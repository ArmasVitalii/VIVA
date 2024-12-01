#pragma once
#include "Mage.h"
#include "Game.h"

class RemoveCardMage : public Mage //Mage 1: removing opponent's card
{
public:
	RemoveCardMage(const std::string& name);
	void Activate(Game& game) override;
};

class  RemoveRowMage : public Mage //Mage 2
{
public:
	RemoveRowMage(const std::string& name);
	void Activate(Game& game) override;
private:
	bool IsValidRow(Game& game, int row);
};

class CoverCardMage : public Mage
{
public:
	CoverCardMage(const std::string& name);
	void Activate(Game& game) override;
};

class CreatePitMage : public Mage
{
public:
	CreatePitMage(const std::string& name);
	void Activate(Game& game) override;
};

class MoveStackMage : public Mage
{
public:
	MoveStackMage(const std::string& name);
	void Activate(Game& game) override;
};

class GetEterCardMage : public Mage
{
public:
	GetEterCardMage(const std::string& name);
	void Activate(Game& game) override;
};

class MoveCardMage : public Mage
{
public:
	MoveCardMage(const std::string& name);
	void Activate(Game& game) override;
};

class MoveRowMage : public Mage
{
public:
	MoveRowMage(const std::string& name);
	void Activate(Game& game) override;
};
