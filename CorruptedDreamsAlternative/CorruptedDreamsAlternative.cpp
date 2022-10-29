#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <ctime>
#include <stdio.h>
#include <conio.h>
#include <cmath>
#include <fstream>

#include "gameBaseSettings.h"
#include "town.h"
#include "Windows.h"
#include "json.hpp"

#include "irrKlang-64bit-1.6.0\include\irrKlang.h"
#pragma comment(lib, "irrKlang.lib")


using namespace std;
using namespace irrklang;
using json = nlohmann::json;
using jsonf = nlohmann::json;

bool realGameIsRunning, isRunning, gameOption;

ISoundEngine* engine = createIrrKlangDevice();
ISound* m_background = engine->play2D("trees.wav", true, true);

int cloudwood, fogstone, pops, army, fortitude, turn, citadel, houses, barracks, mines, mills;
string name;

void runText(string runningText)
{
    for (int i = 0; i < runningText.length(); i++)
    {
        cout << runningText[i];
        if (runningText[i] != ' ')
        {
            engine->play2D("type.wav");
        }
        Sleep(20);
        
        
    }
    cout << endl;
}

void runTextNoEndl(string runningText)
{
    for (int i = 0; i < runningText.length(); i++)
    {
        cout << runningText[i];
        if (runningText[i] != ' ')
        {
            engine->play2D("type.wav");
        }
        Sleep(20);


    }
}

string intToStr(int num)
{
    stringstream ss;
    string str;
    ss << num;
    ss >> str;
    return str;
}

int strToInt(string str)
{
    stringstream ss;
    int num;
    ss << str;
    ss >> num;
    return num;
}

string strLower(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = tolower(str[i]);
    }

    return str;
}

int upgrade(int buildingsAmount, string buildingType, string resourse)
{
    int price = 0;

    strLower(buildingType);
    strLower(resourse);

    if (buildingType == "citadel")
    {
        price = buildingsAmount^2 * 150 + 100;
    }
    else if (buildingType == "house")
    {
        if (resourse == "cloudwood")
        {
            price = buildingsAmount * 15 + 5;
        }

        else if (resourse == "fogstone")
        {
            price = buildingsAmount * 10;
        }
    }
    else if (buildingType == "barracks")
    {
        if (resourse == "cloudwood")
        {
            price = buildingsAmount * 20 + 25;
        }

        else if (resourse == "fogstone")
        {
            price = buildingsAmount * 25 + 20;
        }
    }
    else if (buildingType == "mine")
    {
        if (resourse == "cloudwood")
        {
            price = buildingsAmount * 30 + 10;
        }
    }
    else if (buildingType == "mill")
    {
        if (resourse == "fogstone")
        {
            price = buildingsAmount * 30 + 10;
        }
    }

    if (resourse == "pops")
    {
        price = 30;
    }

    return price;
}

int playerTurn(town dreamtown, GBS baseSettings)
{
    int option;

    int popsPrice = 0, cloudwoodPrice = 0, fogstonePrice = 0;

    int partyTime = 0;

    int buildingOptions;

Options:
    runText("Your options are:");
    cout << "0: View your stats" << endl;
    cout << "1: Build & upgrade" << endl;
    cout << "2: Fortify" << endl;
    cout << "3: Train army" << endl;
    cout << "4: Begin the celebration" << endl;
    cout << "5: SAVE your progress" << endl;
    cout << "6: Wake up" << endl;

    option = _getch() - 48;
    
    if (option == 0)
    {
        runText("Your stats are:");
        runText("Turn:");
        runText(intToStr(dreamtown.getTurn()));
        runText("Fortitude level:");
        runText(intToStr(baseSettings.getFortitude()));
        runText("Cloudwood amount:");
        runText(intToStr(baseSettings.getCloudwood()));
        runText("Fogstone amount:");
        runText(intToStr(baseSettings.getFogstone()));
        runText("Population amount:");
        runText(intToStr(baseSettings.getPops()));
        runText("Soldiers amount:");
        runText(intToStr(baseSettings.getArmy()));
        runText("Level of your citadel:");
        runText(intToStr(dreamtown.getLvlCitadel()));
        runText("Houses amount:");
        runText(intToStr(dreamtown.getHouses()));
        runText("Barracks amount:");
        runText(intToStr(dreamtown.getBarracks()));
        runText("Fogged mines amount:");
        runText(intToStr(dreamtown.getMines()));
        runText("Cloudmills amount:");
        runText(intToStr(dreamtown.getMills()));
        goto Options;
    }
    else if (option == 1)
    {
        runText("What would you like to build?");
        runText("1: Upgrade citadel");
        runText("2: Build houses");
        runText("3: Build barracks");
        runText("4: Build fogged mine");
        runText("5: Build cloudmill");
        runText("6: Return to options menu");
        
        option = _getch() - 48;

        if (option == 1)
        {
            runText("Upgrading your citadel will increase the production rate of ALL buildings! Are you sure that you want to build it?");
            runText("The price of this upgrade is:");
            cloudwoodPrice = upgrade(citadel, "citadel", "cloudwood");
            fogstonePrice = upgrade(citadel, "citadel", "fogstone");
            cout << "CLOUDWOOD: " << cloudwoodPrice << endl;
            cout << "FOGSTONE: " << fogstonePrice << endl;

        }
        
        else if (option == 2)
        {
            runText("Building more houses will allow you to increase population rate. Are you sure that you want to build it?");
            runText("The price of this upgrade is:");
            cloudwoodPrice = upgrade(houses, "house", "cloudwood");
            fogstonePrice = upgrade(houses, "house", "fogstone");
            cout << "CLOUDWOOD: " << cloudwoodPrice << endl;
            cout << "FOGSTONE: " << fogstonePrice << endl;

        }
        
        else if (option == 3)
        {
            runText("Building more barracks will increase the power of your army! Are you sure that you want to build it?");
            runText("The price of this upgrade is:");
            cloudwoodPrice = upgrade(barracks, "barracks", "cloudwood");
            fogstonePrice = upgrade(barracks, "barracks", "fogstone");
            cout << "CLOUDWOOD: " << cloudwoodPrice << endl;
            cout << "FOGSTONE: " << fogstonePrice << endl;
        }

        else if (option == 4)
        {
            runText("Building a fogged mine will allow you to gain more fogstone! Are you sure that you want to build it?:");
            runText("The price of this upgrade is:");
            cloudwoodPrice = upgrade(mines, "mine", "cloudwood");
            popsPrice = upgrade(mines, "mine", "pops");
            cout << "CLOUDWOOD: " << cloudwoodPrice << endl;
            cout << "POPS: " << popsPrice << endl;
        }

        else if (option == 5)
        {
            runText("Building a cloudmill will allow you to gain more cloudwood! Are you sure that you want to build it?:");
            runText("The price of this upgrade is:");
            fogstonePrice = upgrade(mills, "mill", "fogstone");
            popsPrice = upgrade(mills, "mill", "pops");
            cout << "FOGSTONE: " << fogstonePrice << endl;
            cout << "POPS: " << popsPrice << endl;
        }

        else if (option == 6)
        {
            goto Options;
        }

        runText("1: Build");
        runText("2 Do not");

        buildingOptions = _getch() - 48;
        if ((fogstonePrice <= fogstone || cloudwoodPrice <= cloudwood || popsPrice <= pops) & buildingOptions == 1)
        {
            fogstone -= fogstonePrice;
            cloudwood -= cloudwoodPrice;
            pops -= popsPrice;

            if (option == 1)
            {
                citadel++;
            }
            else if (option == 2)
            {
                houses++;
            }
            else if (option == 3)
            {
                barracks++;
            }
            else if (option == 4)
            {
                mines++;
            }
            else if (option == 5)
            {
                mills++;
            }
        }
        else
        {
            runText("Oops! I guess you don't have enough materials for that, or you just want to build it right now. Who knows?");
            goto Options;
        }
    }
    else if (option == 2)
    {
        runText("Fortifying costs 5 fogstone, 5 cloudwood and 5 creatures - it increases the fortification of the dreamtown. Would you like to proceed?");
        runText("1: Yes");
        runText("2: No");

        fogstonePrice = 5;
        cloudwoodPrice = 5;
        popsPrice = 5;

        buildingOptions = _getch() - 48;

        if ((fogstonePrice <= fogstone || cloudwoodPrice <= cloudwood || popsPrice <= pops) && buildingOptions == 1)
        {
            fogstone -= fogstonePrice;
            cloudwood -= cloudwoodPrice;
            pops -= popsPrice;

            fortitude++;
        }
        else
        {
            runText("Oops! I guess you just can't afford that or you don't want to. Who knows?");
            goto Options;
        }

    }
    else if (option == 3)
    {
        int soldiersAmount;
        runText("How many soldiers would you like to train? Every soldier requires 1 creature, 1 fogstone and 1 cloudwood.");
        cin >> soldiersAmount;

        fogstonePrice = soldiersAmount;
        cloudwoodPrice = soldiersAmount;
        popsPrice = soldiersAmount;

        if (fogstonePrice > fogstone || cloudwoodPrice > cloudwood || popsPrice > pops)
        {
            runText("Oops! I guess you don't have enough materials for that!");
            goto Options;
        }
        else
        {
            fogstone -= fogstonePrice;
            cloudwood -= cloudwoodPrice;
            pops -= popsPrice;

            army += soldiersAmount;
        }

    }
    else if (option == 4)
    {
        runText("Party time! Population modifier will increase for a turn.");
        partyTime = 1;

    }

    else if (option == 5)
    {
        jsonf jsonfile;

        jsonfile["Name"] = baseSettings.getName();
        jsonfile["Army"] = baseSettings.getArmy();
        jsonfile["Cloudwood"] = baseSettings.getCloudwood();
        jsonfile["Fogstone"] = baseSettings.getFogstone();
        jsonfile["Pops"] = baseSettings.getPops();
        jsonfile["Fortitude"] = baseSettings.getFortitude();
        jsonfile["Barracks"] = dreamtown.getBarracks();
        jsonfile["Houses"] = dreamtown.getHouses();
        jsonfile["CitadelLevel"] = dreamtown.getLvlCitadel();
        jsonfile["Cloudmills"] = dreamtown.getMills();
        jsonfile["FoggedMines"] = dreamtown.getMines();
        jsonfile["Turn"] = dreamtown.getTurn();
        
        ofstream file("savedata.json");
        file << jsonfile;

        runText("File saved successfully!");
        engine->play2D("save.wav");
        gameOption = false;
    }
    
    else if (option == 6)
    {
        realGameIsRunning = false;
        isRunning = false;
        runText("\"Wakey wakey, sleepyhead!\"");
        gameOption = false;
        _getch();
    }

    turn++;

    cloudwood += mills + citadel;
    fogstone += mines + citadel;
    pops += houses * (partyTime * 2) - barracks + citadel;
    army += barracks + citadel;

    partyTime = 0;

    return dreamtown.getTurn();
}

string nameGen()
{
    int gender = rand() % 1;
    std::ifstream file;
    if (gender == 0)
    {
        file.open("maleCharNames.json");
    }
    else
    {
        file.open("femaleCharNames.json");
    }

    json j;
    file >> j;
    file.close();

    string randomFirstLine = j["firstNames"][rand() % j["firstNames"].size()];

    j.find("middleNames");
    string randomMiddleLine = j["middleNames"][rand() % j["middleNames"].size()];

    string generatedName = randomFirstLine + randomMiddleLine;

    return generatedName;

}

void event()
{
    srand(time(NULL));

    int chance;

    chance = rand() % 100;
    if (chance > 60)
    {
        ifstream file;
        file.open("events.json");
        json j = json::parse(file);
        file.close();
        string counselor = nameGen();

        runTextNoEndl("It looks like one of your counselors, ");
        cout << counselor;
        runText(", has something to say for you...");

        chance = rand() % 100;

        string event;
        if (chance > 50)
        {
            event = "EventsPositive";
        }
        else if (chance <= 50)
        {
            event = "EventsNegative";
        }
        j.find(event);

        int eventNumber = rand() % 5;
        string randomEventName = j[event][eventNumber]["Title"];

        runText(randomEventName);                                      
        
        j[event][eventNumber].find("Data");

        
        cloudwood += strToInt(j[event][eventNumber]["cloudwood"]) * round(turn / 10);
        fogstone += strToInt(j[event][eventNumber]["fogstone"]) * round(turn / 10);
        pops += strToInt(j[event][eventNumber]["pops"]) * round(turn / 10);
        army += strToInt(j[event][eventNumber]["army"]) * round(turn / 10) - round(fortitude / 10);
    }
}

int main()
{
    // IP 127.0.0.1
    uint32_t LOCALHOST_IP = 0x0100007f;

    // INITIALIZATION
    int option;
    GBS baseSettings;
    town dreamtown;
    string name;
    int volume;

    string runningText;

    srand(time(NULL));

    // GAME MENU: START
    isRunning = true;

    
    while (isRunning)
    {
    
        // ASCII art
        cout << R"(.         _  .          .          .    +     .          .          .      .
        .(_)          .            .            .            .       :
        .   .      .    .     .     .    .      .   .      . .  .  -+-        .
          .           .   .        .           .          /         :  .
    . .        .  .      /.   .      .    .     .     .  / .      . ' .
        .  +       .    /     .          .          .   /      .
       .            .  /         .            .        *   .         .     .
      .   .      .    *     .     .    .      .   .       .  .
          .           .           .           .           .         +  .
  . .        .  .       .   .      .    .     .     .    .      .   .

 .   +      .          ___/\_._/~~\_...__/\__.._._/~\        .         .   .
       .          _.--'                              `--./\          .   .
           /~~\/~\                                         `-/~\_            .
 .      .-'                    Corrupted Dreams                  `-/\_
  _/\.-'                                                            __/~\/\-.__
.'                                                                           `)" << endl;


    PreGame:
        runText("1: Play");
        runText("2: Credits");
        runText("3: Load");
        runText("4: How to play?");

        option = _getch() - 48;

        if (option == 2)
        {
            runText("This game application was made for as a course project by õ̷̧̝̘̭̺̝͚̣̣̙̔̆̃͆̔͛̉̚̚ \"That Abyss Egg\" ǫ̷͕̞̗̟̣͚̩͉̤́̆͆̽͐̃͒͂͗̋̍̕͠ͅ, BSUIR, 2021.");
            runText("Marvelous OST made by Pedro Silva for OMORI. Sound effects are obtained from free sources");
            goto PreGame;
        }
        else if (option == 3)
        {
            ifstream file("savedata.json");
            json j;
            file >> j;
            file.close();
            j.find("Army");
            baseSettings.setArmy(j["Army"]);
            army = baseSettings.getArmy();
            j.find("Barracks");
            dreamtown.setBarracks(j["Barracks"]);
            barracks = dreamtown.getBarracks();
            j.find("CitadelLevel");
            dreamtown.setLvlCitadel(j["CitadelLevel"]);
            citadel = dreamtown.getLvlCitadel();
            j.find("Cloudmills");
            dreamtown.setMills(j["Cloudmills"]);
            mills = dreamtown.getMills();
            j.find("Cloudwood");
            baseSettings.setCloudwood(j["Cloudwood"]);
            cloudwood = baseSettings.getCloudwood();
            j.find("FoggedMines");
            dreamtown.setMines(j["FoggedMines"]);
            mines = dreamtown.getMines();
            j.find("Fogstone");
            baseSettings.setFogstone(j["Fogstone"]);
            fogstone = baseSettings.getFogstone();
            j.find("Fortitude");
            baseSettings.setFortitude(j["Fortitude"]);
            fortitude = baseSettings.getFortitude();
            j.find("Houses");
            dreamtown.setHouses(j["Houses"]);
            houses = dreamtown.getHouses();
            j.find("Name");
            baseSettings.setName(j["Name"]);
            name = baseSettings.getName();
            j.find("Pops");
            baseSettings.setPops(j["Pops"]);
            pops = baseSettings.getPops();
            j.find("Turn");
            dreamtown.setTurn(j["Turn"]);
            turn = dreamtown.getTurn();

            m_background->setIsPaused(false);

            goto Loaded;
        }
        else if (option == 4)
        {
            runText("Your goal is to build your very own kingdom! Build more upgrades, and try to stand against the spooky events, that could accure in DREAMWORLD");
            runText("But beware! You will LOSE instantly when you lose ALL of your ARMY or POPS!");
            goto PreGame;
        }
        else
        {
            if (!engine)
            {
                return 0;
            }
            m_background->setIsPaused(false);
            runText("The day was quite a rough one for you. Another one of those, where you follow the famous plan: \"Get up, wash yourself, go to work, go to bed.\" But this time you just can feel the adventures that wait you in the perfect world of dreams. You decided to...");
            runText("0: Stay awake.");
            runText("1: Close your eyes and fall asleep.");

            option = _getch() - 48;
            if (option == 0)
            {
                runText("You stood awake for a much longer time than you expected. Just before you noticed it, you already fell asleep in a few hours, but this time there was no dream world for you to explore...");
                isRunning = false;
            }
            else if (option == 1)
            {
                runText("When you opened your eyes, you found yourself on the golden throne. There was a window on the left, where you could see a beautiful green sky... and destroyed by war town of yours. Your responsibility is to RESTORE it!");
                runText("You look around the ruins once again. Nobody probably remembers the name of this town anyways, so you decided to call it...");
                cin >> name;
                runText("\"We are glad to meet you once again, out leader!\" - you can hear from a distance. Yes, you are back, but you can see the destruction that happened to your kingdom, and it brings you pain in your heart. Time to start a day...");

                // GAME: TRUE START

                baseSettings.setName(name);
                name = baseSettings.getName();
                baseSettings.setCloudwood(0);
                cloudwood = baseSettings.getCloudwood();
                baseSettings.setFogstone(0);
                fogstone = baseSettings.getFogstone();
                baseSettings.setPops(10);
                pops = baseSettings.getPops();
                baseSettings.setArmy(5);
                army = baseSettings.getArmy();
                baseSettings.setFortitude(1);
                fortitude = baseSettings.getFortitude();
                dreamtown.setTurn(1);
                turn = dreamtown.getTurn();
                dreamtown.setLvlCitadel(0);
                citadel = dreamtown.getLvlCitadel();
                dreamtown.setHouses(0);
                houses = dreamtown.getHouses();
                dreamtown.setBarracks(0);
                barracks = dreamtown.getBarracks();
                dreamtown.setMines(1);
                mines = dreamtown.getMines();
                dreamtown.setMills(1);
                mills = dreamtown.getMills();

            Loaded:
                baseSettings.setStart(true);

                realGameIsRunning = baseSettings.getStart();
                while (realGameIsRunning)
                {
                    gameOption = true;
                    playerTurn(dreamtown, baseSettings);

                    if (gameOption)
                    {
                        event();
                    }
                
                    if (army <= 0)
                    {
                        runText("Nobody is stable, neither is your kingdom. As soon as the last of your warriors fell, the kingdom began to drown in shadows of the monsters from the fog. And just as they pierced you with their giant claws... you woke up in your bed.");
                        realGameIsRunning = false;
                        isRunning = false;
                        _getch();
                    }
                    else if (pops <= 0)
                    {
                        runText("Many of your people just couldn't stand the events that you brought to their lives. Just as the last one of them left you thought that you are all alone now... Just until they came back, having weapons of all kinds. And just as a shot from their CLOUDBOW pierced your heart... you woke up in your bed.");
                        realGameIsRunning = false;
                        isRunning = false;
                        _getch();
                    }

                    baseSettings.setArmy(army);
                    baseSettings.setCloudwood(cloudwood);
                    baseSettings.setFogstone(fogstone);
                    baseSettings.setFortitude(fortitude);
                    baseSettings.setPops(pops);
                    dreamtown.setBarracks(barracks);
                    dreamtown.setHouses(houses);
                    dreamtown.setMines(mines);
                    dreamtown.setMills(mills);
                    dreamtown.setLvlCitadel(citadel);
                    dreamtown.setTurn(turn);
                }
            }
        }
    }

    engine->drop();

    return 0;
}