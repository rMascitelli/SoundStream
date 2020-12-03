// Track class definiton
#include "Track.h"
#include <iostream>
#include <Windows.h>
using namespace std;

// TODO: What is an inline + static function?
inline bool file_exists(const std::string& name) {
	if (FILE* file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}

Track::Track() {
	track_id = 0;
	filename = "";
	filepath = "";
}

string Track::getFileName() {
	return filename;
}

string Track::getFilePath() {
	return filepath;
}

unsigned Track::getTrackID() {
	return track_id;
}

int Track::setTrack(string sname) {

	// For now, just look in our directory to see if the file exists
	const string temp_str = "wav_files/" + sname + ".wav";				// TODO: Add "media_format" member
	if (file_exists(temp_str)) {
		track_id = 101;				// TODO: Eventually have a function to generate an "ID"
		filename = sname + ".wav";
		filepath = temp_str;

		return 1;
	}
	else {
		return 0;
	}
}
