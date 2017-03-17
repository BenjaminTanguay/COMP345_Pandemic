#pragma once
#include "Subject.h"
#include <string>
#include <vector>

//Needs to have a forward reference due to 
//circular reference between Observer and Subject
class Subject;

using namespace std;

class Observer {
public:
	~Observer();
	virtual void Update() = 0;
	virtual void Update(string message) = 0;
	virtual void Update(vector<string> * log) = 0;
protected:
	Observer();
};
