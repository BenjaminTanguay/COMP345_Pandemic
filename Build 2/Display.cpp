#include "Display.h"
#include "Controller.h"



Display::Display()
{
	Session::getInstance().Attach(this);
	stats = new PercentInfectedCityStatisticsDecorator(new Statistics);
	stats->Attach(this);




	numberOfDiseaseCubes[1] = "Disease cubes left:";
	numberOfDiseaseCubes[2] = "Blue";
	numberOfDiseaseCubes[3] = "Yellow";
	numberOfDiseaseCubes[4] = "Black";
	numberOfDiseaseCubes[5] = "Red";
	numberOfDiseaseCubes[0] = "";


	
	cureState[1] = "Cure status:";
	cureState[2] = "Blue";
	cureState[3] = "Yellow";
	cureState[4] = "Black";
	cureState[5] = "Red";
	cureState[0] = "";


	
	gameStatus[1] = "Game status:";
	gameStatus[2] = "Infection rate";
	gameStatus[3] = "Next infection increase";
	gameStatus[4] = "Outbreaks left before loss";
	gameStatus[5] = "Cards left in the deck";
	gameStatus[0] = "";

}

Display::~Display()
{
	Session::getInstance().Detach(this);
	stats->Detach(this);
	delete stats;
	stats = nullptr;
}

int Display::cityLines() {
	int maxLines = 0;
	for (auto iterate = Session::getInstance().getPlayMap()->begin(); iterate != Session::getInstance().getPlayMap()->end(); ++iterate) {
		int lines = 5;
		lines += iterate->second->getConnections()->size();
		if (lines > maxLines) {
			maxLines = lines;
		}
	}
	return maxLines;
}

int Display::printPlayer(Player * player, int currentLine, int indexOfPlayer) {

	int boxSize = 20;
	switch (currentLine) {
	case 0:
		switch (indexOfPlayer) {
		case 0:
			ConsoleFormat::setColor(dgreen, white);
			break;
		case 1:
			ConsoleFormat::setColor(dred, white);
			break;
		case 2:
			ConsoleFormat::setColor(white, black);
			break;
		case 3:
			ConsoleFormat::setColor(teal, black);
			break;
		}
		if (indexOfPlayer == Session::getInstance().getCurrentPlayer()) {
			return ConsoleFormat::makeBox(boxSize, "->  " + player->getPlayerName());
		}
		else {
			return ConsoleFormat::makeBox(boxSize, player->getPlayerName());
		}

		
	case 1:
		ConsoleFormat::setColor(lgrey, black);
		return ConsoleFormat::makeBox(boxSize, player->getPlayerRole());
	case 2:
		ConsoleFormat::setColor(lgrey, black);
		return ConsoleFormat::makeBox(boxSize, "Actions: " + to_string(player->getActionPoints()));
	case 10:
		ConsoleFormat::setColor(lgrey, black);
		return ConsoleFormat::makeBox(boxSize, player->getCity()->getLocation()->getName());
	}
	return 0;
}

int Display::printCity(City * city, int currentLine, int maxNumberOfLines, vector<string> * cityConnectionNames) {
	int boxLength = 24;
	string data = "";
	vector<string> * cityDiseaseNumber = new vector<string>;

	switch (currentLine) {
	case 0:
		ConsoleFormat::setColor(city->getLocation()->getRegion());
		return ConsoleFormat::makeBox(boxLength - 4, city->getLocation()->getName());
	case 1:
		for (int i = 0; i < Session::getInstance().getNumberOfRegionInPlay(); ++i) {
			cityDiseaseNumber->push_back(to_string(city->getDisease(i + 1)));
		}
		return ConsoleFormat::printMultipleColorBoxWithData(boxLength, Session::getInstance().getNumberOfRegionInPlay(), cityDiseaseNumber, ConsoleFormat::region);
		cityDiseaseNumber = nullptr;
	case 2:
		ConsoleFormat::setColor(lgrey, black);
		if (city->getResearchCenter()) {
			data = "Research center: Yes";
		}
		else {
			data = "Research center:  No";
		}
		return ConsoleFormat::makeBox(boxLength - 4, data);
	case 3: 
		ConsoleFormat::setColor(lgrey, black);
		return ConsoleFormat::makeBox(boxLength - 4, "Connections:");
	case 4:
		ConsoleFormat::setColor(lgrey, black);
		if (cityConnectionNames->size() < 1) {
			return ConsoleFormat::makeBox(boxLength - 4, "No connection");
		}
		else {
			return ConsoleFormat::makeBox(boxLength - 4, cityConnectionNames->at(0));
		}
	default:
		break;
	}
	if (currentLine != maxNumberOfLines - 1) {
		ConsoleFormat::setColor(lgrey, black);
		if (currentLine - 4 < static_cast<int>(cityConnectionNames->size())) {
			return ConsoleFormat::makeBox(boxLength - 4, cityConnectionNames->at(currentLine - 4));
		}
		else {
			return ConsoleFormat::makeBox(boxLength - 4, "");
		}
	}
	else {
		
		int blockLength = 0;
		switch (city->getPlayer()) {
		default:
			ConsoleFormat::setColor(lgrey, black);
			return ConsoleFormat::makeBox(boxLength - 4, "");
		case 1:
			return ConsoleFormat::blockColor(city, 20);
		case 2:
			return ConsoleFormat::blockColor(city, 8);
		case 3:
			return ConsoleFormat::blockColor(city, 4);
		case 4:
			return ConsoleFormat::blockColor(city, 2);
		}
	}
}

int Display::cityWidget() {
	int lines = cityLines();
	int columns = 9;
	int numberOfCities = Session::getInstance().getPlayMap()->size();
	int row = (numberOfCities / columns);
	if (numberOfCities != columns) {
		++row;
	}
	int lineLength;
	int separator = 5;
	vector<City *> * cities = new vector<City *>;
	for (auto iterate = Session::getInstance().getPlayMap()->begin(); iterate != Session::getInstance().getPlayMap()->end(); ++iterate) {
		cities->push_back(iterate->second);
	}

	for (int currentRow = 0; currentRow < row; ++currentRow) {
		ConsoleFormat::printEmptyLineWall();
		for (int currentLine = 0; currentLine < lines; ++currentLine) {
			lineLength = ConsoleFormat::printWall();
			for (int currentColumn = 0; (currentColumn < columns && currentRow*columns + currentColumn < static_cast<int>(cities->size())); ++currentColumn) {

				// NEED TO REWORK THIS PART. The efficiency is ridiculous!!

				vector<string> * cityConnectionNames = new vector<string>;
				for (auto iterate = cities->at(currentRow * columns + currentColumn)->getConnections()->begin(); iterate != cities->at(currentRow * columns + currentColumn)->getConnections()->end(); ++iterate) {
					cityConnectionNames->push_back(iterate->second->getLocation()->getName());
				}



				lineLength += printCity(cities->at(currentRow * columns + currentColumn), currentLine, lines, cityConnectionNames);
				delete cityConnectionNames;
				cityConnectionNames = nullptr;
				ConsoleFormat::setColor(black, white);
				if (numberOfCities == columns && currentColumn < columns - 1) {
					cout << ConsoleFormat::emptySpaces(separator);
					lineLength += separator;
				}
				else if (numberOfCities < columns && currentColumn < numberOfCities - 1) {
					cout << ConsoleFormat::emptySpaces(separator);
					lineLength += separator;
				}
				else if ((currentColumn < columns - 1 && currentRow < row - 1) || (currentColumn + currentRow * columns < numberOfCities - 1 && currentRow == (row - 1))) {
					cout << ConsoleFormat::emptySpaces(separator);
					lineLength += separator;
				}
				else {
					ConsoleFormat::printRightWall(lineLength);
				}
			}
		}
	}
	ConsoleFormat::printEmptyLineWall();
	ConsoleFormat::printLine();

	int numberOfLines = 0;

	if (cities->size() == 0) {
		numberOfLines = 4;
	}
	else {
		numberOfLines = (++lines)*(++row) + 1 + (++row);
	}

	delete cities;
	cities = nullptr;

	return numberOfLines;
}



void Display::Update()
{
	int verticalLines = mainScreen();
	verticalLines += ConsoleFormat::printEmptyLineWall();
	completeBottomWidget(verticalLines);
}

void Display::Update(string message)
{
	Session::getInstance().getLog()->stringToLog("");
	int verticalLines = mainScreen();
	verticalLines += ConsoleFormat::printEmptyLineWall();
	verticalLines += ConsoleFormat::printLineOfText(message);
	completeBottomWidget(verticalLines);
}

void Display::Update(vector<string>* log)
{
	Session::getInstance().getLog()->stringToLog("");
	int verticalLines = mainScreen();
	verticalLines += ConsoleFormat::printEmptyLineWall();
	for (int i = 0; i < log->size(); ++i) {
		verticalLines += ConsoleFormat::printLineOfText(log->at(i));
	}
	completeBottomWidget(verticalLines);
	delete log;
	log = nullptr;
}

int Display::topWidget() {
	int separation;
	vector<vector<Card *> *> * cards = new vector<vector<Card *> *>;
	for (unsigned i = 0; i < Session::getInstance().getPlayers()->size(); ++i) {
		cards->push_back(new vector<Card *>);
		for (auto iterate = Session::getInstance().getPlayers()->at(i)->getHand()->begin(); iterate != Session::getInstance().getPlayers()->at(i)->getHand()->end(); ++iterate) {
			if (dynamic_cast<CityCard *>(*iterate) != nullptr) {
				cards->at(i)->push_back(dynamic_cast<CityCard *>(*iterate));
			}
			if (dynamic_cast<EventCard *>(*iterate) != nullptr) {
				cards->at(i)->push_back(dynamic_cast<EventCard *>(*iterate));
			}
		}
	}


	switch (Session::getInstance().getPlayers()->size()) {
	case 1:
		separation = 30;
		break;
	case 2:
		separation = 19;
		break;
	case 3:
		separation = 12;
		break;
	case 4:
		separation = 7;
		break;
	default:
		separation = 86;
		break;
	}
	
	ConsoleFormat::printLine();
	ConsoleFormat::printEmptyLineWall();

	//setw(separation);
	int lineLength = 0;
	for (int i = 0; i < 11; ++i) {
		lineLength = ConsoleFormat::printWall();
		ConsoleFormat::setColor(lgrey, black);

		int temp;
		switch (i - 1) {
		case 1:
			temp = GameStateVar::getInstance().getBlue();
			break;
		case 2:
			temp = GameStateVar::getInstance().getYellow();
			break;
		case 3:
			temp = GameStateVar::getInstance().getBlack();
			break;
		case 4:
			temp = GameStateVar::getInstance().getRed();
			break;
		default:
			temp = -1;
			break;
		}
		string data = temp == -1 ? "" : to_string(temp);
		if (i > 5) {
			lineLength += ConsoleFormat::makeBox(22, "");
		}
		else {
			lineLength += ConsoleFormat::makeBox(22, numberOfDiseaseCubes[i], data, 2);
		}
		
		
		lineLength += ConsoleFormat::printSeparation(separation);
		
		int region = i - 1;
		if (region > 0 && region < 5) {
			if (GameStateVar::getInstance().getEradicated(region)) {
				data = "Eradicated";
			}
			else if (GameStateVar::getInstance().getCure(region)) {
				data = "Cured";
			}
			else {
				data = "Not found";
			}
		}
		
		if (i > 5) {
			lineLength += ConsoleFormat::makeBox(23, "");
		}
		else {
			lineLength += ConsoleFormat::makeBox(15, cureState[i], data, 10);
		}

		lineLength += ConsoleFormat::printSeparation(separation);

		switch (i - 1) {
		case 1:
			data = to_string(GameStateVar::getInstance().getInfectionRate());
			break;
		case 2:
			data = to_string(GameStateVar::getInstance().infectionIncreaseIn());
			break;
		case 3:
			data = to_string(8 - GameStateVar::getInstance().getEclosionCounter());
			break;
		case 4:
			data = to_string(Session::getInstance().getPlayerDeck()->getSize());
			break;
		default:
			data = "";
		}

		if (i > 5) {
			lineLength += ConsoleFormat::makeBox(29, "");
		}
		else {
			lineLength += ConsoleFormat::makeBox(29, gameStatus[i], data, 2);
		}

		

		if (Session::getInstance().getPlayers()->size() == 0) {
			ConsoleFormat::printRightWall(lineLength);
			continue;
		}

		lineLength += ConsoleFormat::printSeparation(separation);

		if (i > stats->getNumberOfLines() - 1) {
			lineLength += ConsoleFormat::makeBox(20, "");
		}
		else {
			lineLength += stats->getStatistics(i);
		}

		lineLength += ConsoleFormat::printSeparation(separation);

		for (unsigned j = 0; j < Session::getInstance().getPlayers()->size(); ++j) {
			if (i < 3 || i == 10) {
				lineLength += printPlayer(Session::getInstance().getPlayers()->at(j), i, j);
			}
			else if (i > 10) {
				ConsoleFormat::setColor(lgrey, black);
				lineLength += ConsoleFormat::makeBox(20, "");
			}
			else {
				if (cards->at(j)->size() < static_cast<unsigned>(i - 2)) {
					ConsoleFormat::setColor(lgrey, black);
					lineLength += ConsoleFormat::makeBox(20, "");
				}
				else if (dynamic_cast<CityCard *>(cards->at(j)->at(i - 3)) != nullptr) {
					ConsoleFormat::setColor(dynamic_cast<CityCard *>(cards->at(j)->at(i - 3))->getLocation()->getRegion());
					lineLength += ConsoleFormat::makeBox(20, dynamic_cast<CityCard *>(cards->at(j)->at(i - 3))->getTitle());
				}
				else if (dynamic_cast<EventCard *>(cards->at(j)->at(i-3)) != nullptr) {
					ConsoleFormat::setColor(brown, white);
					lineLength += ConsoleFormat::makeBox(20, dynamic_cast<EventCard *>(cards->at(j)->at(i - 3))->getTitle());
				}

			}
			
			if (j < Session::getInstance().getPlayers()->size() - 1) {
				lineLength += ConsoleFormat::printSeparation(separation);
			}
		}
		ConsoleFormat::printRightWall(lineLength);
	}
	ConsoleFormat::printEmptyLineWall();
	ConsoleFormat::printLine();

	return 15;
}

int Display::mainScreen() {
	int lineCount = 0;
	lineCount = this->topWidget();
	lineCount = this->cityWidget();
	return lineCount;
}

void Display::completeBottomWidget(int numberOfLines) {
	int maxNumberOfLinesInScreen = 64;
	if (numberOfLines >= maxNumberOfLinesInScreen) {
		ConsoleFormat::printEmptyLineWall();
		ConsoleFormat::printLine();
	}
	else {
		for (int i = 0; i < maxNumberOfLinesInScreen - 1 - numberOfLines; ++i) {
			ConsoleFormat::printEmptyLineWall();
		}
		ConsoleFormat::printLine();
	}
	system("pause");
}

int Display::listCities(vector<City*>* cities, City * city)
{
	int columns = 9;
	int numberOfCities = PlayMap::getInstance()->getPlayMap()->size() - 1;
	int row = (numberOfCities / columns);
	if (numberOfCities != columns) {
		++row;
	}
	int lineLength;
	int lineCount = 0;
	int separator = 5;
	for (auto iterate = PlayMap::getInstance()->getPlayMap()->begin(); iterate != PlayMap::getInstance()->getPlayMap()->end(); ++iterate) {
		if (iterate->second == city) {
			continue;
		}
		else {
			cities->push_back(iterate->second);
		}
	}
	for (int currentRow = 0; currentRow < row; ++currentRow) {
		lineLength = 0;
		++lineCount;
		lineLength += ConsoleFormat::printWall();

		for (int currentColumn = 0; (currentColumn < columns && currentRow*columns + currentColumn < static_cast<int>(cities->size())); ++currentColumn) {
			int cityNumber = currentRow*columns + currentColumn;
			lineLength += ConsoleFormat::makeBox(20, to_string(cityNumber + 1) + ". " + cities->at(cityNumber)->getName());

			if (numberOfCities == columns && currentColumn < columns - 1) {
				cout << ConsoleFormat::emptySpaces(separator);
				lineLength += separator;
			}
			else if (numberOfCities < columns && currentColumn < numberOfCities - 1) {
				cout << ConsoleFormat::emptySpaces(separator);
				lineLength += separator;
			}
			else if ((currentColumn < columns - 1 && currentRow < row - 1) || (currentColumn + currentRow * columns < numberOfCities - 1 && currentRow == (row - 1))) {
				cout << ConsoleFormat::emptySpaces(separator);
				lineLength += separator;
			}
			else {
				ConsoleFormat::printRightWall(lineLength);
			}
		}
	}
	return lineCount;
}

int Display::cityChoice(Player * player, string question, vector<City *> * listOfCities)
{
	int verticalLines = mainScreen();
	verticalLines += ConsoleFormat::printEmptyLineWall();
	verticalLines += ConsoleFormat::printLineOfText(question);
	listCities(listOfCities, player->getCity());
	completeBottomWidget(verticalLines);
	return Controller::inputCheck(1, listOfCities->size()) - 1;
}


