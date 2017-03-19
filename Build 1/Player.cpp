#include "Player.h"

ReferenceCard Player::reference = ReferenceCard();


// Helper method to shuffle the roles. May migrate class in subsequent iteration.
int random(int i)
{
	return std::rand() % i;
}

// Assigns basic values to the player. Shuffles the roles. Eventually, the role assignation portion should be
// given to a factory method that will create subclasses (Medic, Researcher, etc) based on a random seed.
Player::Player(string name, City * origin)
{
	std::srand(unsigned(std::time(0)));
	static int numberOfPlayers;
	++numberOfPlayers;
	static vector<int> array;
	if (numberOfPlayers == 1) {
		for (unsigned i = 1; i < 8; ++i) {
			array.push_back(i);
		}
	}
	random_shuffle(array.begin(), array.end(), random);
	this->playerName = name;
	this->hand = new set<Card *, compareSet>;
	playerId = numberOfPlayers;
	playerRole = array.at(0);

	switch (array.at(0)) {
	case 1:
		roleCard = new ContigencyPlanner();
		break;
	case 2:
		roleCard = new OperationExpert();
		break;
	case 3:
		roleCard = new Dispatcher();
		break;
	case 4:
		roleCard = new QuarantineSpecialist();
		break;
	case 5:
		roleCard = new Researcher();
		break;
	case 6:
		roleCard = new Medic();
		break;
	case 7:
		roleCard = new Scientist();
		break;
	}
	array.erase(array.begin());
	actionPoints = 4;
	pawn = new Pawn(origin);
}

Player::~Player()
{
	delete pawn;
	pawn = nullptr;

	delete hand;
	hand = nullptr;

	delete roleCard;
	roleCard = nullptr;
}

// Here to allow to forcefully set a different city without the move command.
void Player::setLocation(City * city)
{
	this->pawn->setCity(city);
}

// Different default actions a player can have. To be implemented in subsequent interation.
string Player::move(City * city)
{
	if (actionPoints <= 0) {
		return "Insufficient action points";
	}
	if (!this->getCity()->isConnected(city)) {
		return getCity()->getName() + " and " + city->getName() + " aren't connected";
	}
	string cityName = this->getCity()->getLocation()->getName();
	this->getCity()->setPlayer(playerId - 1, false);
	city->setPlayer(playerId - 1, true);
	this->pawn->setCity(city);
	--actionPoints;
	return playerName + " moved from " + cityName + " to city: " + city->getName();
}

string Player::move(CityCard * card)
{
	if (actionPoints <= 0) {
		return "Insufficient action points";
	}
	--actionPoints;
	string cityName = this->getCity()->getLocation()->getName();
	this->getCity()->setPlayer(playerId - 1, false);
	City * city = PlayMap::getInstance()->getPlayMap()->at(card->getLocation());
	city->setPlayer(playerId - 1, true);
	this->pawn->setCity(city);
	playCardFromHand(card);
	string data = playerName + " moved from " + cityName + " to city: " + city->getName();
	city = nullptr;
	return data;
}

string Player::move(CityCard * card, City * city)
{
	if (actionPoints <= 0) {
		return "Insufficient action points";
	}
	if (card->getLocation() != getCity()->getLocation()) {
		return "You need to possess the card of the city you are standing on in order to charter a flight";
	}
	--actionPoints;
	string cityName = this->getCity()->getLocation()->getName();
	this->getCity()->setPlayer(playerId - 1, false);
	city->setPlayer(playerId - 1, true);
	this->pawn->setCity(city);
	playCardFromHand(card);
	return playerName + " chartered a flight to move from " + cityName + " to city: " + city->getName();
}

string Player::build(CityCard * card)
{
	if (actionPoints <= 0) {
		return "Insufficient action points";
	}
	if (getCity()->getLocation() != card->getLocation()) {
		return "You are currently in " + getCity()->getName() + " and need to be in "
			+ card->getLocation()->getName() + " to be able to construct a research center" + 
			" with this card";
	}
	if (City::getResearchCitiesList()->size() == 6) {
		return "Maximum number of research centers (6) reached";
	}
	if (getCity()->getResearchCenter()) {
		return getCity()->getName() + " already contains a research center.";
	}
	--actionPoints;
	getCity()->setResearchCenter(true);
	playCardFromHand(card);
	return "Research center constructed in " + getCity()->getName();

}

string Player::treatDisease(int type)
{
	if (actionPoints <= 0) {
		return "Insufficient action points";
	}
	if (this->getCity()->getDisease(type) <= 0) {
		return this->getCity()->diseaseTranslate(type) + " is absent from " + this->getCity()->getName();
	}
	this->getCity()->decrementDisease(type);
	--actionPoints;
	return this->getCity()->diseaseTranslate(type) + " in " + this->getCity()->getName() + " is now at " + to_string(this->getCity()->getDisease(type));
}

string Player::shareKnowledge(CityCard * card, Player * player)
{
	if (actionPoints <= 0) {
		return "Insufficient action points";
	}
	if (playerId == player->getPlayerId()) {
		return "You can't share knowledge with yourself";
	}
	if (getCity() != player->getCity()) {
		return "You need to be in the same city as the other player to share knowledge";
	}
	if (card->getLocation() != player->getCity()->getLocation()) {
		return "You need to be in the city represented by the card in order to share knowledge of that card";
	}
	if (handContains(card)) {
		hand->erase(card);
		player->getHand()->emplace(card);
		--actionPoints;
		return "Card successfully traded from " + playerName + " to " + player->getPlayerName();
	}
	if (player->handContains(card)) {
		hand->emplace(card);
		player->getHand()->erase(card);
		--actionPoints;
		return "Card successfully traded from " + player->getPlayerName() + " to " + playerName;
	}
	return "Error. Nothing Happened.";
}

string Player::discoverCure(CityCard * card1, CityCard * card2, CityCard * card3, CityCard * card4, CityCard * card5)
{
	if (actionPoints <= 0) {
		return "Insufficient action points";
	}
	if (!getCity()->getResearchCenter()) {
		return "Must be on a research center to be able to cure a disease";
	}
	if (card1->getLocation()->getRegion()
		== card2->getLocation()->getRegion()
		== card3->getLocation()->getRegion()
		== card4->getLocation()->getRegion()
		== card5->getLocation()->getRegion()) {
		--actionPoints;
		playCardFromHand(card1);
		playCardFromHand(card2);
		playCardFromHand(card3);
		playCardFromHand(card4);
		playCardFromHand(card5);
		GameStateVar::getInstance().setCure(card1->getLocation()->getRegion());
		return getCity()->diseaseTranslate(card1->getLocation()->getRegion()) + " cured!";
	}
	else {
		return "Must select 5 cards of the same color to be able to cure a disease";
	}
}


// Used to 
void Player::displayInfo()
{	
	cout << "Player #" << playerId << endl << endl
		<< "Player name: " << playerName << endl
		<< "Number of actions left: " << actionPoints << endl
		<< "Player role: " << getPlayerRole() << endl
		<< "Reference cards, role card and player cards: to be implemented by teammates." << endl;
	pawn->displayInfo();
	cout << endl << endl;

}

void Player::draw(Card * card)
{
	if (dynamic_cast<CityCard *>(card) != nullptr) {
		hand->emplace(dynamic_cast<CityCard *>(card));
	}
	else if (dynamic_cast<EventCard *>(card) != nullptr) {
		hand->emplace(dynamic_cast<EventCard *>(card));
	}
}

string Player::getPlayerName() {
	return this->playerName;
}

string Player::getPlayerRole() {
	switch (this->playerRole) {
	case 1:
		return "Contingency planner";
	case 2:
		return "Operation expert";
	case 3:
		return "Dispatcher";
	case 4:
		return "Quarantine specialist";
	case 5:
		return "Researcher";
	case 6:
		return "Medic";
	case 7:
		return "Scientist";
	default:
		return "";
	}
}

City * Player::getCity() {
	return this->pawn->getCity();
}

set<Card*, compareSet>* Player::getHand()
{
	return hand;
}

int Player::getActionPoints() {
	return this->actionPoints;
}

int Player::getPlayerId()
{
	return this->playerId;
}

bool Player::handContains(Card * card)
{
	if (dynamic_cast<CityCard *>(card) != nullptr) {
		return hand->find(dynamic_cast<CityCard *>(card)) != hand->end();
	}
	else if (dynamic_cast<EventCard *>(card) != nullptr) {
		return hand->find(dynamic_cast<EventCard *>(card)) != hand->end();
	}
	return false;
}

void Player::playCardFromHand(Card * card) {
	hand->erase(card);
	Session::getInstance().getPlayerDeck()->toDiscard(card);
}

int Player::getRole()
{
	return playerRole;
}

RoleCard * Player::getRoleCard()
{
	return roleCard;
}

void Player::refreshActions()
{
	actionPoints = 4;
}



