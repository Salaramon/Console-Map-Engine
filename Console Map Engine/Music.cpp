#include "Music.h"

Music::Music()
{
    isPlaying = false;
	isStop = false;
	isLooping = false;
	isPaused = false;

	//Load correct note frequencies
    io::CSVReader<2> noteChart("FrequencyChart.csv");
    int note; double freq;
    while (noteChart.read_row(note, freq)) {
        noteID.push_back(note);
        noteFreq.push_back(freq);
    }
}

Music::~Music()
{
	//Make sure main thread does not continue before playing thread is done
	stop();
	playTask.wait();
}

void Music::load(std::string path)
{
    std::ifstream file(path);
    smf::MidiFile midiFile;
    midiFile.read(file);
    file.close();
    midiFile.mergeTracks(0, 1);
    midiFile.doTimeAnalysis();
    midiNumberOfEvents = midiFile.getEventCount(0);

    trackEventList = midiFile[0];
    trackEventList.linkNotePairs();
}

void Music::stop()
{
	isStop = true;
	isPlaying = false;
	isPaused = false;
}

bool Music::_play() //_play
{
    std::unique_lock<std::mutex> owned_noteMutex(noteMutex);

	//Music loop
    int i = 0;
    while (isPlaying) {
		if (trackEventList[i].isNoteOn()) {

			auto nextNoteIterator = std::find(noteID.begin(), noteID.end(), (int)trackEventList[i][1]);
			int noteIndex = std::distance(noteID.begin(), nextNoteIterator);
			noteCondition.wait(owned_noteMutex, [&]() {
				return trackEventList[i].seconds < trackCurrentPoint || isStop;
			});
			Beep(noteFreq[noteIndex], static_cast<int>(1000 * trackEventList[i].getDurationInSeconds())); //If statemun dis bith up on quit

		}

		i++;
		if (i >= midiNumberOfEvents) {
			i = 0;
			trackCurrentPoint = 0;
			if (!isLooping) {
				isPlaying = false;
			}
		}
		
    }

	return false;
}

void Music::play()
{
    if (!isPlaying) {
        isPlaying = true;
        playTask = std::async(std::launch::async, &Music::_play, this);
    }
    else {
		if (isPaused) {
			isPaused = false;
		}
	}
}

void Music::loop()
{
    isLooping = true;
}

void Music::pause() {
	isPaused = true;
}

void Music::run() {
	if ((!isPaused || !isStop) && isPlaying) {
		trackCurrentPoint += Event::deltaTime;
		noteCondition.notify_all();
	}
}