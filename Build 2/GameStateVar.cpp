#include "GameStateVar.h"
#include "Session.h"


GameStateVar::GameStateVar()
{
	constructGameState();
}


GameStateVar::~GameStateVar()
{
}

void GameStateVar::constructGameState()
{
	this->blue = 24;
	this->yellow = 24;
	this->black = 24;
	this->red = 24;
	this->infectionRate = 2;
	this->infectionCounter = 1;
	this->eclosionCounter = 0;
	this->blueCure = false;
	this->yellowCure = false;
	this->blackCure = false;
	this->redCure = false;
	this->blueEradicated = false;
	this->yellowEradicated = false;
	this->blackEradicated = false;
	this->redEradicated = false;
	this->oneQuietNight = false;
	this->researchCenterCounter = 0;
}

GameStateVar * GameStateVar::getInstance()
{
	static GameStateVar * instance = new GameStateVar();

	return instance;
}

void GameStateVar::reset()
{
	constructGameState();
}

int GameStateVar::getResearchCenterCounter()
{
	return researchCenterCounter;
}

void GameStateVar::incrementResearchCenterCounter()
{
	++researchCenterCounter;
}

bool GameStateVar::decrementCube(int region, vector<string> * log)
{
	switch (region) {
	case 1:
		--blue;
		if (blue >= 0) {
			log->push_back("Blue cubes remaining: " + to_string(blue));
			return true;
		}
		else {
			return false;
		}
		break;
	case 2:
		--yellow;
		if (yellow >= 0) {
			log->push_back("Yellow cubes remaining: " + to_string(yellow));
			return true;
		}
		else {
			return false;
		}
		break;

	case 3:
		--black;
		if (black >= 0) {
			log->push_back("Black cubes remaining: " + to_string(black));
			return true;
		}
		else {
			return false;
		}
		break;

	case 4:
		--red;
		if (red >= 0) {
			log->push_back("Red cubes remaining: " + to_string(red));
			return true;
		}
		else {
			return false;
		}
		break;
	default:
		return false;
	}
}

void GameStateVar::incrementCube(int color)
{
	switch (color) {
	case 1:
		++blue;
		break;
	case 2:
		++yellow;
		break;
	case 3:
		++black;
		break;
	case 4:
		++red;
		break;
	}
}

bool GameStateVar::incrementEclosion(vector<string> * log)
{
	++eclosionCounter;
	log->push_back("Eclosion counter incremented to: " + to_string(eclosionCounter));
	this->incrementInfection();
	if (eclosionCounter == 8) {
		return false;
	}
	else {
		return true;
	}
	return false;
}

int GameStateVar::infectionIncreaseIn() {
	switch (infectionCounter) {
	case 1:
		return 3;
	case 2:
		return 2;
	case 3:
		return 1;
	case 4:
		return 2;
	case 5:
		return 1;
	default:
		return -1;
	}
}

void GameStateVar::incrementInfection()
{
	++infectionCounter;
	switch (infectionCounter) {
	case 1:
		infectionRate = 2;
		break;
	case 2:
		infectionRate = 2;
		break;
	case 3:
		infectionRate = 2;
		break;
	case 4:
		infectionRate = 3;
		break;
	case 5:
		infectionRate = 3;
		break;
	case 6:
		infectionRate = 4;
		break;
	case 7:
		infectionRate = 4;
		break;
	default:
		infectionRate = 4;
		break;
	}
}

bool GameStateVar::getOneQuietNight() {
	return oneQuietNight;
}

void GameStateVar::setOneQuietNight(bool oneQuietNight) {
	this->oneQuietNight = oneQuietNight;
}

int GameStateVar::getBlue()
{
	return this->blue;
}

int GameStateVar::getYellow()
{
	return this->yellow;
}

int GameStateVar::getBlack()
{
	return this->black;
}

int GameStateVar::getRed()
{
	return this->red;
}

int GameStateVar::getEclosionCounter()
{
	return this->eclosionCounter;
}

int GameStateVar::getInfectionRate()
{
	return this->infectionRate;
}

int GameStateVar::getInfectionCounter()
{
	return this->infectionCounter;
}

bool GameStateVar::getCure(int region)
{
	switch (region) {
	case 1:
		return blueCure;
	case 2:
		return yellowCure;
	case 3:
		return blackCure;
	case 4:
		return redCure;
	default:
		return false;
	}
}

bool GameStateVar::setCure(int region)
{
	switch (region) {
	case 1:
		blueCure = true;
		break;
	case 2:
		yellowCure = true;
		break;
	case 3:
		blackCure = true;
		break;
	case 4:
		redCure = true;
		break;
	default:
		break;
	}
	return !(blueCure && yellowCure && blackCure && redCure);
}

bool GameStateVar::getEradicated(int region)
{
	switch (region) {
	case 1:
		return blueEradicated;
	case 2:
		return yellowEradicated;
	case 3:
		return blackEradicated;
	case 4:
		return redEradicated;
	default:
		return false;
	}
}

void GameStateVar::setEradicated(int region)
{
	switch (region) {
	case 1:
		blueEradicated = true;
		break;
	case 2:
		yellowEradicated = true;
		break;
	case 3:
		blackEradicated = true;
		break;
	case 4:
		redEradicated = true;
		break;
	default:
		break;
	}
}

int GameStateVar::getDisease(int region) {
	switch (region) {
	case 1:
		return blue;
	case 2:
		return yellow;
	case 3:
		return black;
	case 4:
		return red;
	}
}

bool GameStateVar::isGameWon() {
	bool answer = false;
	if (Session::getInstance()->getNumberOfLocations(1) > 0) {
		answer = blueCure;
		if (!answer) {
			return false;
		}
	}
	if (Session::getInstance()->getNumberOfLocations(2) > 0) {
		answer = yellowCure;
		if (!answer) {
			return false;
		}
	}
	if (Session::getInstance()->getNumberOfLocations(3) > 0) {
		answer = blackCure;
		if (!answer) {
			return false;
		}
	}
	if (Session::getInstance()->getNumberOfLocations(4) > 0) {
		answer = redCure;
		if (!answer) {
			return false;
		}
	}
	return true;

}

bool GameStateVar::isGameLost() {
	return eclosionCounter == 8 ||
		blue == 0 ||
		yellow == 0 ||
		black == 0 ||
		red == 0;
}

bool GameStateVar::isGameOver() {
	return this->isGameWon() || this->isGameLost();
}
