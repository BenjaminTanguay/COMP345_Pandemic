#include "AbstractStatisticsDecorator.h"




AbstractStatisticsDecorator::AbstractStatisticsDecorator(Statistics * statistics)
{
	this->statistics = statistics;
}

AbstractStatisticsDecorator::~AbstractStatisticsDecorator()
{
	delete statistics;
	statistics = nullptr;
}



