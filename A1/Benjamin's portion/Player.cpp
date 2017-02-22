#include "Player.h"

// Helper method to shuffle the roles. May migrate class in subsequent iteration.
int random(int i)
{
	return std::rand() % i;
}

// Assigns basic values to the player. Shuffles the roles. Eventually, the role assignation portion should be
// given to a factory method that will create subclasses (Medic, Researcher, etc) based on a random seed.
Player::Player(string name, string color, const City & origin)
{
	std::srand(unsigned(std::time(0)));
	static int numberOfPlayers = 0;
	++numberOfPlayers;
	static vector<int> array;
	if (numberOfPlayers == 1) {
		for (unsigned i = 1; i < 8; ++i) {
			array.push_back(i);
		}
	}
	random_shuffle(array.begin(), array.end(), random);
	this->playerName = name;
	playerId = numberOfPlayers;
	playerRole = array.at(0);
	array.erase(array.begin());
	actionPoints = 4;
	hand = new map<pair<int, string>, Card>;
	pawn = new Pawn(color, origin);
}

Player::~Player()
{
	delete pawn;
	pawn = NULL;
	delete hand;
	hand = NULL;
}

// Different default actions a player can have. To be implemented in subsequent interation.
void Player::move(const City & city)
{
}

void Player::move(const Card & card)
{
}

void Player::move(const Card & card, const City & city)
{
}

void Player::build(const Card & card)
{
}

void Player::treatDisease()
{
}

void Player::shareKnowledge()
{
}

void Player::discoverCure(const Card & card1, const Card & card2, const Card & card3, const Card & card4, const Card & card5)
{
}


// Used to 
void Player::displayInfo()
{
	string temp;

	switch (playerRole) {
	case 1:
		temp = "Contingency planner";
		break;
	case 2:
		temp = "Operation expert";
		break;
	case 3:
		temp = "Dispatcher";
		break;
	case 4:
		temp = "Quarantine specialist";
		break;
	case 5:
		temp = "Researcher";
		break;
	case 6:
		temp = "Medic";
		break;
	case 7:
		temp = "Scientist";
		break;
	default:
		temp = "";
		break;
	}
	cout << "Player #" << playerId << endl << endl
		<< "Player name: " << playerName << endl
		<< "Number of actions left: " << actionPoints << endl
		<< "Player role: " << temp << endl
		<< "Reference cards, role card and player cards: to be implemented by teammates." << endl;
	pawn->displayInfo();
	cout << endl << endl;

}

