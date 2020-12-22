#pragma once

#include <cstdint>
#include <cmath>

#include <boost/serialization/split_member.hpp>

#include "ViewFrame.h"

class Scape
{

	friend boost::serialization::access;

	template <class Archive>
	void save(Archive& ar, const unsigned int version) const {
		ar& x;
		ar& y;
		ar& w;
		ar& h;
	}
	template <class Archive>
	void load(Archive& ar, const unsigned int version) {
		ar& x;
		ar& y;
		ar& w;
		ar& h;
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER()

public:
	size_t w, h;
	double_t x, y;
	virtual const char at(intmax_t x, intmax_t y) = 0;
	ViewFrame getViewFrame(size_t x, size_t y);
	void move(double_t x, double_t y);

};

