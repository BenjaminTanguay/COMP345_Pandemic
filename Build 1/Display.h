#pragma once
#include <iostream>
#include <string>
#include "session.h"
#include "GameStateVar.h"
#include "Player.h"
#include "Card.h"
#include "CityCard.h"
#include "EventCard.h"
#include "ConsoleFormat.h"
#include "Observer.h"


using namespace std;


class Display : public Observer
{
	const enum color {
		black = 0,
		dblue = 1,
		dgreen = 2,
		dteal = 3,
		dred = 4,
		purple = 5,
		brown = 6,
		lgrey = 7,
		mgrey = 8,
		blue = 9,
		green = 10,
		teal = 11,
		red = 12,
		pink = 13,
		yellow = 14,
		white = 15
	};

	static const int INTEGER = 1;
	static const int STRING = 2;
	string numberOfDiseaseCubes[12];
	string cureState[12];
	string gameStatus[12];

	int cityLines();
	int printPlayer(Player * player, int currentLine, int indexOfPlayer);
	int printCity(City * city, int currentLine, int maxNumberOfLines, vector<string> * cityConnectionNames);
	void completeBottomWidget(int numberOfLines);
	int inputCheck(int lowerBound, int upperBound);
	void diseaseModification(int region, vector<string>* log, int lineCount, City * currentCity);
	void loadMapDialog();
	void regularMapInitialization();
	void gameInstantiation();

	int listCities(vector<City*>* cities, City * city);

public:
	Display();
	~Display();

	int topWidget();
	int mainScreen();
	int cityWidget();
	void welcomeSceen();
	void newGameScreen();
	void mapEditorGeneralDialog();
	void mapEditorCreateModifyDialog();
	void mapEditorParametersDialog(string city);
	void gameLoop();
	void playerMove();
	void driveFerry();
	void directFlight();
	void charterFlight();
	void shuttleFlight();
	void treatDisease();
	void shareKnowledge();
	void discoverCure();
	void Update();
	void Update(string message);
	void Update(vector<string> * log);



};

bool isInteger(const std::string & s);
