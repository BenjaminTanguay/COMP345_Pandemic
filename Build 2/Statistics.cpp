#include "Statistics.h"



int Statistics::getNumberOfDiseasedCity()
{
	int numberOfDiseasedCity = 0;
	for (auto iterate = PlayMap::getInstance()->getPlayMap()->begin(); iterate != PlayMap::getInstance()->getPlayMap()->end(); ++iterate) {
		if (iterate->second->isDiseased()) {
			++numberOfDiseasedCity;
		}
	}
	return numberOfDiseasedCity;
}

int Statistics::getNumberOfCardsInPlayerHand(int playerId, int region, int cardType)
{
	Player * player = Session::getInstance()->getPlayers()->at(playerId);
	int numberOfCards = 0;
	for (auto iterate = player->getHand()->begin(); iterate != player->getHand()->end(); ++iterate) {
		switch (cardType) {
		case cityCard:
			if (dynamic_cast<CityCard *>(*iterate) != nullptr) {
				// && dynamic_cast<CityCard *>(*iterate)->getLocation()->getRegion() == region
				++numberOfCards;
			}
			break;
		case eventCard:
			if (dynamic_cast<EventCard *>(*iterate) != nullptr) {
				++numberOfCards;
			}
			break;
		default:
			break;
		}
	}
	return numberOfCards;
}

vector<string>* Statistics::getHandSize()
{
	vector<string> * handSize = new vector<string>;
	for (int i = 0; i < Session::getInstance()->getPlayers()->size(); ++i) {
		handSize->push_back(to_string(Session::getInstance()->getPlayers()->at(i)->getHand()->size()));
	}
	return handSize;
}

int Statistics::getNumberOfDiseaseOnMap()
{
	int numberOfCubes = 0;
	for (int i = 0; i < Session::getInstance()->getNumberOfRegionInPlay(); ++i) {
		numberOfCubes += 24 - GameStateVar::getInstance()->getDisease(i + 1);
	}
	return numberOfCubes;
}

int Statistics::getNumberOfCardsInDeck(int region, int cardType) {
	switch (cardType) {
	case cityCard:
		return Session::getInstance()->getPlayerDeck()->getRegionCard(region);
	case eventCard:
		return Session::getInstance()->getPlayerDeck()->getEventCards();
	default:
		return 0;
	}
}

vector<string> * Statistics::getNumberOfPlayerCardsRemainingInDeck() {
	vector<string> * data = new vector<string>;
	for (int i = 1; i <= Session::getInstance()->getNumberOfRegionInPlay(); ++i) {
		data->push_back(to_string(getNumberOfCardsInDeck(i, cityCard)));
	}
	return data;
}

Statistics::Statistics()
{
	lines = 8;
}


Statistics::~Statistics()
{
}

int Statistics::getNumberOfLines() {
	return lines;
}

int Statistics::getStatistics(int line)
{
	ConsoleFormat::setColor(ConsoleFormat::lgrey, ConsoleFormat::black);
	switch (line) {
	case 0:
		ConsoleFormat::makeBox(20, "");
		break;
	case 1:
		ConsoleFormat::makeBox(20, "Statistics:");
		break;
	case 2:
		ConsoleFormat::makeBox(19, "Cities infected:", to_string(getNumberOfDiseasedCity()), 3);
		break;
	case 3:
		ConsoleFormat::makeBox(20, "Hand size:");
		break;
	case 4:
		ConsoleFormat::printMultipleColorBoxWithData(24, Session::getInstance()->getPlayers()->size(), getHandSize(), ConsoleFormat::player);
		break;
	case 5:
		ConsoleFormat::makeBox(19, "Disease on map:", to_string(getNumberOfDiseaseOnMap()), 3);
		break;
	case 6:
		ConsoleFormat::makeBox(20, "CityCards in deck:");
		break;
	case 7:
		ConsoleFormat::printMultipleColorBoxWithData(24, Session::getInstance()->getNumberOfRegionInPlay(), getNumberOfPlayerCardsRemainingInDeck(), ConsoleFormat::region);
		break;
	}
	ConsoleFormat::setColor(ConsoleFormat::black, ConsoleFormat::black);
	return 24;
}
