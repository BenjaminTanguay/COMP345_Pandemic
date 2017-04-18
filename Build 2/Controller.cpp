#include "Controller.h"
#include "ConsoleFormat.h"
#include "Session.h"



Controller::Controller()
{
	display = new Display();
}


Controller::~Controller()
{
	delete display;
	display = nullptr;
}

int Controller::inputCheck(int lowerBound, int upperBound)
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
			Session::getInstance()->getLog()->stringToLog(textInput);
			Session::getInstance()->getLog()->stringToLog("");
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


void Controller::welcomeSceen()
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

void Controller::newGameScreen()
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
			Session::getInstance()->clearPlayMap();
			regularMapInitialization();
			gameInstantiation();
			gameLoop();
			Session::getInstance()->resetSession();
			break;
		case 2:
			Session::getInstance()->clearPlayMap();
			loadFileDialog(map);
			gameInstantiation();
			gameLoop();
			Session::getInstance()->resetSession();
			break;
		case 3:
			loadFileDialog(game);
			break;
		case 4:
			return;
		}
	}
}

void Controller::mapEditorGeneralDialog()
{
	while (true) {
		ConsoleFormat::printLineOfText("Map Editor menu");
		ConsoleFormat::printLineOfText("1. New Map");
		ConsoleFormat::printLineOfText("2. Load Map");
		ConsoleFormat::printLineOfText("3. Back");
		ConsoleFormat::printEmptyLineWall();

		switch (inputCheck(1, 3)) {
		case 1:
			Session::getInstance()->clearPlayMap();
			mapEditorCreateModifyDialog();
			break;
		case 2:
			loadFileDialog(map);
			break;
		case 3:
			return;
		}
	}
}

void Controller::mapEditorCreateModifyDialog()
{
	string textToDisplay;
	int verticalLines;
	string input;
	int cityRegion;
	while (true) {


		verticalLines = display->mainScreen();
		verticalLines += ConsoleFormat::printEmptyLineWall();
		verticalLines += ConsoleFormat::printLineOfText("Create / Modify city");
		verticalLines += ConsoleFormat::printLineOfText("1. Create a new city");
		verticalLines += ConsoleFormat::printLineOfText("2. Modify an existing city");
		verticalLines += ConsoleFormat::printLineOfText("3. Save the current map");
		verticalLines += ConsoleFormat::printLineOfText("4. Back");
		display->completeBottomWidget(verticalLines);


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
			Session::getInstance()->addLocation(input, cityRegion);
			break;
		case 2:
			ConsoleFormat::printEmptyLineWall();
			ConsoleFormat::printLineOfText("What is the city's name?");
			ConsoleFormat::printEmptyLineWall();
			cin >> input;
			ConsoleFormat::printEmptyLineWall();
			if (Session::getInstance()->getLocation()->find(input) != Session::getInstance()->getLocation()->end()) {
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


			saveFileDialog(map);
			break;
		case 4:
			return;
		}
	}
}

void Controller::mapEditorParametersDialog(string city)
{
	City * currentCity = Session::getInstance()->getCity(city);
	vector<City *> * cities = new vector<City *>;
	int input = 0;
	while (true) {
		vector<string> * log = new vector<string>;
		int lineCount = 0;
		lineCount += display->mainScreen();
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
		display->completeBottomWidget(lineCount);

		switch (inputCheck(1, 9)) {
		case 1:
			Session::getInstance()->setOrigin(currentCity->getLocation());
			display->Update("Origin is now " + currentCity->getName());
			break;
		case 2:
			currentCity->setResearchCenter(!currentCity->getResearchCenter());
			display->Update(currentCity->getName() + " has now " + (currentCity->getResearchCenter() ? "a research center" : "no research center"));
			break;
		case 3:
			display->Update();
			diseaseModification(1, log, lineCount, currentCity);
			break;
		case 4:
			display->Update();
			diseaseModification(2, log, lineCount, currentCity);

			break;
		case 5:
			display->Update();
			diseaseModification(3, log, lineCount, currentCity);

			break;
		case 6:
			display->Update();
			diseaseModification(4, log, lineCount, currentCity);

			break;
		case 7:
			lineCount = display->mainScreen();
			cities->clear();
			lineCount += ConsoleFormat::printLineOfText("Which city would you like to connect to the current city?");
			lineCount += ConsoleFormat::printEmptyLineWall();
			lineCount += display->listCities(cities, currentCity);
			lineCount += ConsoleFormat::printEmptyLineWall();
			display->completeBottomWidget(lineCount);

			ConsoleFormat::printEmptyLineWall();
			input = inputCheck(1, cities->size());
			Session::getInstance()->connectCity(currentCity->getLocation(), cities->at(input - 1)->getLocation(), false);
			break;
		case 8:
			lineCount = display->mainScreen();
			cities->clear();
			lineCount += ConsoleFormat::printLineOfText("Which city would you like to disconnect from the current city?");
			lineCount += ConsoleFormat::printEmptyLineWall();
			lineCount += display->listCities(cities, currentCity);
			lineCount += ConsoleFormat::printEmptyLineWall();
			display->completeBottomWidget(lineCount);
			ConsoleFormat::printEmptyLineWall();
			input = inputCheck(1, cities->size());
			currentCity->disconnect(cities->at(input - 1), 1);
			display->Update(currentCity->getName() + "is now disconnected from " + cities->at(input - 1)->getName());

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

void Controller::gameLoop()
{
	int verticalLines = 0;
	int currentPlayerIndex = Session::getInstance()->getCurrentPlayer();
	Player * currentPlayer = Session::getInstance()->getPlayers()->at(currentPlayerIndex);
	do {

		while (currentPlayer->getActionPoints() != 0) {
			playerMove(currentPlayer);
		}
		for (int i = 0; i < 2; ++i) {
			// goes in a wrapper to display the card
			vector<string> * log = new vector<string>;
			Session::getInstance()->playerDraw(currentPlayerIndex);
			handSizeCheck(currentPlayer);
			log = nullptr;
		}
		Session::getInstance()->incrementCurrentPlayer();
		currentPlayerIndex = Session::getInstance()->getCurrentPlayer();
		currentPlayer = Session::getInstance()->getPlayers()->at(currentPlayerIndex);
		currentPlayer->refreshActions();

		if (!(GameStateVar::getInstance()->getOneQuietNight())) {
			for (int i = 0; i < GameStateVar::getInstance()->getInfectionRate(); ++i) {
				// goes in a wrapper to display the card
				eventCardPrompt();
				Session::getInstance()->drawFromInfectionDeck(new vector<string>);
			}
		}
		else {
			GameStateVar::getInstance()->setOneQuietNight(false);
		}

	} while (!GameStateVar::getInstance()->isGameOver());

	if (GameStateVar::getInstance()->isGameLost()) {
		display->Update("Game over. You lose! Better luck next time.");
	}
	else {
		display->Update("Game over. You win! Congratulation");
	}
	Session::getInstance()->getLog()->recordLog();
	Session::getInstance()->getLog()->stopLog();

}

void Controller::playerMove(Player * aPlayer)
{
	Player * currentPlayer = Session::getInstance()->getPlayers()->at(Session::getInstance()->getCurrentPlayer());
	int verticalLines = display->mainScreen();
	verticalLines += ConsoleFormat::printEmptyLineWall();
	verticalLines += ConsoleFormat::printLineOfText("Player options");
	verticalLines += ConsoleFormat::printLineOfText("1. Drive / Ferry");
	verticalLines += ConsoleFormat::printLineOfText("2. Direct flight");
	verticalLines += ConsoleFormat::printLineOfText("3. Charter flight");
	verticalLines += ConsoleFormat::printLineOfText("4. Shuttle flight");
	int moveNum = 4;
	if (aPlayer->getPlayerId() == currentPlayer->getPlayerId()) {// not a role play on another player
		verticalLines += ConsoleFormat::printLineOfText("5. Build a research center");
		verticalLines += ConsoleFormat::printLineOfText("6. Treat disease");
		verticalLines += ConsoleFormat::printLineOfText("7. Share knowledge");
		verticalLines += ConsoleFormat::printLineOfText("8. Discover cure");
		verticalLines += ConsoleFormat::printLineOfText("9. Consult reference card");
		verticalLines += ConsoleFormat::printLineOfText("10. Consult role card");
		verticalLines += ConsoleFormat::printLineOfText("11. Play an event card");
		verticalLines += ConsoleFormat::printLineOfText("12. Save the game");
		moveNum = 12;
	}
	display->completeBottomWidget(verticalLines);
	
	switch (inputCheck(1, moveNum)) {
	case 1:
		driveFerry(aPlayer);
		break;
	case 2:
		directFlight(aPlayer);
		break;
	case 3:
		charterFlight(aPlayer);
		break;
	case 4:
		shuttleFlight(aPlayer);
		break;
	case 5:
		buildResearchCenter();
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
		Session::getInstance()->consultReference();
		break;
	case 10:
		Session::getInstance()->consultRoleCard();
		playRole();
		break;
	case 11:
		eventCardPrompt();
		break;
	case 12:
		saveFileDialog(game);
		break;
	}
}

void Controller::driveFerry(Player * aPlayer)
{
	Player * currentPlayer = Session::getInstance()->getPlayers()->at(Session::getInstance()->getCurrentPlayer());
	int verticalLines = display->mainScreen();
	verticalLines += ConsoleFormat::printEmptyLineWall();
	verticalLines += ConsoleFormat::printLineOfText("Where would you like to move?");
	vector<City *> * listOfCities = new vector<City *>;
	int iterationNumber = 1;
	for (auto iterate = aPlayer->getCity()->getConnections()->begin(); iterate != aPlayer->getCity()->getConnections()->end(); ++iterate, ++iterationNumber) {
		listOfCities->push_back(iterate->second);
		verticalLines += ConsoleFormat::printLineOfText(to_string(iterationNumber) + ". " + iterate->second->getName());
	}
	display->completeBottomWidget(verticalLines);
	int userInput = inputCheck(1, listOfCities->size());

	Session::getInstance()->move(listOfCities->at(userInput - 1), aPlayer);

	currentPlayer = nullptr;
	delete listOfCities;
	listOfCities = nullptr;
}

void Controller::directFlight(Player * aPlayer)
{
	Player * currentPlayer = Session::getInstance()->getPlayers()->at(Session::getInstance()->getCurrentPlayer());
	bool handContainsCityCard;
	// Checking to see if the hand contains a city card.
	for (auto iterate = currentPlayer->getHand()->begin(); iterate != currentPlayer->getHand()->end(); ++iterate) {
		if (dynamic_cast<CityCard *>((*iterate)) != nullptr) {
			handContainsCityCard = true;
			break;
		}
	}


	if (handContainsCityCard) {
		int verticalLines = display->mainScreen();
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
		display->completeBottomWidget(verticalLines);
		int userInput = inputCheck(1, listOfCards->size());

		Session::getInstance()->move(dynamic_cast<CityCard*>(listOfCards->at(userInput - 1)), aPlayer);
		delete listOfCards;
		listOfCards = nullptr;
	}
	else {
		int verticalLines = display->mainScreen();
		verticalLines += ConsoleFormat::printEmptyLineWall();
		verticalLines += ConsoleFormat::printLineOfText("The hand doesn't contain a city card. Direct flight is illegal.");
		verticalLines += ConsoleFormat::printEmptyLineWall();
		display->completeBottomWidget(verticalLines);
	}

	currentPlayer = nullptr;
}

void Controller::charterFlight(Player * aPlayer)
{
	Player * currentPlayer = Session::getInstance()->getPlayers()->at(Session::getInstance()->getCurrentPlayer());
	Card * card = Session::getInstance()->getCityCards(aPlayer->getCity()->getName());
	

	if (currentPlayer->getHand()->find(card) == currentPlayer->getHand()->end()) {
		int verticalLines = display->mainScreen();
		verticalLines += ConsoleFormat::printEmptyLineWall();
		verticalLines += ConsoleFormat::printLineOfText(currentPlayer->getPlayerName() + " doesn't own the " + aPlayer->getCity()->getName() + " card in his hand. Can't charter a flight.");
		verticalLines += ConsoleFormat::printEmptyLineWall();
		display->completeBottomWidget(verticalLines);
	}
	else {
		vector<City *> * listOfCities = new vector<City *>;
		int userInput = display->cityChoice(currentPlayer, "Where would you like to charter a flight to?", listOfCities);
		Session::getInstance()->move(dynamic_cast<CityCard *>(card), listOfCities->at(userInput), aPlayer);


		delete listOfCities;
		listOfCities = nullptr;
	}	

	currentPlayer = nullptr;
	card = nullptr;

}

void Controller::shuttleFlight(Player * aPlayer)
{
	Player * currentPlayer = Session::getInstance()->getPlayers()->at(Session::getInstance()->getCurrentPlayer());
	if (aPlayer->getCity()->getResearchCenter() || currentPlayer->getPlayerId() != aPlayer->getPlayerId()) {

		int verticalLines = display->mainScreen();
		vector<City *> * listOfCities = new vector<City *>;
		if (aPlayer->getCity()->getResearchConnections()->size() > 0 || currentPlayer->getPlayerId() != aPlayer->getPlayerId()) {
			int iterationNumber = 1;
			verticalLines += ConsoleFormat::printEmptyLineWall();
			verticalLines += ConsoleFormat::printLineOfText("Where would you like to move?");
			if (aPlayer->getCity()->getResearchConnections()->size() > 0){
				
				for (auto iterate = aPlayer->getCity()->getResearchConnections()->begin(); iterate != aPlayer->getCity()->getResearchConnections()->end(); ++iterate, ++iterationNumber) {
					listOfCities->push_back(iterate->second);
					verticalLines += ConsoleFormat::printLineOfText(to_string(iterationNumber) + ". " + iterate->second->getName());
				}
			}
			if (currentPlayer->getPlayerId() != aPlayer->getPlayerId()) {
				for (auto iterate = Session::getInstance()->getPlayers()->begin(); iterate != Session::getInstance()->getPlayers()->end(); ++iterate, ++iterationNumber) {
					listOfCities->push_back(Session::getInstance()->getPlayers()->at(iterationNumber - 1)->getCity());
					verticalLines += ConsoleFormat::printLineOfText(to_string(iterationNumber) + ". " + listOfCities->at(iterationNumber - 1)->getLocation()->getName());
				}
			}

			display->completeBottomWidget(verticalLines);
			int userInput = inputCheck(1, listOfCities->size());


			Session::getInstance()->move(listOfCities->at(userInput - 1), aPlayer);

			delete listOfCities;
			listOfCities = nullptr;
		}
	}
	else {
		int verticalLines = display->mainScreen();
		verticalLines += ConsoleFormat::printEmptyLineWall();
		verticalLines += ConsoleFormat::printLineOfText(aPlayer->getCity()->getName() + " doesn't contain a research center. Illegal move.");
		verticalLines += ConsoleFormat::printEmptyLineWall();
		display->completeBottomWidget(verticalLines);
	}
	currentPlayer = nullptr;
}

void Controller::buildResearchCenter()
{
	Player * currentPlayer = Session::getInstance()->getPlayers()->at(Session::getInstance()->getCurrentPlayer());
	int verticalLines = display->mainScreen();
	if (GameStateVar::getInstance()->getResearchCenterCounter() == 6) {
		verticalLines += ConsoleFormat::printLineOfText("Which research station would you like to relocate?");
		vector<City *> * listOfCities = new vector<City *>;
		int iterationNumber = 1;
		// list all research station locations in order to chose one to be moved.
		for (auto iterate = currentPlayer->getCity()->getResearchConnections()->begin(); iterate != currentPlayer->getCity()->getResearchConnections()->end(); ++iterate, ++iterationNumber) {
			listOfCities->push_back(iterate->second);
			verticalLines += ConsoleFormat::printLineOfText(to_string(iterationNumber) + ". " + iterate->second->getName());
		}
		display->completeBottomWidget(verticalLines);
		int userInput = inputCheck(1, listOfCities->size());

		Session::getInstance()->build(Session::getInstance()->getCityCards(currentPlayer->getCity()->getLocation()->getName()), listOfCities->at(userInput - 1));

		delete listOfCities;
		listOfCities = nullptr;
	}
	else{
		Session::getInstance()->build(Session::getInstance()->getCityCards(currentPlayer->getCity()->getLocation()->getName()), currentPlayer->getCity());
	}
	currentPlayer = nullptr;
}

void Controller::treatDisease()
{
	int verticalLines = display->mainScreen();
	verticalLines += ConsoleFormat::printEmptyLineWall();
	verticalLines += ConsoleFormat::printLineOfText("Which disease would you like to treat?");
	verticalLines += ConsoleFormat::printLineOfText("1. Blue");
	verticalLines += ConsoleFormat::printLineOfText("2. Yellow");
	verticalLines += ConsoleFormat::printLineOfText("3. Black");
	verticalLines += ConsoleFormat::printLineOfText("4. Red");
	display->completeBottomWidget(verticalLines);

	int userInput = inputCheck(1, 4);

	Session::getInstance()->treatDisease(userInput);
}

void Controller::shareKnowledge()
{
	Player * currentPlayer = Session::getInstance()->getPlayers()->at(Session::getInstance()->getCurrentPlayer());
	if (currentPlayer->getCity()->getPlayer() > 1) {
		int verticalLines = display->mainScreen();
		verticalLines += ConsoleFormat::printEmptyLineWall();
		verticalLines += ConsoleFormat::printLineOfText("Who would you like to share knowledge with?");
		vector<Player *> * players = new vector<Player *>;
		int numberOfPlayers = 0;
		for (int i = 1; i < Session::getInstance()->getPlayers()->size(); ++i) {
			if (currentPlayer->getCity()->containPlayer(i) && currentPlayer->getPlayerId() != (i + 1)) {
				++numberOfPlayers;
				players->push_back(Session::getInstance()->getPlayers()->at(i));
				verticalLines += ConsoleFormat::printLineOfText(to_string(numberOfPlayers) + ". " + players->at(numberOfPlayers - 1)->getPlayerName());
			}
		}
		display->completeBottomWidget(verticalLines);

		int selectedPlayerIndex = inputCheck(1, players->size()) - 1;


		Session::getInstance()->shareKnowledge(Session::getInstance()->getCityCards(currentPlayer->getCity()->getName()), players->at(selectedPlayerIndex));
		handSizeCheck(currentPlayer);
		handSizeCheck(players->at(selectedPlayerIndex));

		delete players;
		players = nullptr;
	}

	currentPlayer = nullptr;
}

void Controller::discoverCure()
{
	Player * currentPlayer = Session::getInstance()->getPlayers()->at(Session::getInstance()->getCurrentPlayer());
	vector<CityCard *> * listOfCards = new vector<CityCard *>;
	for (set<Card*>::iterator it = currentPlayer->getHand()->begin(); it != currentPlayer->getHand()->end(); it++) {
		if (dynamic_cast<CityCard*>(*it) != nullptr) {
			listOfCards->push_back(dynamic_cast<CityCard*>(*it));
		}
	}
	if (listOfCards->size() < 5) {
		display->Update("Insufficient number of city cards in hand to discover a cure");
	}
	else {
		int verticalLines = 0;
		int userInput = 0;
		vector<CityCard *> * listOfSelectedCards = new vector<CityCard *>;
		for (int i = 0; i < 5; ++i) {
			display->Update("Please choose a card to play for the cure");

			for (int j = 0; j < listOfCards->size(); ++j) {
				verticalLines += ConsoleFormat::printLineOfText(to_string(j + 1) + ". " + listOfCards->at(j)->getTitle());
			}
			display->completeBottomWidget(verticalLines);
			userInput = inputCheck(1, listOfCards->size()) - 1;
			listOfSelectedCards->push_back(listOfCards->at(userInput));
			listOfCards->erase(listOfCards->begin() + userInput);
		}
		Session::getInstance()->discoverCure(listOfSelectedCards->at(0), listOfSelectedCards->at(1), listOfSelectedCards->at(2), listOfSelectedCards->at(3), listOfSelectedCards->at(4));



		delete listOfSelectedCards;
		listOfSelectedCards = nullptr;
	}

	currentPlayer = nullptr;
	delete listOfCards;
	listOfCards = nullptr;
}

void Controller::diseaseModification(int region, vector<string>* log, int lineCount, City * currentCity)
{
	int diseaseValue = 0;
	ConsoleFormat::printLineOfText("What is the new value of the " + currentCity->diseaseTranslate(region) + " in the city?");
	diseaseValue = inputCheck(0, 3);
	if (diseaseValue != currentCity->getDisease(region)) {
		vector<string> * log = new vector<string>;
		if (diseaseValue > currentCity->getDisease(region)) {
			for (int i = 0; i < diseaseValue; ++i) {
				GameStateVar::getInstance()->decrementCube(region, log);
				currentCity->incrementDisease(region);
				log->push_back("Disease incremented to " + to_string(i + 1) + " in " + currentCity->getName());
			}
		}
		else {
			for (int i = currentCity->getDisease(region); i > diseaseValue; --i) {
				GameStateVar::getInstance()->incrementCube(region);
				log->push_back("One " + currentCity->diseaseTranslate(region) + " cube returned");
				currentCity->decrementDisease(region);
				log->push_back("Disease incremented to " + to_string(i + 1) + " in " + currentCity->getName());
			}
		}
		display->Update(log);
	}
}


void Controller::loadFileDialog(int mapOrGame)
{
	string fileName;
	bool loadSuccess = false;
	ConsoleFormat::printLineOfText("What is the file name?");
	ConsoleFormat::printEmptyLineWall();
	cin >> fileName;
	switch (mapOrGame) {
	case game:
		loadSuccess = Session::getInstance()->loadSession(fileName);
		break;
	case map:
		loadSuccess = Session::getInstance()->loadPlayMap(fileName);
		break;
	default:
		break;
	}

	if (loadSuccess) {
		mapEditorCreateModifyDialog();
	}
	else {
		ConsoleFormat::printLineOfText("File couldn't be opened");
		ConsoleFormat::printEmptyLineWall();
	}
}

void Controller::saveFileDialog(int mapOrGame)
{
	bool saveSuccess = false;
	string fileName;
	ConsoleFormat::printLineOfText("What is the name of the file you want to save?");
	ConsoleFormat::printEmptyLineWall();
	cin >> fileName;

	switch (mapOrGame) {
	case map:
		saveSuccess = Session::getInstance()->savePlayMap(fileName);
		break;
	case game:
		saveSuccess = Session::getInstance()->saveSession(fileName);
		break;
	default:
		break;
	}

	if (saveSuccess) {
		ConsoleFormat::printLineOfText("File saved!");
		ConsoleFormat::printEmptyLineWall();
	}
	else {
		ConsoleFormat::printLineOfText("Error, couldn't save the file!");
		ConsoleFormat::printEmptyLineWall();
	}
}

void Controller::gameInstantiation()
{
	int playerCount = 0;
	int lineCount = 0;
	int logGame = 0;
	string playerName;
	ConsoleFormat::printLineOfText("Would you like to create a log of the game?");
	ConsoleFormat::printLineOfText("1. Yes");
	ConsoleFormat::printLineOfText("2. No");
	ConsoleFormat::printEmptyLineWall();
	ConsoleFormat::printEmptyLineWall();
	logGame = Controller::inputCheck(1, 2);
	switch (logGame) {
	case 1:
		Session::getInstance()->getLog()->startLog();
		break;
	default:
		Session::getInstance()->getLog()->stopLog();
		break;
	}

	ConsoleFormat::printLineOfText("How many will be playing (2 to 4)");
	ConsoleFormat::printEmptyLineWall();
	ConsoleFormat::printEmptyLineWall();
	playerCount = Controller::inputCheck(2, 4);
	ConsoleFormat::printLineOfText("What will be the difficulty level?");
	ConsoleFormat::printLineOfText("1. Introductory");
	ConsoleFormat::printLineOfText("2. Standard");
	ConsoleFormat::printLineOfText("3. Heroic");
	ConsoleFormat::printEmptyLineWall();
	ConsoleFormat::printEmptyLineWall();
	Session::getInstance()->setDifficultyLevel(Controller::inputCheck(1, 3));

	for (int i = 0; i < playerCount; ++i) {
		lineCount += ConsoleFormat::printLineOfText("What is the name of player " + to_string(i + 1));
		lineCount += ConsoleFormat::printEmptyLineWall();
		lineCount += ConsoleFormat::printEmptyLineWall();
		cin >> playerName;

		Session::getInstance()->addPlayer(playerName);

	}


	Session::getInstance()->initializeHands(new vector<string>);




	Session::getInstance()->initializeInfections();

}

void Controller::eventCardPrompt()
{
	int verticalLines = display->mainScreen();
	verticalLines += ConsoleFormat::printEmptyLineWall();
	verticalLines += ConsoleFormat::printLineOfText("Would anyone want to play an event card?");
	verticalLines += ConsoleFormat::printLineOfText("1. Yes");
	verticalLines += ConsoleFormat::printLineOfText("2. No");
	verticalLines += ConsoleFormat::printEmptyLineWall();
	display->completeBottomWidget(verticalLines);

	switch (Controller::inputCheck(1, 2)) {
	case 1:
		playEventCards();
	case 2:
		return;
	}
}

void Controller::playEventCardOrDiscard(Player * player)
{
	int verticalLines = display->mainScreen();
	verticalLines += ConsoleFormat::printEmptyLineWall();
	verticalLines += ConsoleFormat::printLineOfText("Your hand is full. Play an event card to make some space or discard a card.");
	verticalLines += ConsoleFormat::printLineOfText("1. Play an event card");
	verticalLines += ConsoleFormat::printLineOfText("2. Discard a card");
	verticalLines += ConsoleFormat::printEmptyLineWall();
	display->completeBottomWidget(verticalLines);
	Card * card;
	switch (Controller::inputCheck(1, 2)) {
	case 1:
		playEventCards();
		return;
	case 2:
		card = cardSelection(player, "Which card would you like to discard?");
		player->discardCard(card);
		card = nullptr;
		return;
	}
}

void Controller::playEventCards()
{
	int verticalLines = display->mainScreen();
	verticalLines += ConsoleFormat::printEmptyLineWall();



	verticalLines += ConsoleFormat::printLineOfText("Which event card would you like to play?");

	vector<pair<EventCard *, int>> * pairEventCardPlayerIndex = new vector<pair<EventCard *, int>>;
	vector<Player *> * players = Session::getInstance()->getPlayers();
	int iterationNumber = 0;
	for (int i = 0; i < players->size(); ++i) {
		for (set<Card*>::iterator it = players->at(i)->getHand()->begin(); it != players->at(i)->getHand()->end(); ++it) {
			if (dynamic_cast<EventCard*>(*it) != nullptr) {
				++iterationNumber;
				pairEventCardPlayerIndex->push_back(make_pair(dynamic_cast<EventCard *>(*it), i));
				verticalLines += ConsoleFormat::printLineOfText(to_string(iterationNumber) + ". " + (*it)->getTitle());
			}
		}
	}
	verticalLines += ConsoleFormat::printEmptyLineWall();
	display->completeBottomWidget(verticalLines);

	int cardChoice = Controller::inputCheck(1, pairEventCardPlayerIndex->size()) - 1;

	Player * playerPlayingCard = players->at(pairEventCardPlayerIndex->at(cardChoice).second);
	EventCard * cardBeingPlayed = pairEventCardPlayerIndex->at(cardChoice).first;



	delete pairEventCardPlayerIndex;
	pairEventCardPlayerIndex = nullptr;


	// Variables needed for switch cases
	Player * player;
	vector<City *> * listOfCities;
	vector<Card *> * discardDeck;
	City * city;
	vector<CityCard *> * forecast;
	CityCard * tempForSwap;
	int userInput = 0;
	bool alreadyResearchCenterInCity = false;

	switch (cardBeingPlayed->getEventId()) {
		// Airlift
	case 1:

		verticalLines = display->mainScreen();
		verticalLines += ConsoleFormat::printEmptyLineWall();
		verticalLines += ConsoleFormat::printLineOfText("Which player would you like to airlift?");
		for (int i = 1; i <= players->size(); ++i) {
			verticalLines += ConsoleFormat::printLineOfText(to_string(i) + ". " + players->at(i - 1)->getPlayerName());
		}
		verticalLines += ConsoleFormat::printEmptyLineWall();
		display->completeBottomWidget(verticalLines);

		player = players->at(Controller::inputCheck(1, players->size()) - 1);
		listOfCities = new vector<City *>;

		userInput = display->cityChoice(player, "Which city would you like to airlift " + player->getPlayerName() + " to?", listOfCities);
		PlayEventCardController::play(new Airlift(player, listOfCities->at(userInput)), playerPlayingCard, cardBeingPlayed);

		delete listOfCities;
		listOfCities = nullptr;
		player = nullptr;
		return;

		// One Quiet Night
	case 2:

		PlayEventCardController::play(new OneQuietNight(), playerPlayingCard, cardBeingPlayed);
		return;

		// Resilient Population
	case 3:

		discardDeck = Session::getInstance()->getInfectionDeck()->getDiscard();
		if (discardDeck->size() == 0) {

			verticalLines = display->mainScreen();
			verticalLines += ConsoleFormat::printEmptyLineWall();
			verticalLines += ConsoleFormat::printLineOfText("Can't remove any card since the discard pile is empty.");
			verticalLines += ConsoleFormat::printEmptyLineWall();
			display->completeBottomWidget(verticalLines);

		}
		else {

			verticalLines = display->mainScreen();
			verticalLines += ConsoleFormat::printEmptyLineWall();
			verticalLines += ConsoleFormat::printLineOfText("Which infection card would you like to remove?");
			for (int i = 1; i <= discardDeck->size(); ++i) {
				verticalLines += ConsoleFormat::printLineOfText(to_string(i) + ". " + discardDeck->at(i - 1)->getTitle());
			}
			verticalLines += ConsoleFormat::printEmptyLineWall();
			display->completeBottomWidget(verticalLines);

			userInput = Controller::inputCheck(1, discardDeck->size()) - 1;

			PlayEventCardController::play(new ResilientPopulation(dynamic_cast<CityCard *>(discardDeck->at(userInput))), playerPlayingCard, cardBeingPlayed);

		}
		return;

		// Government Grant
	case 4:


		do {

			listOfCities = new vector<City *>;

			verticalLines = display->mainScreen();
			verticalLines += ConsoleFormat::printEmptyLineWall();
			verticalLines += ConsoleFormat::printLineOfText("Which city would you like to add a Research Center in?");
			display->listCities(listOfCities, PlayMap::getInstance()->getOrigin());
			verticalLines += ConsoleFormat::printEmptyLineWall();
			display->completeBottomWidget(verticalLines);
			userInput = Controller::inputCheck(1, listOfCities->size()) - 1;

			city = listOfCities->at(userInput);
			if (city->getResearchCenter() == true) {
				alreadyResearchCenterInCity = true;
				verticalLines = display->mainScreen();
				verticalLines += ConsoleFormat::printEmptyLineWall();
				verticalLines += ConsoleFormat::printLineOfText("There aldready is a research center in this city. Try again.");
				verticalLines += ConsoleFormat::printEmptyLineWall();
				display->completeBottomWidget(verticalLines);
			}
			else {
				alreadyResearchCenterInCity = false;
			}
			delete listOfCities;
			listOfCities = nullptr;

		} while (alreadyResearchCenterInCity);

		PlayEventCardController::play(new GovernmentGrant(city), playerPlayingCard, cardBeingPlayed);

		city = nullptr;
		return;

		// Forecast
	case 5:

		forecast = Session::getInstance()->getInfectionDeck()->drawForeCast();

		string numberWord;
		for (int i = 0; i < 6; ++i) {
			switch (i + 1) {
			case 1:
				numberWord = "first";
				break;
			case 2:
				numberWord = "second";
				break;
			case 3:
				numberWord = "third";
				break;
			case 4:
				numberWord = "fourth";
				break;
			case 5:
				numberWord = "fifth";
				break;
			case 6:
				numberWord = "last";
				break;
			}

			verticalLines = display->mainScreen();
			verticalLines += ConsoleFormat::printEmptyLineWall();
			verticalLines += ConsoleFormat::printLineOfText("Which city do you want to draw " + numberWord + "?");
			for (int j = 1; j <= (6 - i); ++j) {
				verticalLines += ConsoleFormat::printLineOfText(to_string(j) + ". " + forecast->at(j - 1 + i)->getTitle());
			}
			verticalLines += ConsoleFormat::printEmptyLineWall();
			display->completeBottomWidget(verticalLines);
			userInput = Controller::inputCheck(1, 6 - i) - 1;

			tempForSwap = forecast->at(i);
			forecast->at(i) = forecast->at(i + userInput);
			forecast->at(i + userInput) = tempForSwap;

			tempForSwap = nullptr;
		}


		PlayEventCardController::play(new Forecast(forecast), playerPlayingCard, cardBeingPlayed);
		forecast = nullptr;
		return;
	}
}

//This method allows a role to be played.
void Controller::playRole()
{
	Player * currentPlayer = Session::getInstance()->getPlayers()->at(Session::getInstance()->getCurrentPlayer());
	vector<Player *> * players = Session::getInstance()->getPlayers();
	int verticalLines = display->mainScreen();
	verticalLines += ConsoleFormat::printEmptyLineWall();

	display->completeBottomWidget(verticalLines);
	switch (currentPlayer->getRole()) {
		;//playrole
	case 1:

		break;
	case 2:

		break;
	case 3:
		playerMove(choseAPlayer());
		break;
	case 4:

		break;
	case 5:

		break;
	case 6:

		break;
	case 7:

		break;
	}

}

void Controller::dispatcher() {

}

Player * Controller::choseAPlayer() {
	Player * currentPlayer = Session::getInstance()->getPlayers()->at(Session::getInstance()->getCurrentPlayer());
	vector<Player *> * players = Session::getInstance()->getPlayers();
	int verticalLines = display->mainScreen();
	verticalLines += ConsoleFormat::printEmptyLineWall();

	Player * chosenPlayer;
	bool consent = false;
	bool wrongChoice = false;

	for (int x = 1; x <= players->size(); ++x) {// chose anotherplayer to control
		if (currentPlayer->getPlayerId() != players->at(x - 1)->getPlayerId()) {
			verticalLines += ConsoleFormat::printLineOfText(to_string(x) + ". " + players->at(x - 1)->getPlayerName());
		}
	}
	do {
		verticalLines += ConsoleFormat::printLineOfText("Chose a player to control.");
		int userInput = inputCheck(1, players->size());
		chosenPlayer = players->at(userInput - 1);
		if (currentPlayer->getPlayerId() == chosenPlayer->getPlayerId())
			wrongChoice = true;
		verticalLines += ConsoleFormat::printLineOfText("Does player " + chosenPlayer->getPlayerName() + " consent?");
		verticalLines += ConsoleFormat::printEmptyLineWall();
		verticalLines += ConsoleFormat::printLineOfText("1. yes");
		verticalLines += ConsoleFormat::printLineOfText("2. no");
		userInput = inputCheck(1, 2);
		if (userInput == 1)
			consent = true;
	} while (!consent || wrongChoice);
	//delete  players;
	//delete currentPlayer;
	//currentPlayer = nullptr;
	//players = nullptr;
	return chosenPlayer;

}

void Controller::handSizeCheck(Player * player) {
	if (player->getHand()->size() <= 7) {
		return;
	}
	bool handContainsEventCard = false;
	for (set<Card*>::iterator it = player->getHand()->begin(); it != player->getHand()->end(); ++it) {
		if (dynamic_cast<EventCard *>(*it) != nullptr) {
			handContainsEventCard = true;
			break;
		}
	}
	if (handContainsEventCard) {
		while (player->getHand()->size() > 7) {
			playEventCardOrDiscard(player);
		}
	}
	else {
		while (player->getHand()->size() > 7) {
			Card * card = cardSelection(player, "Which card would you like to discard?");
			player->discardCard(card);
			card = nullptr;
		}
	}
}

Card * Controller::cardSelection(Player * player, string message) {
	vector<Card *> * cards = new vector<Card *>;
	int verticalLines = 0;
	verticalLines += display->mainScreen();
	verticalLines += ConsoleFormat::printEmptyLineWall();
	verticalLines += ConsoleFormat::printLineOfText(message);
	verticalLines += ConsoleFormat::printEmptyLineWall();
	int iterationNumber = 0;
	for (set<Card*>::iterator it = player->getHand()->begin(); it != player->getHand()->end(); ++it) {
		++iterationNumber;
		cards->push_back(*it);
		verticalLines += ConsoleFormat::printLineOfText(to_string(iterationNumber) + ". " + (*it)->getTitle());

	}
	verticalLines += ConsoleFormat::printEmptyLineWall();
	display->completeBottomWidget(verticalLines);
	int cardChoice = Controller::inputCheck(1, cards->size()) - 1;

	Card * cardToReturn = cards->at(cardChoice);

	delete cards;
	cards = nullptr;

	return cardToReturn;
}

void Controller::regularMapInitialization()
{
	static Session * session = Session::getInstance();
	session->addLocation("Atlanta", 1);
	session->addLocation("San Francisco", 1);
	session->addLocation("Chicago", 1);
	session->addLocation("Montreal", 1);
	session->addLocation("Washington", 1);
	session->addLocation("New York", 1);
	session->addLocation("Londres", 1);
	session->addLocation("Madrid", 1);
	session->addLocation("Paris", 1);
	session->addLocation("Essen", 1);
	session->addLocation("Saint-Petersbourg", 1);
	session->addLocation("Milan", 1);

	session->addLocation("Los Angeles", 2);
	session->addLocation("Miami", 2);
	session->addLocation("Mexico", 2);
	session->addLocation("Bogota", 2);
	session->addLocation("Lima", 2);
	session->addLocation("Santiago", 2);
	session->addLocation("Sao Paulo", 2);
	session->addLocation("Buenos Aires", 2);
	session->addLocation("Johannesburg", 2);
	session->addLocation("Kinshasa", 2);
	session->addLocation("Lagos", 2);
	session->addLocation("Khartoum", 2);

	session->addLocation("Alger", 3);
	session->addLocation("Le Caire", 3);
	session->addLocation("Istanbul", 3);
	session->addLocation("Moscou", 3);
	session->addLocation("Bagdad", 3);
	session->addLocation("Teheran", 3);
	session->addLocation("Karachi", 3);
	session->addLocation("Riyad", 3);
	session->addLocation("Delhi", 3);
	session->addLocation("Mumbai", 3);
	session->addLocation("Calcutta", 3);
	session->addLocation("Chennai", 3);

	session->addLocation("Pekin", 4);
	session->addLocation("Seoul", 4);
	session->addLocation("Shanghai", 4);
	session->addLocation("Tokyo", 4);
	session->addLocation("Osaka", 4);
	session->addLocation("Taipei", 4);
	session->addLocation("Hong Kong", 4);
	session->addLocation("Bangkok", 4);
	session->addLocation("Manille", 4);
	session->addLocation("Ho-Chi-Minh-Ville", 4);
	session->addLocation("Jakarta", 4);
	session->addLocation("Sydney", 4);

	session->connectCity("San Francisco", "Tokyo", true);
	session->connectCity("San Francisco", "Manille", true);
	session->connectCity("Los Angeles", "Sydney", true);
	session->connectCity("New York", "Londres", true);
	session->connectCity("New York", "Madrid", true);
	session->connectCity("Madrid", "Sao Paulo", true);
	session->connectCity("Lagos", "Sao Paulo", true);
	session->connectCity("Johannesburg", "Buenos Aires", true);
	session->connectCity("San Francisco", "Los Angeles", true);
	session->connectCity("San Francisco", "Chicago", true);
	session->connectCity("Los Angeles", "Chicago", true);
	session->connectCity("Los Angeles", "Mexico", true);
	session->connectCity("Los Angeles", "Lima", true);
	session->connectCity("Mexico", "Lima", true);
	session->connectCity("Santiago", "Lima", true);
	session->connectCity("Bogota", "Lima", true);
	session->connectCity("Santiago", "Buenos Aires", true);
	session->connectCity("Chicago", "Mexico", true);
	session->connectCity("Chicago", "Atlanta", true);
	session->connectCity("Chicago", "Montreal", true);
	session->connectCity("Bogota", "Mexico", true);
	session->connectCity("Miami", "Mexico", true);
	session->connectCity("Bogota", "Miami", true);
	session->connectCity("Bogota", "Sao Paulo", true);
	session->connectCity("Bogota", "Buenos Aires", true);
	session->connectCity("Sao Paulo", "Buenos Aires", true);
	session->connectCity("Atlanta", "Washington", true);
	session->connectCity("Atlanta", "Miami", true);
	session->connectCity("Washington", "Miami", true);
	session->connectCity("Washington", "Montreal", true);
	session->connectCity("Washington", "New York", true);
	session->connectCity("Montreal", "New York", true);
	session->connectCity("Lagos", "Kinshasa", true);
	session->connectCity("Lagos", "Khartoum", true);
	session->connectCity("Khartoum", "Kinshasa", true);
	session->connectCity("Khartoum", "Johannesburg", true);
	session->connectCity("Kinshasa", "Johannesburg", true);
	session->connectCity("Khartoum", "Le Caire", true);
	session->connectCity("Londres", "Madrid", true);
	session->connectCity("Londres", "Paris", true);
	session->connectCity("Londres", "Essen", true);
	session->connectCity("Paris", "Madrid", true);
	session->connectCity("Alger", "Madrid", true);
	session->connectCity("Alger", "Paris", true);
	session->connectCity("Alger", "Le Caire", true);
	session->connectCity("Alger", "Istanbul", true);
	session->connectCity("Paris", "Essen", true);
	session->connectCity("Paris", "Milan", true);
	session->connectCity("Milan", "Essen", true);
	session->connectCity("Saint-Petersbourg", "Essen", true);
	session->connectCity("Milan", "Istanbul", true);
	session->connectCity("Saint-Petersbourg", "Istanbul", true);
	session->connectCity("Saint-Petersbourg", "Moscou", true);
	session->connectCity("Le Caire", "Istanbul", true);
	session->connectCity("Bagdad", "Istanbul", true);
	session->connectCity("Moscou", "Istanbul", true);
	session->connectCity("Le Caire", "Bagdad", true);
	session->connectCity("Le Caire", "Riyad", true);
	session->connectCity("Moscou", "Teheran", true);
	session->connectCity("Bagdad", "Teheran", true);
	session->connectCity("Bagdad", "Riyad", true);
	session->connectCity("Karachi", "Riyad", true);
	session->connectCity("Karachi", "Teheran", true);
	session->connectCity("Karachi", "Delhi", true);
	session->connectCity("Karachi", "Mumbai", true);
	session->connectCity("Teheran", "Delhi", true);
	session->connectCity("Mumbai", "Delhi", true);
	session->connectCity("Calcutta", "Delhi", true);
	session->connectCity("Chennai", "Delhi", true);
	session->connectCity("Mumbai", "Chennai", true);
	session->connectCity("Calcutta", "Chennai", true);
	session->connectCity("Jakarta", "Chennai", true);
	session->connectCity("Calcutta", "Bangkok", true);
	session->connectCity("Calcutta", "Hong Kong", true);
	session->connectCity("Pekin", "Seoul", true);
	session->connectCity("Pekin", "Shanghai", true);
	session->connectCity("Seoul", "Shanghai", true);
	session->connectCity("Tokyo", "Shanghai", true);
	session->connectCity("Taipei", "Shanghai", true);
	session->connectCity("Hong Kong", "Shanghai", true);
	session->connectCity("Seoul", "Tokyo", true);
	session->connectCity("Osaka", "Tokyo", true);
	session->connectCity("Osaka", "Taipei", true);
	session->connectCity("Hong Kong", "Taipei", true);
	session->connectCity("Manille", "Taipei", true);
	session->connectCity("Hong Kong", "Manille", true);
	session->connectCity("Hong Kong", "Bangkok", true);
	session->connectCity("Hong Kong", "Ho-Chi-Minh-Ville", true);
	session->connectCity("Bangkok", "Ho-Chi-Minh-Ville", true);
	session->connectCity("Jakarta", "Ho-Chi-Minh-Ville", true);
	session->connectCity("Manille", "Ho-Chi-Minh-Ville", true);
	session->connectCity("Jakarta", "Bangkok", true);
	session->connectCity("Jakarta", "Sydney", true);
	session->connectCity("Manille", "Sydney", true);

}
