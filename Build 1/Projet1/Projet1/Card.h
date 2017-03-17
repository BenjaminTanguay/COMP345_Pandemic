#pragma once
#include <string>

using namespace std;

class Card
{
public:
	Card();
	virtual ~Card();

	virtual void read() = 0;
	virtual string getTitle() = 0;
};

