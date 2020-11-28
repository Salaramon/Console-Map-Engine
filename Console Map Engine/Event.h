#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
#include <chrono>

#include <boost/serialization/split_member.hpp>

#include <Interfaces.h>


struct Key {
	Key(WORD key, bool pressedAction, double time, size_t cycle) {
		charCode = key;
		stateCode = pressedAction;
		timeStamp = time;
		eventCycle = cycle;
	}

	char charCode;
	bool stateCode;
	double timeStamp;
	size_t eventCycle;

	static const bool RELEASED = 0;
	static const bool PRESSED = 1;

	static const char W = 0x57;
	static const char A = 0x41;
	static const char S = 0x53;
	static const char D = 0x44;
	static const char E = 0x45;
	static const char ESC = 0x1B;
};

class Event : protected iul::Subject<Key>
{
public:
	Event();

	struct Receiver : public iul::Observer<Key> {

		friend boost::serialization::access;

		template <class Archive>
		void save(Archive& ar, const unsigned int version) const {

		}
		template <class Archive>
		void load(Archive& ar, const unsigned int version) {
			
		}
		BOOST_SERIALIZATION_SPLIT_MEMBER()

		virtual void observerResponse(Key key) override {
			response(key);
		};
		virtual void response(Key key) = 0;
	};

	void addReceiver(Event::Receiver* receiver, size_t priority);

	void transmitEvents();

	static const size_t PRIORITY_LAST = SIZE_MAX;
private:
	size_t priorityMax;
	HANDLE handleInput;
	BYTE keyboardStateIgnoreList[256];
	std::vector<bool> wasPressed;
	std::chrono::steady_clock::time_point runTime = std::chrono::steady_clock::now();
	size_t runCycle = 0;

};

