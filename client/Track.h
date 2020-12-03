#pragma once
#include <string>

class Track {
public:
	std::string getFileName();
	std::string getFilePath();
	unsigned getTrackID();

	Track();

	int setTrack(std::string sname);
	int setTrackID(unsigned id);

private:
	unsigned track_id;
	std::string filename;
	std::string filepath;
};