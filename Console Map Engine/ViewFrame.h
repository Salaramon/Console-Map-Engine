#pragma once

#include <boost/serialization/split_member.hpp>

class ViewFrame
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
	ViewFrame();
	ViewFrame(size_t x, size_t y, size_t w, size_t h);

	void move(size_t x, size_t y);
	

	size_t x, y, w, h;
};

