#include <iostream>
//#include <Windows.h>

#include "Cdc.h"

void Cdc::run() {
	this->setup();
}

int main() {
	Cdc cdc;
	cdc.run();
}

bool Cdc::setup() {

	std::cout << "How Many Players will be joining you?" << std::endl;
	int *n;
	std::cin >> *n;
	this->setNumP(*n);

	for (int i = 1; i <= this->getNumP; i++) {
		if(i == 1){
			std::cout << "Player " << i << ", which role would you like to play?" << std::endl;
			std::cout << "Anna, the Scientist perhaps?" << std::endl;
			this->setPList(i - 1, Player("Anna"));
			this->getPList(i - 1).setRole(Scientist());
		}

		if (i > 1) {
			std::cout << "Player " << i << ", which role would you like to play?" << std::endl;
			std::cout << "Mary, the Researcher perhaps?" << std::endl;
			this->setPList(i - 1, Player("Mary"));
			this->getPList(i - 1).setRole(Researcher());
		}

		if (i > 2) {
			std::cout << "Player " << i << ", which role would you like to play?" << std::endl;
			std::cout << "Greg, the quarantine Specialist perhaps?" << std::endl;
			this->setPList(i - 1, Player("Greg"));
			this->getPList(i - 1).setRole(QuarantineSpecialist());
		}
		if (i > 3) {
			std::cout << "Player " << i << ", which role would you like to play?" << std::endl;
			std::cout << "Oliver, the contingency Planner perhaps?" << std::endl;
			this->setPList(i - 1, Player("Oliver"));
			this->getPList(i - 1).setRole(ContigencyPlanner());
		}
		getPList(i - 1).setRefCard(ReferenceCard());
	}

}

bool costAction(Action& action) {//this method verifies if there is an action that can be done

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

	else
		return false;

}

void doAction() {}

bool costRole(RoleCard& role) { //this method verifies if there is a role that can be played
	
	RoleCard* r = &role;
	ContigencyPlanner* r1 = dynamic_cast<ContigencyPlanner*>(r);
	OperationExpert* r2 = dynamic_cast<OperationExpert*>(r);
	Dispatcher* r3 = dynamic_cast<Dispatcher*>(r);
	QuarantineSpecialist* r4 = dynamic_cast<QuarantineSpecialist*>(r);
	Researcher* r5 = dynamic_cast<Researcher*>(r);
	Medic* r6 = dynamic_cast<Medic*>(r);
	Scientist* r7 = dynamic_cast<Scientist*>(r);
	
	if (r1 = NULL) {
		return true;
	}
	
	if (r2 = NULL) {
		return true;
	}

	if (r3 = NULL) {
		return true;
	}

	if (r4 = NULL) {
		return true;
	}

	if (r5 = NULL) {
		return true;
	}

	if (r6= NULL) {
		return true;
	}

	if (r7 = NULL) {
		return true;
	}

	else
		return false;

}

void doRole() {}

