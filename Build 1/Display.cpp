#include "Display.h"



Display::Display()
{
	Session::getInstance().Attach(this);




	numberOfDiseaseCubes[1] = "Disease cubes left:";
	numberOfDiseaseCubes[2] = "Blue";
	numberOfDiseaseCubes[3] = "Yellow";
	numberOfDiseaseCubes[4] = "Black";
	numberOfDiseaseCubes[5] = "Red";
	numberOfDiseaseCubes[0] = "";
	numberOfDiseaseCubes[6] = "";
	numberOfDiseaseCubes[7] = "";
	numberOfDiseaseCubes[8] = "";
	numberOfDiseaseCubes[9] = "";
	numberOfDiseaseCubes[10] = "";
	numberOfDiseaseCubes[11] = "";

	
	cureState[1] = "Cure status:";
	cureState[2] = "Blue";
	cureState[3] = "Yellow";
	cureState[4] = "Black";
	cureState[5] = "Red";
	cureState[0] = "";
	cureState[6] = "";
	cureState[7] = "";
	cureState[8] = "";
	cureState[9] = "";
	cureState[10] = "";
	cureState[11] = "";

	
	gameStatus[1] = "Game status:";
	gameStatus[2] = "Infection rate";
	gameStatus[3] = "Next infection increase";
	gameStatus[4] = "Outbreaks left before loss";
	gameStatus[5] = "Cards left in the deck";
	gameStatus[0] = "";
	gameStatus[6] = "";
	gameStatus[7] = "";
	gameStatus[8] = "";
	gameStatus[9] = "";
	gameStatus[10] = "";
	gameStatus[11] = "";
}


Display::~Display()
{
	Session::getInstance().Detach(this);
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
	
	switch (currentLine) {
	case 0:
		ConsoleFormat::setColor(city->getLocation()->getRegion());
		return ConsoleFormat::makeBox(boxLength - 4, city->getLocation()->getName());
	case 1:
		ConsoleFormat::setColor(blue, white);
		ConsoleFormat::makeBox(2, to_string(city->getBlueDisease()));
		ConsoleFormat::setColor(yellow, black);
		ConsoleFormat::makeBox(2, to_string(city->getYellowDisease()));
		ConsoleFormat::setColor(black, white);
		ConsoleFormat::makeBox(2, to_string(city->getBlackDisease()));
		ConsoleFormat::setColor(red, white);
		ConsoleFormat::makeBox(2, to_string(city->getRedDisease()));
		return boxLength;
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

void Display::welcomeSceen()
{
	while (true) {
		ConsoleFormat::printLineOfText("Welcome to Pandemic!");
		ConsoleFormat::printLineOfText("1. New Game");
		ConsoleFormat::printLineOfText("2. Map Editor");
		ConsoleFormat::printLineOfText("3. Exit program");
		ConsoleFormat::printEmptyLineWall();
		ConsoleFormat::printEmptyLineWall();

		switch (inputCheck(1, 3)) {
		case 1:
			newGameScreen();
			break;
		case 2:
			mapEditorGeneralDialog();
			break;
		case 3:
			return;
		default:
			ConsoleFormat::printLineOfText("Invalid input. Try again!");
			ConsoleFormat::printEmptyLineWall();
			ConsoleFormat::printEmptyLineWall();
			break;
		}
	}
}

void Display::newGameScreen()
{


	while (true) {
		ConsoleFormat::printLineOfText("How would you like to play your game?");
		ConsoleFormat::printLineOfText("1. Default game");
		ConsoleFormat::printLineOfText("2. Load map from save file");
		ConsoleFormat::printLineOfText("3. Load game from save file");
		ConsoleFormat::printLineOfText("4. Back");
		ConsoleFormat::printEmptyLineWall();
		ConsoleFormat::printEmptyLineWall();

		switch (inputCheck(1, 4)) {
		case 1:
			Session::getInstance().clearPlayMap();
			regularMapInitialization();
			gameInstantiation();
			gameLoop();
			break;
		case 2:
			Session::getInstance().clearPlayMap();
			loadMapDialog();
			gameInstantiation();
			gameLoop();
			break;
		case 3:
			break;
		case 4:
			return;
		}
	}
}

void Display::mapEditorGeneralDialog()
{
	while (true) {
		ConsoleFormat::printLineOfText("Map Editor menu");
		ConsoleFormat::printLineOfText("1. New Map");
		ConsoleFormat::printLineOfText("2. Load Map");
		ConsoleFormat::printLineOfText("3. Back");
		ConsoleFormat::printEmptyLineWall();
		
		switch (inputCheck(1, 3)) {
		case 1:
			Session::getInstance().clearPlayMap();
			mapEditorCreateModifyDialog();
			break;
		case 2:
			loadMapDialog();
			break;
		case 3:
			return;
		}
	}
}

void Display::mapEditorCreateModifyDialog()
{
	string textToDisplay;
	int verticalLines;
	string input;
	int cityRegion;
	while (true) {

		
		verticalLines = mainScreen();
		verticalLines += ConsoleFormat::printEmptyLineWall();
		verticalLines += ConsoleFormat::printLineOfText("Create / Modify city");
		verticalLines += ConsoleFormat::printLineOfText("1. Create a new city");
		verticalLines += ConsoleFormat::printLineOfText("2. Modify an existing city");
		verticalLines += ConsoleFormat::printLineOfText("3. Save the current map");
		verticalLines += ConsoleFormat::printLineOfText("4. Back");
		completeBottomWidget(verticalLines);


		switch (inputCheck(1, 4)) {
		case 1:
			ConsoleFormat::printEmptyLineWall();
			ConsoleFormat::printLineOfText("What will be the city's name?");
			ConsoleFormat::printEmptyLineWall();
			cin >> input;
			ConsoleFormat::printEmptyLineWall();
			ConsoleFormat::printLineOfText("What will be the city's color?");
			ConsoleFormat::printLineOfText("1. Blue");
			ConsoleFormat::printLineOfText("2. Yellow");
			ConsoleFormat::printLineOfText("3. Black");
			ConsoleFormat::printLineOfText("4. Red");
			ConsoleFormat::printEmptyLineWall();
			cityRegion = inputCheck(1, 4);
			ConsoleFormat::printEmptyLineWall();
			Session::getInstance().addLocation(input, cityRegion);
			break;
		case 2:
			ConsoleFormat::printEmptyLineWall();
			ConsoleFormat::printLineOfText("What is the city's name?");
			ConsoleFormat::printEmptyLineWall();
			cin >> input;
			ConsoleFormat::printEmptyLineWall();
			if (Session::getInstance().getLocation()->find(input) != Session::getInstance().getLocation()->end()) {
				mapEditorParametersDialog(input);
			}
			else {
				ConsoleFormat::printLineOfText("A city by the name of " + input + " wasn't found. Please try again");
				ConsoleFormat::printEmptyLineWall();
			}
			
			break;
		case 3:
			if (!PlayMap::getInstance()->connectedGraphCheck()) {
				ConsoleFormat::printLineOfText("Map can't be used because some cities are unconnected.");
				ConsoleFormat::printEmptyLineWall();
				break;
			}
			if (!PlayMap::getInstance()->maxNumberOfResearchCenterCheck()) {
				ConsoleFormat::printLineOfText("The maximum number of research center is 6.");
				ConsoleFormat::printEmptyLineWall();
				break;
			}
			if (!PlayMap::getInstance()->minimumNumberOfCities()) {
				ConsoleFormat::printLineOfText("There must be a minimum of 5 cities of each region entered in order to be able to win the game.");
				ConsoleFormat::printEmptyLineWall();
				break;
			}


			ConsoleFormat::printLineOfText("What is the name of the file you want to save the map to");
			ConsoleFormat::printEmptyLineWall();
			cin >> input;
			if (Session::getInstance().savePlayMap(input)) {
				ConsoleFormat::printLineOfText("Map saved!");
				ConsoleFormat::printEmptyLineWall();
			}
			else {
				ConsoleFormat::printLineOfText("Error, couldn't save the map!");
				ConsoleFormat::printEmptyLineWall();
			}
			break;
		case 4:
			return;
		}
	}
}

void Display::mapEditorParametersDialog(string city)
{
	City * currentCity = Session::getInstance().getCity(city);
	vector<City *> * cities = new vector<City *>;
	int input = 0;
	while(true){
		vector<string> * log = new vector<string>;
		int lineCount = 0;
		lineCount += mainScreen();
		lineCount += ConsoleFormat::printLineOfText("City: " + currentCity->getName());
		lineCount += ConsoleFormat::printLineOfText("What would you like to modify");
		lineCount += ConsoleFormat::printLineOfText("1. Set as origin point for the players");
		lineCount += ConsoleFormat::printLineOfText("2. Change the research center status");
		lineCount += ConsoleFormat::printLineOfText("3. Amount of blue disease in the city");
		lineCount += ConsoleFormat::printLineOfText("4. Amount of yellow disease in the city");
		lineCount += ConsoleFormat::printLineOfText("5. Amount of black disease in the city");
		lineCount += ConsoleFormat::printLineOfText("6. Amount of red disease in the city");
		lineCount += ConsoleFormat::printLineOfText("7. Connect to another city");
		lineCount += ConsoleFormat::printLineOfText("8. Disonnect from another city");
		lineCount += ConsoleFormat::printLineOfText("9. Back");
		lineCount += ConsoleFormat::printEmptyLineWall();
		completeBottomWidget(lineCount);

		switch (inputCheck(1, 9)) {
		case 1:
			Session::getInstance().setOrigin(currentCity->getLocation());
			Update("Origin is now " + currentCity->getName());
			break;
		case 2:
			currentCity->setResearchCenter(!currentCity->getResearchCenter());
			Update(currentCity->getName() + " has now " + (currentCity->getResearchCenter() ? "a research center" : "no research center"));	
			break;
		case 3:
			Update();
			diseaseModification(1, log, lineCount, currentCity);
			break;
		case 4:
			Update();
			diseaseModification(2, log, lineCount, currentCity);
			
			break;
		case 5:
			Update();
			diseaseModification(3, log, lineCount, currentCity);
			
			break;
		case 6:
			Update();
			diseaseModification(4, log, lineCount, currentCity);
			
			break;
		case 7:
			lineCount = mainScreen();
			cities->clear();
			lineCount += ConsoleFormat::printLineOfText("Which city would you like to connect to the current city?");
			lineCount += ConsoleFormat::printEmptyLineWall();
			lineCount += listCities(cities, currentCity);
			lineCount += ConsoleFormat::printEmptyLineWall();
			completeBottomWidget(lineCount);

			ConsoleFormat::printEmptyLineWall();
			input = inputCheck(1, cities->size());
			Session::getInstance().connectCity(currentCity->getLocation(), cities->at(input - 1)->getLocation(), false);
			break;
		case 8:
			lineCount = mainScreen();
			cities->clear();
			lineCount += ConsoleFormat::printLineOfText("Which city would you like to disconnect from the current city?");
			lineCount += ConsoleFormat::printEmptyLineWall();
			lineCount += listCities(cities, currentCity);
			lineCount += ConsoleFormat::printEmptyLineWall();
			completeBottomWidget(lineCount);
			ConsoleFormat::printEmptyLineWall();
			input = inputCheck(1, cities->size());
			currentCity->disconnect(cities->at(input - 1), 1);
			Update(currentCity->getName() + "is now disconnected from " + cities->at(input - 1)->getName());
			
			break;
		case 9:
			currentCity = nullptr;
			delete cities;
			cities = nullptr;
			delete log;
			log = nullptr;
			return;
		}
	}
}

void Display::gameLoop()
{
	int verticalLines = 0;
	int currentPlayerIndex = Session::getInstance().getCurrentPlayer();
	Player * currentPlayer = Session::getInstance().getPlayers()->at(currentPlayerIndex);
	do {
		
		while (currentPlayer->getActionPoints() != 0) {
			playerMove();
		}
		for (int i = 0; i < 2; ++i) {
			// goes in a wrapper to display the card
			vector<string> * log = new vector<string>;
			Session::getInstance().playerDraw(currentPlayerIndex);
			log = nullptr;
		}
		Session::getInstance().incrementCurrentPlayer();
		currentPlayerIndex = Session::getInstance().getCurrentPlayer();
		currentPlayer = Session::getInstance().getPlayers()->at(currentPlayerIndex);
		currentPlayer->refreshActions();

		for (int i = 0; i < GameStateVar::getInstance().getInfectionRate(); ++i) {
			// goes in a wrapper to display the card
			Session::getInstance().drawFromInfectionDeck(new vector<string>);
		}

	} while (!((GameStateVar::getInstance().getEclosionCounter() == 8 ||
		GameStateVar::getInstance().getBlue() == 0 ||
		GameStateVar::getInstance().getYellow() == 0 ||
		GameStateVar::getInstance().getBlack() == 0 ||
		GameStateVar::getInstance().getRed() == 0)
		|| (GameStateVar::getInstance().getCure(1) &&
			GameStateVar::getInstance().getCure(2) &&
			GameStateVar::getInstance().getCure(3) &&
			GameStateVar::getInstance().getCure(4))));
}

void Display::playerMove()
{
	Player * currentPlayer = Session::getInstance().getPlayers()->at(Session::getInstance().getCurrentPlayer());
	int verticalLines = mainScreen();
	verticalLines += ConsoleFormat::printEmptyLineWall();
	verticalLines += ConsoleFormat::printLineOfText("Player options");
	verticalLines += ConsoleFormat::printLineOfText("1. Drive / Ferry");
	verticalLines += ConsoleFormat::printLineOfText("2. Direct flight");
	verticalLines += ConsoleFormat::printLineOfText("3. Charter flight");
	verticalLines += ConsoleFormat::printLineOfText("4. Shuttle flight");
	verticalLines += ConsoleFormat::printLineOfText("5. Build a research center");
	verticalLines += ConsoleFormat::printLineOfText("6. Treat disease");
	verticalLines += ConsoleFormat::printLineOfText("7. Share knowledge");
	verticalLines += ConsoleFormat::printLineOfText("8. Discover cure");
	verticalLines += ConsoleFormat::printLineOfText("9. Consult reference card");
	verticalLines += ConsoleFormat::printLineOfText("10. Consult role card");
	completeBottomWidget(verticalLines);

	switch (inputCheck(1, 10)) {
	case 1:
		driveFerry();
		break;
	case 2:
		directFlight();
		break;
	case 3:
		charterFlight();
		break;
	case 4:
		shuttleFlight();
		break;
	case 5:
		Session::getInstance().build(Session::getInstance().getCityCards(currentPlayer->getCity()->getLocation()->getName()));
		break;
	case 6:
		treatDisease();
		break;
	case 7:
		shareKnowledge();
		break;
	case 8:
		discoverCure();
		break;
	case 9:
		Session::getInstance().consultReference();
		break;
	case 10:
		Session::getInstance().consultRoleCard();
		break;
	}
}

void Display::driveFerry()
{
	Player * currentPlayer = Session::getInstance().getPlayers()->at(Session::getInstance().getCurrentPlayer());
	int verticalLines = mainScreen();
	verticalLines += ConsoleFormat::printEmptyLineWall();
	verticalLines += ConsoleFormat::printLineOfText("Where would you like to move?");
	vector<City *> * listOfCities = new vector<City *>;
	int iterationNumber = 1;
	for (auto iterate = currentPlayer->getCity()->getConnections()->begin(); iterate != currentPlayer->getCity()->getConnections()->end(); ++iterate, ++iterationNumber) {
		listOfCities->push_back(iterate->second);
		verticalLines += ConsoleFormat::printLineOfText(to_string(iterationNumber) + ". " + iterate->second->getName());
	}
	completeBottomWidget(verticalLines);
	int userInput = inputCheck(1, listOfCities->size());
	
	Session::getInstance().move(listOfCities->at(userInput - 1));

	currentPlayer = nullptr;
	delete listOfCities;
	listOfCities = nullptr;
}

void Display::directFlight()
{
	Player * currentPlayer = Session::getInstance().getPlayers()->at(Session::getInstance().getCurrentPlayer());
	int verticalLines = mainScreen();
	verticalLines += ConsoleFormat::printEmptyLineWall();
	verticalLines += ConsoleFormat::printLineOfText("Which city would you like to direct fly to?");
	vector<Card *> * listOfCards = new vector<Card *>;
	int iterationNumber = 1;
	for (set<Card*>::iterator it = currentPlayer->getHand()->begin(); it != currentPlayer->getHand()->end(); it++, ++iterationNumber) {
		if (dynamic_cast<CityCard*>(*it) != nullptr) {
			listOfCards->push_back(dynamic_cast<CityCard*>(*it));
			verticalLines += ConsoleFormat::printLineOfText(to_string(iterationNumber) + ". " + (*it)->getTitle());
		}
	}
	completeBottomWidget(verticalLines);
	int userInput = inputCheck(1, listOfCards->size());

	Session::getInstance().move(dynamic_cast<CityCard*>(listOfCards->at(userInput - 1)));
		
	delete listOfCards;
	listOfCards = nullptr;
	currentPlayer = nullptr;
}

void Display::charterFlight()
{
	Player * currentPlayer = Session::getInstance().getPlayers()->at(Session::getInstance().getCurrentPlayer());
	int verticalLines = mainScreen();
	verticalLines += ConsoleFormat::printEmptyLineWall();
	verticalLines += ConsoleFormat::printLineOfText("Where would you like to charter a flight to?");
	vector<City *> * listOfCities = new vector<City *>;
	listCities(listOfCities, currentPlayer->getCity());
	completeBottomWidget(verticalLines);
	int userInput = inputCheck(1, listOfCities->size());


	Session::getInstance().move(Session::getInstance().getCityCards(currentPlayer->getCity()->getName()), listOfCities->at(userInput - 1));


	delete listOfCities;
	listOfCities = nullptr;
	currentPlayer = nullptr;
}

void Display::shuttleFlight()
{
	Player * currentPlayer = Session::getInstance().getPlayers()->at(Session::getInstance().getCurrentPlayer());
	if (currentPlayer->getCity()->getResearchConnections()->size() > 1) {
		int verticalLines = mainScreen();
		verticalLines += ConsoleFormat::printEmptyLineWall();
		verticalLines += ConsoleFormat::printLineOfText("Where would you like to move?");
		vector<City *> * listOfCities = new vector<City *>;
		int iterationNumber = 1;
		for (auto iterate = currentPlayer->getCity()->getResearchConnections()->begin(); iterate != currentPlayer->getCity()->getResearchConnections()->end(); ++iterate, ++iterationNumber) {
			listOfCities->push_back(iterate->second);
			verticalLines += ConsoleFormat::printLineOfText(to_string(iterationNumber) + ". " + iterate->second->getName());
		}
		completeBottomWidget(verticalLines);
		int userInput = inputCheck(1, listOfCities->size());

		Session::getInstance().move(listOfCities->at(userInput - 1));


		delete listOfCities;
		listOfCities = nullptr;
	}
	currentPlayer = nullptr;
}

void Display::treatDisease()
{
	int verticalLines = mainScreen();
	verticalLines += ConsoleFormat::printEmptyLineWall();
	verticalLines += ConsoleFormat::printLineOfText("Which disease would you like to treat?");
	verticalLines += ConsoleFormat::printLineOfText("1. Blue");
	verticalLines += ConsoleFormat::printLineOfText("2. Yellow");
	verticalLines += ConsoleFormat::printLineOfText("3. Black");
	verticalLines += ConsoleFormat::printLineOfText("4. Red");
	completeBottomWidget(verticalLines);

	int userInput = inputCheck(1, 4);
	
	Session::getInstance().treatDisease(userInput);
}

void Display::shareKnowledge()
{
	Player * currentPlayer = Session::getInstance().getPlayers()->at(Session::getInstance().getCurrentPlayer());
	if (currentPlayer->getCity()->getPlayer() > 1) {
		int verticalLines = mainScreen();
		verticalLines += ConsoleFormat::printEmptyLineWall();
		verticalLines += ConsoleFormat::printLineOfText("Who would you like to share knowledge with?");
		vector<Player *> * players = new vector<Player *>;
		int numberOfPlayers = 0;
		for (int i = 1; i < Session::getInstance().getPlayers()->size(); ++i) {
			if (currentPlayer->getCity()->containPlayer(i) && currentPlayer->getPlayerId() != (i + 1)) {
				++numberOfPlayers;
				players->push_back(Session::getInstance().getPlayers()->at(i));
				verticalLines += ConsoleFormat::printLineOfText(to_string(numberOfPlayers) + ". " + players->at(numberOfPlayers - 1)->getPlayerName());
			}
		}
		completeBottomWidget(verticalLines);

		int selectedPlayerIndex = inputCheck(1, players->size()) - 1;


		Session::getInstance().shareKnowledge(Session::getInstance().getCityCards(currentPlayer->getCity()->getName()), players->at(selectedPlayerIndex));

		delete players;
		players = nullptr;
	}

	currentPlayer = nullptr;
}

void Display::discoverCure()
{
	Player * currentPlayer = Session::getInstance().getPlayers()->at(Session::getInstance().getCurrentPlayer());
	vector<CityCard *> * listOfCards = new vector<CityCard *>;
	for (set<Card*>::iterator it = currentPlayer->getHand()->begin(); it != currentPlayer->getHand()->end(); it++) {
		if (dynamic_cast<CityCard*>(*it) != nullptr) {
			listOfCards->push_back(dynamic_cast<CityCard*>(*it));
		}
	}
	if (listOfCards->size() < 5) {
		Update("Insufficient number of city cards in hand to discover a cure");
	}
	else {
		int verticalLines = 0;
		int userInput = 0;
		vector<CityCard *> * listOfSelectedCards = new vector<CityCard *>;
		for (int i = 0; i < 5; ++i) {
			Update("Please choose a card to play for the cure");
			
			for (int j = 0; j < listOfCards->size(); ++j) {
				verticalLines += ConsoleFormat::printLineOfText(to_string(j+1) + ". " + listOfCards->at(j)->getTitle());
			}
			completeBottomWidget(verticalLines);
			userInput = inputCheck(1, listOfCards->size()) - 1;
			listOfSelectedCards->push_back(listOfCards->at(userInput));
			listOfCards->erase(listOfCards->begin() + userInput);
		}
		Session::getInstance().discoverCure(listOfSelectedCards->at(0), listOfSelectedCards->at(1), listOfSelectedCards->at(2), listOfSelectedCards->at(3), listOfSelectedCards->at(4));

		

		delete listOfSelectedCards;
		listOfSelectedCards = nullptr;
	}

	currentPlayer = nullptr;
	delete listOfCards;
	listOfCards = nullptr;
}

void Display::Update()
{
	int verticalLines = mainScreen();
	verticalLines += ConsoleFormat::printEmptyLineWall();
	completeBottomWidget(verticalLines);
}

void Display::Update(string message)
{
	int verticalLines = mainScreen();
	verticalLines += ConsoleFormat::printEmptyLineWall();
	verticalLines += ConsoleFormat::printLineOfText(message);
	completeBottomWidget(verticalLines);
}

void Display::Update(vector<string>* log)
{
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
		separation = 40;
		break;
	case 2:
		separation = 30;
		break;
	case 3:
		separation = 19;
		break;
	case 4:
		separation = 12;
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
		lineLength += ConsoleFormat::makeBox(22, numberOfDiseaseCubes[i], data, 2);
		
		ConsoleFormat::setColor(black, black);
		lineLength += separation;
		cout << ConsoleFormat::emptySpaces(separation);
		ConsoleFormat::setColor(lgrey, black);
		
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
		
		lineLength += ConsoleFormat::makeBox(15, cureState[i], data, 10);

		ConsoleFormat::setColor(black, black);
		lineLength += separation;
		cout << ConsoleFormat::emptySpaces(separation);
		ConsoleFormat::setColor(lgrey, black);

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

		lineLength += ConsoleFormat::makeBox(29, gameStatus[i], data, 2);

		if (Session::getInstance().getPlayers()->size() == 0) {
			ConsoleFormat::printRightWall(lineLength);
			continue;
		}

		ConsoleFormat::setColor(black, black);
		lineLength += separation;
		cout << ConsoleFormat::emptySpaces(separation);
		ConsoleFormat::setColor(lgrey, black);

		for (unsigned j = 0; j < Session::getInstance().getPlayers()->size(); ++j) {
			if (i < 3 || i == 10) {
				lineLength += printPlayer(Session::getInstance().getPlayers()->at(j), i, j);
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
				ConsoleFormat::setColor(black, black);
				lineLength += separation;
				cout << ConsoleFormat::emptySpaces(separation);
				ConsoleFormat::setColor(lgrey, black);
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

int Display::inputCheck(int lowerBound, int upperBound)
{
	string textInput;
	while (true) {
		cin >> textInput;

		if (!isInteger(textInput) || stoi(textInput) < lowerBound || stoi(textInput) > upperBound) {
			ConsoleFormat::printEmptyLineWall();
			ConsoleFormat::printLineOfText("The input must be a number between " + to_string(lowerBound) + " and " + to_string(upperBound) + ". Try again.");
			ConsoleFormat::printEmptyLineWall();
		}
		else {
			return stoi(textInput);
		}
	}
}

inline bool isInteger(const std::string & s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char * p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}



void Display::diseaseModification(int region, vector<string>* log, int lineCount, City * currentCity)
{
	int diseaseValue = 0;
	ConsoleFormat::printLineOfText("What is the new value of the " + currentCity->diseaseTranslate(region) + " in the city?");
	diseaseValue = inputCheck(0, 3);
	if (diseaseValue != currentCity->getDisease(region)) {
		vector<string> * log = new vector<string>;
		if (diseaseValue > currentCity->getDisease(region)) {
			for (int i = 0; i < diseaseValue; ++i) {
				GameStateVar::getInstance().decrementCube(region, log);
				currentCity->incrementDisease(region);
				log->push_back("Disease incremented to " + to_string(i + 1) + " in " + currentCity->getName());
			}
		}
		else {
			for (int i = currentCity->getDisease(region); i > diseaseValue; --i) {
				GameStateVar::getInstance().incrementCube(region);
				log->push_back("One " + currentCity->diseaseTranslate(region) + " cube returned");
				currentCity->decrementDisease(region);
				log->push_back("Disease incremented to " + to_string(i + 1) + " in " + currentCity->getName());
			}
		}
		Update(log);
	}
}

void Display::loadMapDialog()
{
	string fileName;
	ConsoleFormat::printLineOfText("What is the file name?");
	ConsoleFormat::printEmptyLineWall();
	cin >> fileName;
	if (Session::getInstance().loadPlayMap(fileName)) {
		mapEditorCreateModifyDialog();
	}
	else {
		ConsoleFormat::printLineOfText("File couldn't be opened");
		ConsoleFormat::printEmptyLineWall();
	}
}

void Display::regularMapInitialization()
{
	static Session & session = Session::getInstance();
	session.addLocation("Atlanta", 1);
	session.addLocation("San Francisco", 1);
	session.addLocation("Chicago", 1);
	session.addLocation("Montreal", 1);
	session.addLocation("Washington", 1);
	session.addLocation("New York", 1);
	session.addLocation("Londres", 1);
	session.addLocation("Madrid", 1);
	session.addLocation("Paris", 1);
	session.addLocation("Essen", 1);
	session.addLocation("Saint-Petersbourg", 1);
	session.addLocation("Milan", 1);

	session.addLocation("Los Angeles", 2);
	session.addLocation("Miami", 2);
	session.addLocation("Mexico", 2);
	session.addLocation("Bogota", 2);
	session.addLocation("Lima", 2);
	session.addLocation("Santiago", 2);
	session.addLocation("Sao Paulo", 2);
	session.addLocation("Buenos Aires", 2);
	session.addLocation("Johannesburg", 2);
	session.addLocation("Kinshasa", 2);
	session.addLocation("Lagos", 2);
	session.addLocation("Khartoum", 2);

	session.addLocation("Alger", 3);
	session.addLocation("Le Caire", 3);
	session.addLocation("Istanbul", 3);
	session.addLocation("Moscou", 3);
	session.addLocation("Bagdad", 3);
	session.addLocation("Teheran", 3);
	session.addLocation("Karachi", 3);
	session.addLocation("Riyad", 3);
	session.addLocation("Delhi", 3);
	session.addLocation("Mumbai", 3);
	session.addLocation("Calcutta", 3);
	session.addLocation("Chennai", 3);

	session.addLocation("Pekin", 4);
	session.addLocation("Seoul", 4);
	session.addLocation("Shanghai", 4);
	session.addLocation("Tokyo", 4);
	session.addLocation("Osaka", 4);
	session.addLocation("Taipei", 4);
	session.addLocation("Hong Kong", 4);
	session.addLocation("Bangkok", 4);
	session.addLocation("Manille", 4);
	session.addLocation("Ho-Chi-Minh-Ville", 4);
	session.addLocation("Jakarta", 4);
	session.addLocation("Sydney", 4);

	session.connectCity("San Francisco", "Tokyo", true);
	session.connectCity("San Francisco", "Manille", true);
	session.connectCity("Los Angeles", "Sydney", true);
	session.connectCity("New York", "Londres", true);
	session.connectCity("New York", "Madrid", true);
	session.connectCity("Madrid", "Sao Paulo", true);
	session.connectCity("Lagos", "Sao Paulo", true);
	session.connectCity("Johannesburg", "Buenos Aires", true);
	session.connectCity("San Francisco", "Los Angeles", true);
	session.connectCity("San Francisco", "Chicago", true);
	session.connectCity("Los Angeles", "Chicago", true);
	session.connectCity("Los Angeles", "Mexico", true);
	session.connectCity("Los Angeles", "Lima", true);
	session.connectCity("Mexico", "Lima", true);
	session.connectCity("Santiago", "Lima", true);
	session.connectCity("Bogota", "Lima", true);
	session.connectCity("Santiago", "Buenos Aires", true);
	session.connectCity("Chicago", "Mexico", true);
	session.connectCity("Chicago", "Atlanta", true);
	session.connectCity("Chicago", "Montreal", true);
	session.connectCity("Bogota", "Mexico", true);
	session.connectCity("Miami", "Mexico", true);
	session.connectCity("Bogota", "Miami", true);
	session.connectCity("Bogota", "Sao Paulo", true);
	session.connectCity("Bogota", "Buenos Aires", true);
	session.connectCity("Sao Paulo", "Buenos Aires", true);
	session.connectCity("Atlanta", "Washington", true);
	session.connectCity("Atlanta", "Miami", true);
	session.connectCity("Washington", "Miami", true);
	session.connectCity("Washington", "Montreal", true);
	session.connectCity("Washington", "New York", true);
	session.connectCity("Montreal", "New York", true);
	session.connectCity("Lagos", "Kinshasa", true);
	session.connectCity("Lagos", "Khartoum", true);
	session.connectCity("Khartoum", "Kinshasa", true);
	session.connectCity("Khartoum", "Johannesburg", true);
	session.connectCity("Kinshasa", "Johannesburg", true);
	session.connectCity("Khartoum", "Le Caire", true);
	session.connectCity("Londres", "Madrid", true);
	session.connectCity("Londres", "Paris", true);
	session.connectCity("Londres", "Essen", true);
	session.connectCity("Paris", "Madrid", true);
	session.connectCity("Alger", "Madrid", true);
	session.connectCity("Alger", "Paris", true);
	session.connectCity("Alger", "Le Caire", true);
	session.connectCity("Alger", "Istanbul", true);
	session.connectCity("Paris", "Essen", true);
	session.connectCity("Paris", "Milan", true);
	session.connectCity("Milan", "Essen", true);
	session.connectCity("Saint-Petersbourg", "Essen", true);
	session.connectCity("Milan", "Istanbul", true);
	session.connectCity("Saint-Petersbourg", "Istanbul", true);
	session.connectCity("Saint-Petersbourg", "Moscou", true);
	session.connectCity("Le Caire", "Istanbul", true);
	session.connectCity("Bagdad", "Istanbul", true);
	session.connectCity("Moscou", "Istanbul", true);
	session.connectCity("Le Caire", "Bagdad", true);
	session.connectCity("Le Caire", "Riyad", true);
	session.connectCity("Moscou", "Teheran", true);
	session.connectCity("Bagdad", "Teheran", true);
	session.connectCity("Bagdad", "Riyad", true);
	session.connectCity("Karachi", "Riyad", true);
	session.connectCity("Karachi", "Teheran", true);
	session.connectCity("Karachi", "Delhi", true);
	session.connectCity("Karachi", "Mumbai", true);
	session.connectCity("Teheran", "Delhi", true);
	session.connectCity("Mumbai", "Delhi", true);
	session.connectCity("Calcutta", "Delhi", true);
	session.connectCity("Chennai", "Delhi", true);
	session.connectCity("Mumbai", "Chennai", true);
	session.connectCity("Calcutta", "Chennai", true);
	session.connectCity("Jakarta", "Chennai", true);
	session.connectCity("Calcutta", "Bangkok", true);
	session.connectCity("Calcutta", "Hong Kong", true);
	session.connectCity("Pekin", "Seoul", true);
	session.connectCity("Pekin", "Shanghai", true);
	session.connectCity("Seoul", "Shanghai", true);
	session.connectCity("Tokyo", "Shanghai", true);
	session.connectCity("Taipei", "Shanghai", true);
	session.connectCity("Hong Kong", "Shanghai", true);
	session.connectCity("Seoul", "Tokyo", true);
	session.connectCity("Osaka", "Tokyo", true);
	session.connectCity("Osaka", "Taipei", true);
	session.connectCity("Hong Kong", "Taipei", true);
	session.connectCity("Manille", "Taipei", true);
	session.connectCity("Hong Kong", "Manille", true);
	session.connectCity("Hong Kong", "Bangkok", true);
	session.connectCity("Hong Kong", "Ho-Chi-Minh-Ville", true);
	session.connectCity("Bangkok", "Ho-Chi-Minh-Ville", true);
	session.connectCity("Jakarta", "Ho-Chi-Minh-Ville", true);
	session.connectCity("Manille", "Ho-Chi-Minh-Ville", true);
	session.connectCity("Jakarta", "Bangkok", true);
	session.connectCity("Jakarta", "Sydney", true);
	session.connectCity("Manille", "Sydney", true);
}

void Display::gameInstantiation()
{
	int playerCount = 0;
	int lineCount = 0;
	string playerName;
	ConsoleFormat::printLineOfText("How many will be playing (2 to 4)");
	ConsoleFormat::printEmptyLineWall();
	ConsoleFormat::printEmptyLineWall();
	playerCount = inputCheck(2, 4);
	for (int i = 0; i < playerCount; ++i) {
		lineCount += ConsoleFormat::printLineOfText("What is the name of player " + to_string(i+1));
		lineCount += ConsoleFormat::printEmptyLineWall();
		lineCount += ConsoleFormat::printEmptyLineWall();
		cin >> playerName;
		
		Session::getInstance().addPlayer(playerName);

	}


	Session::getInstance().initializeHands(new vector<string>);
	
	


	Session::getInstance().initializeInfections();
	
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


