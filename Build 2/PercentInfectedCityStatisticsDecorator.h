#pragma once
#include "AbstractStatisticsDecorator.h"
#include <iomanip> // setprecision
#include <sstream> // stringstream

class PercentInfectedCityStatisticsDecorator :
	public AbstractStatisticsDecorator
{

public:

	PercentInfectedCityStatisticsDecorator(Statistics * statistics);
	~PercentInfectedCityStatisticsDecorator();

	virtual int getNumberOfLines();
	virtual int getStatistics(int line);
};

