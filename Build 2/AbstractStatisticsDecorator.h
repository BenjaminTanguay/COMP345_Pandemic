#pragma once
#include "Statistics.h"
class AbstractStatisticsDecorator :
	public Statistics
{
protected:
	Statistics * statistics;

public:
	AbstractStatisticsDecorator(Statistics * statistics);
	~AbstractStatisticsDecorator();

	virtual int getNumberOfLines() = 0;
	virtual int getStatistics(int line) = 0;

};

