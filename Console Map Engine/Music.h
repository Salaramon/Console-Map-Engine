#pragma once

#include <string>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <Windows.h>
#include <future>

#include <MidiFile.h>

#include <Interfaces.h>

#include "csv.h"

#include "Event.h"

class Music
{
public:
	Music();
	~Music();

	void load(std::string path);

	//Checks in with the main thread to be able to continue playing.
	void run();

    void play();
	void loop();
	void pause();
	void stop();
private:

	//play thread
    bool _play();

    std::mutex noteMutex;
    std::condition_variable noteCondition;
	std::future<bool> playTask;

	//music player variables
	double_t trackCurrentPoint;
	std::vector<int> noteID, noteFreq;
    smf::MidiEventList trackEventList;
	int currentEvent = 0;
	int midiNumberOfEvents;

	//Play state variables
    bool isPlaying;
	bool isStopping;
    bool isLooping;
    bool isPaused;
	bool isStop;

};

