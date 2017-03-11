#pragma once
class Card
{
public:
	Card();
	virtual ~Card();

	virtual void read() = 0;
};

