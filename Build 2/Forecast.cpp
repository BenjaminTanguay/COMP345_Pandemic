#include "Forecast.h"


Forecast::Forecast(vector<CityCard*>* forecast): forecast(forecast)
{
}

Forecast::~Forecast()
{
	delete forecast;
	forecast = nullptr;
}

void Forecast::execute()
{
	Session::getInstance()->getInfectionDeck()->putForeCast(forecast);
}
