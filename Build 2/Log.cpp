#include "Log.h"



Log::Log()
{
	messages = new vector<string>;
}


Log::~Log()
{
	delete messages;
	messages = nullptr;
}

void Log::startLog()
{
	log = true;
}

void Log::stopLog()
{
	log = false;
}

bool Log::recordLog()
{
	if (!log) {
		return false;
	}
	ofstream logFile;
	logFile.open("Log.txt");
	if (logFile.is_open())
	{
		for (int i = 0; i < messages->size(); ++i) {
			logFile << messages->at(i) << endl;
		}
		logFile.close();
		return true;
	}
	else {
		cout << "Can't open the file to write" << endl;
		return false;
	}
}

void Log::stringToLog(string message)
{
	if (!log) {
		return;
	}
	messages->push_back(message);
}

void Log::vectorToLog(vector<string>* message)
{
	if (!log) {
		return;
	}
	for (int i = 0; i < message->size(); ++i) {
		messages->push_back(message->at(i));
	}
}
