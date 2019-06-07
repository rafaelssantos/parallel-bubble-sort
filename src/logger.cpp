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
	m_iter = 0;
}



void Logger::setTimes(int times) {
	m_times = times;
}




int Logger::times() const {
	return m_times;
}



void Logger::setEnable(bool enable) {
	m_enable = enable;
}

bool Logger::isEnable() {
	return m_enable;
}





void Logger::save(string filePath) {
	ofstream file(filePath);

	file << m_log;

	file.close();
}





void Logger::reset() {
	m_log = "";
	m_iter = 0;
}




bool Logger::hasRepeatToExec() {
	if (m_iter++ < m_times) {
		return true;
	} else {
		return false;
	}
}



Logger::Logger() {
	m_times = 1;
	m_iter = 0;
	m_enable = false;
	m_log = "";
}




Logger::~Logger() {
}
