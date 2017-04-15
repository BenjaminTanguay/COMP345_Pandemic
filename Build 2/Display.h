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
#include "PlayEventCardController.h"
#include "PercentInfectedCityStatisticsDecorator.h"


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

	// Following the observer pattern. The observer contains a copy of its subject
	Statistics * stats;

	int cityLines();
	

public:
	Display();
	~Display();

	int listCities(vector<City*>* cities, City * city);
	int printPlayer(Player * player, int currentLine, int indexOfPlayer);
	int printCity(City * city, int currentLine, int maxNumberOfLines, vector<string> * cityConnectionNames);
	void completeBottomWidget(int numberOfLines);
	int cityChoice(Player * player, string question, vector<City *> * listOfCities);
	int topWidget();
	int mainScreen();
	int cityWidget();
	void Update();
	void Update(string message);
	void Update(vector<string> * log);



};


