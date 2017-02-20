#include "Player.h"



Player::Player(string name, string color, const City & origin)
{
	static int numberOfPlayers = 0;
	++numberOfPlayers;
	static int array[7];
	if (numberOfPlayers == 1) {
		for (int i = 0; i < 7; ++i) {
			array[i] = i + 1;
		}
		shuffle(array, 7);
	}
	this->playerName = name;
	playerId = numberOfPlayers;
	playerRole = array[playerId - 1];
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
		<< "Player role: " << temp << endl;
	pawn->displayInfo();
	cout << endl << endl;

}




void Player::shuffle(int array[], int length)
{
	int temp;
	for (int i = 0; i < length - 2; ++i) {
		temp = array[i];
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(i, length - 1);
		int j = distribution(generator);
		array[i] = array[j];
		array[j] = temp;
	}
}