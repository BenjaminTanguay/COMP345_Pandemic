#include "OneQuietNight.h"



OneQuietNight::OneQuietNight()
{
}


OneQuietNight::~OneQuietNight()
{
}


void OneQuietNight::execute() {
	GameStateVar::getInstance()->setOneQuietNight(true);
}