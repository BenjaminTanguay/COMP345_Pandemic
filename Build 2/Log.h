#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>



using namespace std;

class Log
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	inline void serialize(Archive & ar, const unsigned int version)
	{
		ar & log;
		ar & messages;
	}

	bool log;
	vector<string> * messages;

public:
	Log();
	~Log();

	void startLog();
	void stopLog();
	bool recordLog();

	void stringToLog(string message);
	void vectorToLog(vector<string> * message);
};

