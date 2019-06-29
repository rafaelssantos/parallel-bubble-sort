#ifndef LOGGER_H
#define LOGGER_H


#include <chrono>
#include <string>
#include <vector>


class Logger {
public:
	static Logger& instance();

	void start(int i);

	void appendMessage(std::string message);

	void stop(int i, std::string message);

	void startBenchmark();

	void setEnable(bool enable);

	bool isEnable();

	void print();

	void reset();


private:
	Logger();

	virtual ~Logger();

	std::vector<std::chrono::system_clock::time_point> m_startsTime;
	bool m_enable;
	std::string m_log;
};


#endif    // LOGGER_H
