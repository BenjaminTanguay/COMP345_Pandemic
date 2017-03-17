#pragma once
#include "Observer.h"
#include <list>
#include <string>
#include <vector>
using namespace std;

//Needs to have a forward reference due to 
//circular reference between Observer and Subject
class Observer;

class Subject {
  public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify();
	virtual void Notify(string message);
	virtual void Notify(vector<string>* log);
	Subject();
	~Subject();
  private:
	list<Observer*> *_observers;
};
