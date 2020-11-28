#include "Event.h"

Event::Event()
{
	wasPressed = std::vector<bool>(256, false);
	handleInput = GetStdHandle(STD_INPUT_HANDLE);
	GetKeyboardState(&keyboardStateIgnoreList[0]);
}

void Event::addReceiver(Event::Receiver* receiver, size_t priority)
{
	if (priority > priorityMax) {
		priorityMax = priority;
	}
	addObserver(receiver, priority);
}

void Event::transmitEvents()
{
	std::vector<SHORT> keyEventStack;
	std::vector<bool> keyStateStack;
	SHORT checkKey;

	for (int i = 0; i < 256; i++) {
		if (i != 240 && i != 242) {
			checkKey = GetKeyState(i);
			SHORT shift = ((sizeof(SHORT) * 8) - 1);
			SHORT keyCode = checkKey & (1 << shift);
			bool keyIsPressed = keyCode;

			if (keyIsPressed != wasPressed[i]) {
				keyStateStack.push_back((wasPressed[i] ^ keyIsPressed) & keyIsPressed);
				keyEventStack.push_back(i);
				wasPressed[i] = keyStateStack.back();
			}

			if (keyIsPressed && wasPressed[i]) {
				keyStateStack.push_back(false);
				keyEventStack.push_back(i);
			}
		}
	}

	for (size_t order = 0; order <= priorityMax; order++) {

		if (!keyEventStack.empty()) {
			for (int i = 0; i < keyEventStack.size(); i++) {
				double time = std::chrono::duration<double>(std::chrono::steady_clock::now() - runTime).count();
				notifyObservers(Key(keyEventStack[i], keyStateStack[i], time, runCycle), order);
			}
		}
		if (priorityMax == order && !keyEventStack.empty()) {
			runCycle++;
		}
		
	}
	

}
