#pragma once

#include "Action.h"
#include "ReferenceCard.h"
#include "RoleCard.h"
#include "Player.h"

class Cdc {
	private:
		int numP;
		const int maxP = 4;
		Player pList[4];

	public:
		Cdc() {};

		void setNumP(int ii) {
			if (ii <= this->maxP && ii > 0)
				this->numP = ii;
			else
				this->numP = 2;

			this->pList[this->numP];

			std::cout << this->numP <<" total players? Splendid!" << std::endl;

			for (int j = 0; j < this->numP; j++) {
				this->pList[j] = Player::Player();
			}
		}

		int getNumP() {
			return this->numP;
		}

		void setPList(int i, Player p) {
			this->pList[i] = p;
		}

		Player getPList(int i) {
			return this->pList[i];
		}

		bool costAction(Action& action);

		//void doAction();

		bool costRole(RoleCard& role);

		//void doRole();

		bool setup();

		void run();

};