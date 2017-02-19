#pragma once

#include <vector>
#include <iostream>

#include "Action.h"

class ReferenceCard {
	private:
		std::vector<Action> list;

	public:
		ReferenceCard() {
			this->list.push_back(DriveFerry());
			this->list.push_back(DirectFlight());
			this->list.push_back(CharterFlight());
			this->list.push_back(ShuttleFlight());
			this->list.push_back(BuildResearchStation());
			this->list.push_back(TreatDisease());
			this->list.push_back(ShareKnowledge());
			this->list.push_back(DiscoverCure());
			
		}

		void viewList() {
			if (list.size() < 1)
				std::cout << "No Actions..." << std::endl;

			else 
				for (std::vector<Action>::iterator it = list.begin(); it < list.end(); it++) {
					Action action = *it;
					std::cout << "Reference Card" << &action.getTitle() << &action.getDescription() << std::endl;
				}
					
		}

};