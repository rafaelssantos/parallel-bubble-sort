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

	bool hasRepeatToExec();

	void startBenchmark();

	void setTimes(int times);

	int times() const;

	void setEnable(bool enable);

	bool isEnable();

	void save(std::string filePath);

	void reset();


private:
	Logger();

	virtual ~Logger();

	std::vector<std::chrono::system_clock::time_point> m_startsTime;
	int m_times;
	int m_iter;
	bool m_enable;
	std::string m_log;
};


#endif    // LOGGER_H
