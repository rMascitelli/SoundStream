#include <iostream>
#include <Windows.h>
#include "MusicPlayer.h"
using namespace std;

MusicPlayer::MusicPlayer() {
	player_id = 0;
	tracklist = *((vector<Track> *) calloc(5, sizeof(Track)));
	cout << "Created new MusicPlayer instance!" << endl;
}

void MusicPlayer::addTrack(Track* track)
{
	tracklist.push_back(*track);
}

void MusicPlayer::printTracklist() 
{
	// Print out all elements of the tracklist
	cout << "\nTracklist: \n";
	for (int i = 0; i < tracklist.size(); i++) {
		printf("[%d]: %s\n", i, tracklist[i].getFileName().c_str());
	}
	cout << endl;
}

void MusicPlayer::play()
{
	Track current_track;
	int i;

	if (!tracklist.empty()) {
		for (i = 0; i < tracklist.size(); i++) {
			current_track = tracklist[i];
			string tname = current_track.getFilePath();

			std::wstring stemp = std::wstring(tname.begin(), tname.end());
			cout << "Trying to play: " << current_track.getFilePath() << endl;
			LPCWSTR test_str = stemp.c_str();

			// TODO: Not using ASYNC flag means this PlaySound() is NON-INTERRUPTABLE!
			PlaySound(test_str, GetModuleHandle(NULL), SND_FILENAME);
		}
	}
	else {
		cout << "MusicPlayer tracklist is empty!" << endl;
	}

}

void MusicPlayer::playSingle(int track_number)
{
	Track current_track;
	cout << "Playing song " << track_number << endl;

	// Tracklist must be non-empty, and must be given valid track_number
	if (!tracklist.empty() || !(track_number > tracklist.size())) {
			string tname = tracklist[track_number].getFilePath();
			std::wstring stemp = std::wstring(tname.begin(), tname.end());

			
			LPCWSTR test_str = stemp.c_str();
			PlaySound(test_str, GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
			//PlaySound(NULL, GetModuleHandle(NULL), SND_FILENAME);
	}
	else {
		cout << "MusicPlayer tracklist is empty!" << endl;
	}


}

void MusicPlayer::stop()
{
	PlaySound(NULL, 0, 0);
}

