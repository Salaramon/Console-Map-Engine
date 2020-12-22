#include "Event.h"

std::chrono::steady_clock::time_point Event::runTime = std::chrono::steady_clock::now();
double_t Event::deltaTime = 0;
double_t Event::timeElapsed = 0;

Event::Event()
{
	wasPressed = std::vector<bool>(256, false);
	handleInput = GetStdHandle(STD_INPUT_HANDLE);
}

void Event::addReceiver(Event::Receiver* receiver, size_t priority)
{
	if (priority > priorityMax) {
		priorityMax = priority;
	}
	addObserver(receiver, priority);
}

void Event::pollEvents() {

	//Get timings
	double_t newElapsed = std::chrono::duration<double>(std::chrono::steady_clock::now() - runTime).count();
	deltaTime = newElapsed - timeElapsed;
	timeElapsed = newElapsed;
	eventTime = timeElapsed;

	//Key stack retriever
	for (int i = 0; i < 256; i++) {
		SHORT checkKey;
		if (i != 240 && i != 242) {
			checkKey = GetKeyState(i);
			SHORT shift = ((sizeof(SHORT) * 8) - 1);
			SHORT keyCode = checkKey & (1 << shift);
			bool keyIsPressed = keyCode;
			if (keyIsPressed) {
				if (wasPressed[i]) {
					keyStack.push_back(Key(i, false));
				}
				else {
					keyStack.push_back(Key(i, true));
				}
				wasPressed[i] = true;
			}
			else {
				wasPressed[i] = false;
			}
		}
	}
}

void Event::transmitEvents()
{
	//Notify all clients with occured events
	for (size_t order = 0; order <= priorityMax; order++) {

		if (!keyStack.empty()) {
				notifyObservers(keyStack, eventTime, order);
		}
	}
	keyStack.clear();
}

bool Event::anyEvent() {
	return !keyStack.empty();
}