#pragma once
class town
{
private:

	int turnClass;
	int lvlCitadelClass;
	int amountOfHousesClass, amountOfBarracksClass, amountOfMinesClass, amountOfMillsClass;

public:

	void setTurn(int turn)
	{
		turnClass = turn;
	}

	void setLvlCitadel(int lvlCitadel)
	{
		lvlCitadelClass = lvlCitadel;
	}

	void setHouses(int amountOfHouses)
	{
		amountOfHousesClass = amountOfHouses;
	}

	void setBarracks(int amountOfBarracks)
	{
		amountOfBarracksClass = amountOfBarracks;
	}

	void setMines(int amountOfMines)
	{
		amountOfMinesClass = amountOfMines;
	}

	void setMills(int amountOfMills)
	{
		amountOfMillsClass = amountOfMills;
	}

	int getMills()
	{
		return amountOfMillsClass;
	}

	int getMines()
	{
		return amountOfMinesClass;
	}

	int getBarracks()
	{
		return amountOfBarracksClass;
	}

	int getHouses()
	{
		return amountOfHousesClass;
	}

	int getLvlCitadel()
	{
		return lvlCitadelClass;
	}
	int getTurn()
	{
		return turnClass;
	}
};

