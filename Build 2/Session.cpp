#include "Session.h"


// Initialize the objects that needs to go on the heap.
Session::Session()
{

	numberOfLocationsPerRegion = new vector<int>;
	this->numberOfRegionsInPlay = 0;
	for (int i = 0; i < 4; ++i) {
		numberOfLocationsPerRegion->push_back(0);
	}
	this->locations = new unordered_map<string, Location *>;
	playMap = PlayMap::getInstance();
	this->players = new vector<Player *>;
	this->playerDeck = new PlayerDeck();
	this->infectionDeck = new InfectionDeck();
	this->cityCards = new unordered_map<string, CityCard *>;
	this->eventCards = new unordered_map<string, EventCard *>;
}

// The origin is used to store the default location where players will begin on the play map. 
// By default, the origin point should have a research center.
void Session::setOrigin(Location * cityName)
{
	this->playMap->setOrigin(cityName);
	for (unsigned i = 0; i < this->players->size(); ++i) {
		this->players->at(i)->setLocation(this->playMap->getPlayMap()->at(cityName));
	}
}

Session::Session(City * origin)
{
	playMap = PlayMap::getInstance(origin);
}

map<Location *, City *, compareMap> * Session::getPlayMap() {
	return this->playMap->getPlayMap();
}

int Session::getCurrentPlayer()
{
	return static_cast<int>(currentPlayer);
}

Session::~Session()
{
	delete playMap;
	playMap = nullptr;
	delete players;
	players = nullptr;
	delete locations;
	locations = nullptr;
	delete cityCards;
	cityCards = nullptr;
	delete eventCards;
	eventCards = nullptr;
	delete numberOfLocationsPerRegion;
	numberOfLocationsPerRegion = nullptr;
}



// The origin is used to store the default location where players will begin on the play map.
City * Session::getOrigin()
{
	return this->playMap->getOrigin();
}

// Setters and getters
vector<Player *> * Session::getPlayers()
{
	return this->players;
}

int Session::getPlayerTurn()
{
	return playerTurn;
}

int Session::getPlayerPhase()
{
	return playerPhase;
}

void Session::setPlayerTurn(int const turn)
{
	this->playerTurn = turn;
}

void Session::setPlayerPhase(int const phase)
{
	this->playerPhase = phase;
}

void Session::setDifficultyLevel(int const difficultyLevel)
{
	this->difficultyLevel = difficultyLevel;
}

int Session::getDifficultyLevel()
{
	return this->difficultyLevel;
}


// Simple interface implemented so that we can demonstrate the different functions of the classes in the main.
void Session::clearPlayMap()
{
	this->playMap->clearPlayMap();
	// The players needs to point to a city. If there is no city, there can be no player.
	this->clearPlayers();
	this->playerDeck->clear();
	this->infectionDeck->clear();
	this->locations->clear();
	this->cityCards->clear();
}

void Session::clearPlayers()
{
	this->players->clear();
}

void Session::addResearchCenter(Location * city)
{
	this->playMap->addResearchCenter(city);
}



bool Session::savePlayMap(string fileName)
{
	if (!this->playMap->savePlayMap(fileName)) {
		return false;
	}
	return true;
}

bool Session::loadPlayMap(string fileName)
{
	if (!this->playMap->loadPlayMap(fileName)) {
		return false;
	}
	locations->clear();
	playerDeck->clear();
	infectionDeck->clear();
	for (auto iterate = this->playMap->getPlayMap()->begin(); iterate != this->playMap->getPlayMap()->end(); ++iterate) {
		generateCards(iterate->first);
		locations->emplace(iterate->first->getName(), iterate->first);
	}
	return true;
}

InfectionDeck * Session::getInfectionDeck()
{
	return this->infectionDeck;
}

PlayerDeck * Session::getPlayerDeck()
{
	return this->playerDeck;
}

CityCard * Session::getCityCards(string name)
{
	return cityCards->at(name);
}

bool Session::infect(Location * city, int numberOfInfections, int region, vector<string> * log)
{
	City * cityToInfect = this->playMap->getPlayMap()->at(city);
	int currentDiseaseCount = cityToInfect->getDisease(region);
	bool temp;
	if (currentDiseaseCount + numberOfInfections > 3) {
		for (int i = 0; i < 4 - currentDiseaseCount; ++i) {
			temp = cityToInfect->infect(new unordered_map<string, City *>, region, log);
			if (!temp) {
				break;
			}
		}
	}
	else {
		for (int i = 0; i < numberOfInfections; ++i) {
			temp = cityToInfect->infect(new unordered_map<string, City *>, region, log);
			if (!temp) {
				break;
			}
		}
	}
	return temp;

}

void Session::initializeInfections()
{
	infectionDeck->shuffle();
	int numberOfEpidemicCardsToShuffle;
	switch (difficultyLevel) {
		// Introductory
	case 1:
		numberOfEpidemicCardsToShuffle = 4;
		break;
		// Standard
	case 2:
		numberOfEpidemicCardsToShuffle = 5;
		break;
		// Heroic
	case 3:
		numberOfEpidemicCardsToShuffle = 6;
		break;
	}
	playerDeck->shuffleEpidemic(numberOfEpidemicCardsToShuffle);
	vector<string> * log = new vector<string>;
	for (int j = 3; j > 0; --j) {
		for (int i = 0; i < 3; ++i) {
			Location * loc = infectionDeck->draw();
			log->push_back(loc->getName() + " drawn from the infection deck.");
			infect(loc, j, loc->getRegion(), log);
		}
	}
	Notify(log);
	log = nullptr;
}

bool Session::infectionDraw(vector<string> * log) {
	return infect(infectionDeck->epidemic(), 3, infectionDeck->epidemic()->getRegion(), log);
}

bool Session::drawFromInfectionDeck(vector<string> * log) {
	Location * loc = infectionDeck->draw();
	log->push_back(loc->getName() + " drawn from the infection deck.");
	bool temp = infect(loc, 1, loc->getRegion(), log);
	Notify(log);
	loc = nullptr;
	return temp;
}

bool Session::playerDraw(unsigned index) {
	Card * card;
	if (playerDeck->getSize() != 0) {
		card = playerDeck->draw();
	}
	else {
		return false;
	}
	bool temp = true;
	if (dynamic_cast<EpidemicCard *>(card) != nullptr) {
		vector<string> * log = new vector<string>;
		log->push_back(players->at(index)->getPlayerName() + " drew an infection card.");
		temp = this->infectionDraw(log);
		playerDeck->toDiscard(dynamic_cast<EpidemicCard *>(card));
		Notify(log);
		log = nullptr;
		return temp;
	}
	else {
		if (dynamic_cast<CityCard *>(card) != nullptr) {
			players->at(index)->draw(dynamic_cast<CityCard *>(card));
			Notify(players->at(index)->getPlayerName() + " drew " + dynamic_cast<CityCard *>(card)->getTitle());
			return true;
		}
		else if (dynamic_cast<EventCard *>(card) != nullptr) {
			players->at(index)->draw(dynamic_cast<EventCard *>(card));
			playerDeck->decrementEventCards();
			Notify(players->at(index)->getPlayerName() + " drew " + dynamic_cast<EventCard *>(card)->getTitle());
			return true;
		}
		else {
			return true;
		}
	}
}

void Session::initializeHands(vector<string> * log) {
	unsigned handSize;
	if (players->size() == 4) {
		handSize = 2;
	}
	if (players->size() == 3) {
		handSize = 3;
	}
	if (players->size() == 2) {
		handSize = 4;
	}
	playerDeck->initialize();
	for (unsigned i = 0; i < players->size(); ++i) {
		for (unsigned j = 0; j < handSize; ++j) {
			playerDraw(i);
		}
	}
}

void Session::addLocation(const string name, const int region)
{
	Location * loc = new Location(name, region);
	this->locations->emplace(name, loc);
	if (this->locations->size() == 1) {
		this->playMap->setNewOrigin(loc, true);
		this->playMap->getPlayMap()->emplace(loc, this->playMap->getOrigin());
	}
	else {
		this->playMap->getPlayMap()->emplace(loc, new City(loc, false));
	}
	if (loc->getRegion() > numberOfRegionsInPlay) {
		numberOfRegionsInPlay = loc->getRegion();
	}
	++numberOfLocationsPerRegion->at(loc->getRegion() - 1);
	Session::generateCards(loc);
	loc = nullptr;
	
}

void Session::generateCards(Location * loc) {
	Card * card = new CityCard(loc);
	this->playerDeck->add(card);
	this->playerDeck->incrementRegionCards(loc->getRegion());
	this->infectionDeck->add(card);
	this->cityCards->emplace(loc->getName(), dynamic_cast<CityCard *>(card));
}

void Session::clearLocation()
{
	this->locations->clear();
}

void Session::connectCity(string city1, string city2, bool notify)
{
	connectCity(locations->at(city1), locations->at(city2), notify);
}

void Session::connectCity(Location * city1, Location * city2, bool notify)
{
	City::connect(this->playMap->getPlayMap()->at(city2), this->playMap->getPlayMap()->at(city1), City::REGULAR_CONNECTION);
	if (!notify) {
		Notify(city1->getName() + " is now connected to " + city2->getName());
	}
}

void Session::addPlayer(string name)
{
	this->players->push_back(new Player(name, this->playMap->getOrigin()));
	this->playMap->getOrigin()->setPlayer(this->players->size() - 1, true);
	currentPlayer = 0;
	Notify(name + " is now added as a player");
}

void Session::displayPlayersInfo()
{
	for (auto player : *(this->players)) {
		player->displayInfo();
	}
}

void Session::displayCityInfo()
{
	if (this->playMap->getPlayMap()->size() == 0) {
		cout << "No city defined" << endl;
	}
	else {
		for (auto iterate = this->playMap->getPlayMap()->begin(); iterate != this->playMap->getPlayMap()->end(); ++iterate) {
			iterate->second->displayInfo();
		}
	}
}

Session & Session::getInstance(City * origin)
{
	static Session * instance = new Session(origin);

	return *instance;
}

Session & Session::getInstance()
{
	static Session * instance = new Session();

	return *instance;
}

City * Session::getCity(string name) {
	return this->playMap->getPlayMap()->at(this->locations->at(name));
}

unordered_map<string, Location *> * Session::getLocation() {
	return this->locations;
}

void Session::incrementCurrentPlayer()
{
	currentPlayer = (currentPlayer + 1) % players->size();
}

void Session::move(City * city)
{
	Notify(players->at(currentPlayer)->move(city));
}

void Session::move(CityCard * card)
{
	Notify(players->at(currentPlayer)->move(card));
}

void Session::move(CityCard * card, City * city)
{
	Notify(players->at(currentPlayer)->move(card, city));
}

void Session::build(CityCard * card)
{
	Notify(players->at(currentPlayer)->build(card));
}

void Session::treatDisease(int type)
{
	Notify(players->at(currentPlayer)->treatDisease(type));
}

void Session::shareKnowledge(CityCard * card, Player * player)
{
	Notify(players->at(currentPlayer)->shareKnowledge(card, player));
}

void Session::discoverCure(CityCard * card1, CityCard * card2, CityCard * card3, CityCard * card4, CityCard * card5)
{
	Notify(players->at(currentPlayer)->discoverCure(card1, card2, card3, card4, card5));
}

void Session::consultReference() {
	vector<string> * log = new vector<string>;
	for (auto iterator = Player::reference.getList()->begin(); iterator != Player::reference.getList()->end(); ++iterator) {
		log->push_back((*iterator)->getTitle() + ": " + (*iterator)->getDescription());
	}
	Notify(log);
	log = nullptr;
}

void Session::consultRoleCard() {
	switch (players->at(currentPlayer)->getRole()) {
	case 1:
		Notify(dynamic_cast<ContigencyPlanner *> (players->at(currentPlayer)->getRoleCard())->getDescription());
		break;
	case 2:
		Notify(dynamic_cast<OperationExpert *> (players->at(currentPlayer)->getRoleCard())->getDescription());
		break;
	case 3:
		Notify(dynamic_cast<Dispatcher *> (players->at(currentPlayer)->getRoleCard())->getDescription());
		break;
	case 4:
		Notify(dynamic_cast<QuarantineSpecialist *> (players->at(currentPlayer)->getRoleCard())->getDescription());
		break;
	case 5:
		Notify(dynamic_cast<Researcher *> (players->at(currentPlayer)->getRoleCard())->getDescription());
		break;
	case 6:
		Notify(dynamic_cast<Medic *> (players->at(currentPlayer)->getRoleCard())->getDescription());
		break;
	case 7:
		Notify(dynamic_cast<Scientist *> (players->at(currentPlayer)->getRoleCard())->getDescription());
		break;
	}
}

void Session::addEventCards(EventCard * card)
{
	eventCards->emplace(card->getTitle(), card);
}

EventCard * Session::getEventCard(string card)
{
	return eventCards->at(card);
}

int Session::getNumberOfRegionInPlay() {
	return numberOfRegionsInPlay;
}

int Session::getNumberOfLocations(int region)
{
	return numberOfLocationsPerRegion->at(region -1);
}



