#include <chrono>
#include <iostream>

#include "timer.hpp"

void Timer::start()
{
	start_time = std::chrono::system_clock::now();
	is_running = true;
}

void Timer::stop()
{
	end_time = std::chrono::system_clock::now();
	is_running = false;
}

double Timer::elapsed_ms()
{
	std::chrono::time_point<std::chrono::system_clock> time;
	
	if(is_running)
		time = std::chrono::system_clock::now();
	else
		time = end_time;
	
	return std::chrono::duration_cast<std::chrono::milliseconds>(time - start_time).count();
}

double Timer::elapsed_sec()
{
	return elapsed_ms()/1000.0;
}
