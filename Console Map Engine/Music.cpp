#include "Music.h"

Music::Music()
{
    isPlaying = false;
	isStop = false;
	isLooping = false;
	isPaused = false;
	trackPauseDuration = std::chrono::steady_clock::duration::zero();
    io::CSVReader<2> noteChart("FrequencyChart.csv");
    int note; double freq;
    while (noteChart.read_row(note, freq)) {
        noteID.push_back(note);
        noteFreq.push_back(freq);
    }
}

Music::~Music()
{
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
}

bool Music::playing() //_play
{
    trackTimePoint = std::chrono::steady_clock::now();
    std::unique_lock<std::mutex> owned_noteMutex(noteMutex);

    int i = 0;
    while (isPlaying) {
		if (trackEventList[i].isNoteOn()) {
			

			auto nextNoteIterator = std::find(noteID.begin(), noteID.end(), (int)trackEventList[i][1]);
			int noteIndex = std::distance(noteID.begin(), nextNoteIterator);
			noteCondition.wait(owned_noteMutex, [&]() {
				return (trackEventList[i].seconds < (std::chrono::duration<double>(std::chrono::steady_clock::now() - trackTimePoint - trackPauseDuration)).count() && !isPaused) || isStop;
			});
			Beep(noteFreq[noteIndex], static_cast<int>(1000 * trackEventList[i].getDurationInSeconds())); //If statemun dis bith up on quit

		}

		i++;
		if (i >= midiNumberOfEvents) {
			i = 0;
			trackTimePoint = std::chrono::steady_clock::now();
			trackPauseDuration = std::chrono::steady_clock::duration::zero();
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
        playTask = std::async(std::launch::async, &Music::playing, this);
    }
    else {
		if (isPaused) {
			isPaused = false;
			trackPauseDuration = std::chrono::steady_clock::now() - trackTimePoint;
		}
		else {
			std::cout << "Music is already playing!" << std::endl;
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
	noteCondition.notify_all();
}