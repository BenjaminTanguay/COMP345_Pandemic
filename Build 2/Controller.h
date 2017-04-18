#pragma once
#include <string>
#include <vector>
#include "City.h"
#include "Player.h"
#include "Display.h"

using namespace std;
class Controller
{
private:
	Display * display;

	const enum load {
		map = 1,
		game = 2
	};

	void regularMapInitialization();
	
	void diseaseModification(int region, vector<string>* log, int lineCount, City * currentCity);
	void loadFileDialog(int mapOrGame);
	void saveFileDialog(int mapOrGame);
	void gameInstantiation();
	void playEventCards();
	void handSizeCheck(Player * player);
	Card * cardSelection(Player * player, string message);
	void eventCardPrompt();
	void playEventCardOrDiscard(Player * player);
	void playRole();
	void dispatcher();
	Player * choseAPlayer();

public:
	Controller();
	~Controller();

	static int inputCheck(int lowerBound, int upperBound);
	void welcomeSceen();
	void newGameScreen();
	void mapEditorGeneralDialog();
	void mapEditorCreateModifyDialog();
	void mapEditorParametersDialog(string city);
	void gameLoop();
	void playerMove(Player * aPlayer);
	void driveFerry(Player * aPlayer);
	void directFlight(Player * aPlayer);
	void charterFlight(Player * aPlayer);
	void shuttleFlight(Player * aPlayer);
	void buildResearchCenter();
	void treatDisease();
	void shareKnowledge();
	void discoverCure();
};

bool isInteger(const std::string & s);