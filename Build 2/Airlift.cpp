#include "Airlift.h"

Airlift::Airlift(Player * player, City * city):player(player), city(city)
{
}

Airlift::~Airlift()
{
}

void Airlift::execute()
{
	vector<Player *> * vec = Session::getInstance()->getPlayers();
	unsigned playerPosition = distance(vec->begin(), find(vec->begin(), vec->end(), player));
	this->player->getCity()->setPlayer(playerPosition, false);
	this->player->setLocation(city);
	city->setPlayer(playerPosition, true);
	vec = nullptr;
}
