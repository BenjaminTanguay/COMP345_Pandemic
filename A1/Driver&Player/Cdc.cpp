#include <iostream>

#include "Cdc.h"

bool costAction(Action& action) {

	Action* a = &action;
	DriveFerry* a1 = dynamic_cast<DriveFerry*>(a);
	DirectFlight* a2 = dynamic_cast<DirectFlight*>(a);
	CharterFlight* a3 = dynamic_cast<CharterFlight*>(a);
	ShuttleFlight* a4 = dynamic_cast<ShuttleFlight*>(a);
	BuildResearchStation* a5 = dynamic_cast<BuildResearchStation*>(a);
	TreatDisease* a6 = dynamic_cast<TreatDisease*>(a);
	ShareKnowledge* a7 = dynamic_cast<ShareKnowledge*>(a);
	DiscoverCure* a8 = dynamic_cast<DiscoverCure*>(a);

	if (a1 != NULL) {
		return true;
	}

	if (a2 != NULL) {
		return true;
	}

	if (a3 != NULL) {
		return true;
	}

	if (a4 != NULL) {
		return true;
	}

	if (a5 != NULL) {
		return true;
	}

	if (a6 != NULL) {
		return true;
	}

	if (a7 != NULL) {
		return true;
	}

	if (a8 != NULL) {
		return true;
	}

}

void doAction() {

}

bool costRole() {}

void doRole() {}