#include "logger.h"


#include <fstream>
#include <iostream>


using namespace std;


Logger& Logger::instance() {
	static Logger instance;

	return instance;
}





void Logger::start(int i) {
	while (i >= static_cast<int>(m_startsTime.size())) {
		m_startsTime.emplace_back(chrono::system_clock::now());
	}
	m_startsTime[i] = chrono::system_clock::now();
}



void Logger::appendMessage(string message) {
	m_log += message + "\n";
}



void Logger::stop(int i, std::string message) {
	auto end = chrono::system_clock::now();
	std::chrono::duration<float> elapsed_seconds = end - m_startsTime[i];

	m_log += message + "," + to_string(elapsed_seconds.count()) + "\n";
}





void Logger::startBenchmark() {
}




void Logger::setEnable(bool enable) {
	m_enable = enable;
}

bool Logger::isEnable() {
	return m_enable;
}





void Logger::print() {
	std::cout << m_log << "\n";
}





void Logger::reset() {
	m_log = "";
}




Logger::Logger() {
	m_enable = false;
	m_log = "";
}




Logger::~Logger() {
}
