#include <iostream>
#include <windows.h> 
#include "Display.h"
#include "conio.h"
#include "tchar.h"
#include <iostream>
#include <fstream>
#include "Location.h"
#include "Player.h"
#include "Session.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
using namespace std;


int main() {
	static Session & session = Session::getInstance();
	Display * display = new Display();
	display->welcomeSceen();
	delete display;
	display = nullptr;
	return 0;
}

//66 lines tall, 1 line to clear.
//271 chars wide