// A very simple exampe of inter-thread communication
// Passing a string msg between threads using a mutex-protected STL queue

#include <iostream>
#include <Windows.h>
#include <thread>
#include <queue>
#include <mutex>

using namespace std;

queue<string> g_command_queue;
mutex g_command_mutex;

// Take user input, feed info to Command Queue
void userInput() {
	string user_input;

	for (;;) {
		cout << "Enter a command:  \n";
		cin >> user_input;

		// Lock mutex, put message in queue
		g_command_mutex.lock();
		g_command_queue.push(user_input);
		g_command_mutex.unlock();
	}
}

// Listen for user input from Command Queue, print that information in thread
void musicPlayer() {
	string last_msg = "Default", cur_msg = "";

	for (;;) {

		g_command_mutex.lock();
		if (!g_command_queue.empty()) {
			cur_msg = g_command_queue.front();
			g_command_queue.pop();
		}
		g_command_mutex.unlock();
		
		if((cur_msg != last_msg) && cur_msg != "") {
			cout << "Received: " << cur_msg << endl;
			cur_msg = last_msg;
		}
		

		Sleep(1000);
	}
	
}

int main() 
{
	thread player(musicPlayer);
	thread user(userInput);
	player.join();
	user.join();
}