#pragma once
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/assume_abstract.hpp>





using namespace std;

class Card
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version){}
public:
	Card();
	virtual ~Card();

	virtual void read() = 0;
	virtual string getTitle() = 0;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Card);

