#ifndef VALUESMANAGER_H
#define VALUESMANAGER_H

#include <string>

class ValuesManager {
public:
	static ValuesManager& instance();

	int* generateUniform(int n, int max);

	int* generatePoisson(int n, float mean);

	int* generateRandom(int n, int max);

	void print(const int* values, int n);

	void save(std::string filePath, int* values, int n);

	int* read(std::string filePath, int* n);

private:
	ValuesManager();

	virtual ~ValuesManager();
};

#endif    // VALUESMANAGER_H
