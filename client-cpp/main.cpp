#include <iostream>
#include <Windows.h>
#include <thread>
#include <queue>
#include <mutex>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include "Track.h"
#include "MusicPlayer.h"
using namespace std;
using namespace web::http::client;
using namespace web::http;

// TODO: What does this do? 
#pragma comment(lib, "Winmm.lib")

#define NUM_SONGS 4
string song_names[NUM_SONGS] = { "piano", "wonder", "birds", "space" };

queue<struct cmd_type> g_command_queue;
mutex g_command_mutex;


constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

void printUsage() {
	cout << "/* ------------------------------------ */" << endl;
	cout << "USAGE: " << endl;
	cout << "\t play: Plays a specific song, will be asked for track number" << endl;
	cout << "\t stop: Stops music that is currently playing" << endl;
	cout << "\t list: Lists available tracks with each track number" << endl;
	cout << "/* ------------------------------------ */\n" << endl;
}

// Take user input, feed info to Command Queue
void userInput() 
{
	string user_input;
	cmd_type cmd;

	for (;;) {
		cout << "Enter a command:  ";
		cin >> user_input;

		// Some string recognition for commands
		switch (str2int(user_input.c_str())) {
		case(str2int("play")):
			cmd.cmd = PLAY;
			cout << "Choose track number: ";
			cin >> cmd.track_num;
			break;

		case(str2int("stop")):
			cmd.cmd = STOP;
			break;

		case(str2int("list")):
			cmd.cmd = LIST;
			break;

		default:
			printUsage();
			break;
		}

		// Lock mutex, put message in queue
		g_command_mutex.lock();
		g_command_queue.push(cmd);
		g_command_mutex.unlock();
	}
}

// Listen for user input from Command Queue, print that information in thread
void musicPlayer(MusicPlayer *mplyr) 
{
	string last_msg = "Default", cur_msg = "";
	int cur_song = 0;
	cmd_type cmd = *((struct cmd_type *) calloc(1, sizeof(cmd_type)));

	for (;;) {

		// Pop a command message from the queue, if not empty
		if (!g_command_queue.empty()) {

			g_command_mutex.lock();
			cmd = g_command_queue.front();
			g_command_queue.pop();
			g_command_mutex.unlock();

			switch (cmd.cmd)
			{
			case(PLAY):
				mplyr->playSingle(cmd.track_num);
				break;

			case(STOP):
				mplyr->stop();
				break;

			case(LIST):
				mplyr->printTracklist();
				break;
			}
		}

		Sleep(1000);
	}
}

// Creates an HTTP request and prints the length of the response stream.
pplx::task<void> HTTPStreamingAsync()
{
	http_client client(L"http://localhost:8080/list");

	// Make the request and asynchronously process the response. 
	return client.request(methods::GET).then([](http_response response)
		{
			// Print the status code.
			std::wostringstream ss;
			ss << L"Server returned returned status code " << response.status_code() << L'.' << std::endl;
			std::wcout << ss.str();

			// TODO: Perform actions here reading from the response stream.
			auto bodyStream = response.body();
			cout << "Body:" << endl << response.body() << endl;

			// In this example, we print the length of the response to the console.
			ss.str(std::wstring());
			ss << L"Content length is " << response.headers().content_length() << L" bytes." << std::endl;
			std::wcout << ss.str();
		});

	/* Sample output:
	Server returned returned status code 200.
	Content length is 63803 bytes.
	*/
}


int main() 
{	
	std::wcout << L"Calling HTTPStreamingAsync..." << std::endl;
    HTTPStreamingAsync().wait();


	/*
	string user_input;
	Track track;
	MusicPlayer mplyr;

	// Load up the tracklist
	for (int i = 0; i < NUM_SONGS; i++) {
		if (track.setTrack(song_names[i]))
			mplyr.addTrack(&track);
	}

	// Create threads
	thread player(musicPlayer, &mplyr);
	thread user(userInput);

	player.join();
	user.join();
	*/
	
	return 0;

}