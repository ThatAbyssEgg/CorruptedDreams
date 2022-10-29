#pragma once
#include <string>

using namespace std;

class GBS
{
private:
	bool GBSisRunning;
	bool GBSgameBegan;

	string GBSname;
	int GBScloudwood;
	int GBSfogstone;
	int GBSpops;
	int GBSarmy;
	int GBSfortitude;

	bool GBSisCorrupt;

public:
	void setRunning(bool running)
	{
		GBSisRunning = running;
	}
	
	void setStart(bool gameBegan)
	{
		GBSgameBegan = gameBegan;
	}

	void setName(string name)
	{
		GBSname = name;
	}
	
	void setCloudwood(int cloudwood)
	{
		GBScloudwood = cloudwood;
	}

	void setFogstone(int fogstone)
	{
		GBSfogstone = fogstone;
	}

	void setPops(int pops)
	{
		GBSpops = pops;
	}

	void setArmy(int army)
	{
		GBSarmy = army;
	}
	
	void setFortitude(int fortitude)
	{
		GBSfortitude = fortitude;
	}

	string getName()
	{
		return GBSname;
	}

	int getCloudwood()
	{
		return GBScloudwood;
	}
	int getFogstone()
	{
		return GBSfogstone;
	}
	int getPops()
	{
		return GBSpops;
	}

	int getArmy()
	{
		return GBSarmy;
	}

	int getFortitude()
	{
		return GBSfortitude;
	}

	bool getStart()
	{
		return GBSgameBegan;
	}

	bool getRunning()
	{
		return GBSisRunning;
	}
};

