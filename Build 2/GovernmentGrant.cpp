#include "GovernmentGrant.h"


GovernmentGrant::GovernmentGrant(City * city):city(city)
{
}

GovernmentGrant::~GovernmentGrant()
{
}

void GovernmentGrant::execute()
{
	city->setResearchCenter(true);
}
