#pragma once

#include "Action.h"
#include "ReferenceCard.h"
#include "RoleCard.h"
#include "Player.h"

class Cdc {
	private:
		int numP;
		const int maxP = 4;
		Player plist[];

	public:
		void setNumP(int i) {
			if (i < maxP)
				this->numP = i + 1;
			else
				this->numP = 2;
			this->plist[numP];
		}

		int getNumP() {
			return this->numP;
		}

		void setPList(int i, Player p) {
			this->plist[i] = p;
		}

		Player getPList(int i) {
			return this->plist[i];
		}

		bool costAction(Action& action);

		void doAction();

		bool costRole();

		void doRole();

		bool setup();

		void run();

};