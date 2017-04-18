#include "PercentInfectedCityStatisticsDecorator.h"






PercentInfectedCityStatisticsDecorator::PercentInfectedCityStatisticsDecorator(Statistics * statistics):AbstractStatisticsDecorator(statistics)
{
}

PercentInfectedCityStatisticsDecorator::~PercentInfectedCityStatisticsDecorator()
{
	delete statistics;
	statistics = nullptr;
}

// Adds the added line to the lineCount. The idea is that we need to know
// how many lines are printed through decorator so that we know when we need
// to print blank lines if needed.
int PercentInfectedCityStatisticsDecorator::getNumberOfLines() 
{
	return this->statistics->getNumberOfLines() + 1;
}


// Adds the percentage of infected city to the statistics block.
int PercentInfectedCityStatisticsDecorator::getStatistics(int line)
{
	if (line < this->statistics->getNumberOfLines()) {
		this->statistics->getStatistics(line);
	}
	else if (line == statistics->getNumberOfLines()) {
		ConsoleFormat::setColor(ConsoleFormat::lgrey, ConsoleFormat::black);
		stringstream ss;
		ss << std::fixed << std::setprecision(1) << ((double)Statistics::getNumberOfDiseasedCity() / (double)Session::getInstance()->getPlayMap()->size()) * 100;
		std::string percentage = ss.str();
		ConsoleFormat::makeBox(16, "Infected:", percentage + "%", 6);
	}

	return 24;
}
