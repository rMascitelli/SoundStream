#pragma once
#include <vector>
#include "Track.h"

// Use this enum + struct for the Queue in main.cpp
enum CMD {
	PLAY = 1,
	STOP = 2,
	LIST = 3
};

struct cmd_type {
	CMD cmd;
	int track_num;
};

// TODO: public vs private inheritance? 
class MusicPlayer {

public:
	MusicPlayer();
	void play();
	void stop();
	void addTrack(Track* track);
	void playSingle(int track_number);
	void printTracklist();

	unsigned player_id;
	std::vector<Track> tracklist;

private:
	
};