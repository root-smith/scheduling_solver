#pragma once

#include <chrono>

class Timer
{
private:
	std::chrono::time_point<std::chrono::system_clock> start_time;
	std::chrono::time_point<std::chrono::system_clock> end_time;
	bool is_running = false;
	
public:
	void start();
	void stop();
	
	double elapsed_ms();
	double elapsed_sec();
};
