#pragma once

#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <future>

#include <MidiFile.h>

#include <Interfaces.h>

#include "csv.h"

class Music
{
public:
	Music();
	~Music();

    void loop();
	void pause();
	void run();
    void play();
    void load(std::string path);
	void stop();
private:

    bool playing();

    std::mutex noteMutex;
    std::condition_variable noteCondition;
    //std::thread musicThread;
    std::vector<int> noteID, noteFreq;

	std::future<bool> playTask;

    std::chrono::steady_clock::time_point trackTimePoint;
	std::chrono::steady_clock::duration trackPauseDuration;

    smf::MidiEventList trackEventList;
    int currentEvent = 0;
    bool isPlaying;
	bool isStopping;
    bool isLooping;
    bool isPaused;
	bool isStop;

    int midiNumberOfEvents;

};

