#include "Subject.h"
#include "Observer.h"

Subject::Subject(){
	_observers = new list<Observer*>;
}
Subject::~Subject(){ 
	delete _observers;
}
void Subject::Attach(Observer* o){
  _observers->push_back(o);
};
void Subject::Detach(Observer* o){
  _observers->remove(o);
};
void Subject::Notify(){
  list<Observer *>::iterator i = _observers->begin();
  for (; i != _observers->end(); ++i)
	(*i)->Update(); 
};
void Subject::Notify(string message) {
	list<Observer *>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->Update(message);
};
void Subject::Notify(vector<string> * log) {
	list<Observer *>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->Update(log);
};