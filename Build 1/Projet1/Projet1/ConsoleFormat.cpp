#include "ConsoleFormat.h"

HANDLE ConsoleFormat::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

ConsoleFormat::ConsoleFormat()
{
}


ConsoleFormat::~ConsoleFormat()
{
}

int ConsoleFormat::printWall() {
	int spacing = 5;
	setColor(black, white);
	cout << "|" << setw(spacing) << left << " ";
	return spacing;
}

int ConsoleFormat::printEmptyLineWall() {
	setColor(black, white);
	cout << setw(270) << left << "|" << "|";
	return 1;
}

void ConsoleFormat::setColor(int background, int color) {
	SetConsoleTextAttribute(hConsole, (background * 16) + color);
}

void ConsoleFormat::printRightWall(int numberOfCharsUsedInLine) {
	setColor(black, white);
	for (int i = 0; i < (269 - numberOfCharsUsedInLine); ++i) {
		cout << " ";
	}
	cout << "|";
}

string ConsoleFormat::emptySpaces(int spaces) {
	string temp = "";
	for (int i = 0; i < spaces; ++i) {
		temp += " ";
	}
	return temp;
}

void ConsoleFormat::printLine() {
	setColor(black, white);
	cout << "|";
	for (int i = 1; i < 270; ++i) {
		cout << "-";
	}
	cout << "|";
}

int ConsoleFormat::makeBox(int length, string sentence, string data, int maxDataSize) {
	cout << setw(length) << left << emptySpaces(2) + sentence;
	int spacesToPad = maxDataSize - data.length();
	cout << emptySpaces(spacesToPad) << data << emptySpaces(2);
	return length + maxDataSize + 2;
}

int ConsoleFormat::makeBox(int length, string data) {
	cout << emptySpaces(2) + data + emptySpaces(length + 2 - data.size());
	return length + 4;
}

int ConsoleFormat::blockColor(City * city, int division) {
	int lines = 0;
	if (city->containPlayer(0)) {
		setColor(dgreen, white);
		lines += makeBox(division, "");
	}
	if (city->containPlayer(1)) {
		setColor(dred, white);
		lines += makeBox(division, "");
	}
	if (city->containPlayer(2)) {
		setColor(white, black);
		lines += makeBox(division, "");
	}
	if (city->containPlayer(3)) {
		setColor(teal, black);
		lines += makeBox(division, "");
	}
	return lines;
}

void ConsoleFormat::setColor(int region) {
	switch (region) {
	case 1:
		setColor(blue, white);
		break;
	case 2:
		setColor(yellow, black);
		break;
	case 3:
		setColor(black, white);
		break;
	case 4:
		setColor(red, white);
		break;
	}
}

int ConsoleFormat::printLineOfText(string text)
{
	int numberOfChars = 0;

	numberOfChars += printWall();
	numberOfChars += text.length();
	cout << text;
	printRightWall(numberOfChars);
	return 1;
}