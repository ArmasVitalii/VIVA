#pragma once
#include "Mage.h"
#include "Game.h"

class FireMasters : public Mage //Mage 1: MASTERS OF FIRE
{
public:
	FireMasters();
	void Activate(Game& game) override;

private:
	void UsePower1(Game& game);
	void UsePower2(Game& game);
	bool IsValidRow(Game& game, int row);
	bool IsOwnCard(Game& game, int row, int col);
};


class EarthMasters : public Mage
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
};
