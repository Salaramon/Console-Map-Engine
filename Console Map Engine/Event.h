#pragma once

#include <Windows.h>
#include <vector>
#include <chrono>

#include <Interfaces.h>

typedef char KEY;
struct Key {
	Key(char charCode, bool stateCode) : charCode(charCode), stateCode(stateCode) {}
	char charCode;
	bool stateCode;

	static const bool RELEASED = 0;
	static const bool PRESSED = 1;

	static const KEY W = 0x57;
	static const KEY A = 0x41;
	static const KEY S = 0x53;
	static const KEY D = 0x44;
	static const KEY E = 0x45;
	static const KEY ESC = 0x1B;
	static const KEY LSHIFT = 0xA0;
};

typedef std::vector<Key> Keys;

class Event : protected iul::Subject<Keys, double_t>
{
public:
	Event();

	struct Receiver : public iul::Observer<Keys, double_t> {

		virtual void observerResponse(Keys keys, double_t timeStamp) override {
			response(keys, timeStamp);
		};
		virtual void response(Keys key, double_t timeStamp) = 0;
	};

	void addReceiver(Event::Receiver* receiver, size_t priority);
	void pollEvents();
	void transmitEvents();
	bool anyEvent();

	static double_t deltaTime;
	static const size_t PRIORITY_LAST = SIZE_MAX;
	static double_t timeElapsed;

private:

	std::vector<Key> keyStack;
	double_t eventTime;
	size_t priorityMax;
	HANDLE handleInput;
	BYTE keyboardStateIgnoreList[256];
	std::vector<bool> wasPressed;
	static std::chrono::steady_clock::time_point runTime;

};

