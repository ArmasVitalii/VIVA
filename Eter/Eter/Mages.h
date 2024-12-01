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

/*class EarthMasters : public Mage
{
public:
	EarthMasters();
	void Activate(Game& game) override;

private:
	void UsePower1(Game& game);
	void UsePower2(Game& game);
};

class AirMasters : public Mage
{
public:
	AirMasters();
	void Activate(Game& game) override;

private:
	void UsePower1(Game& game);
	void UsePower2(Game& game);
};

class WaterMasters : public Mage
{
public:
	WaterMasters();
	void Activate(Game& game) override;

private:
	void UsePower1(Game& game);
	void UsePower2(Game& game);
};*/

