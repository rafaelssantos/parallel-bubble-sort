#include "valuesmanager.h"


#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <vector>


using namespace std;





ValuesManager& ValuesManager::instance() {
	static ValuesManager instance;

	return instance;
}





int* ValuesManager::generateUniform(int n, int max) {
	int* values = nullptr;

	values = new int[n];
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, max);

	for (auto i = 0; i < n; i++) {
		values[i] = distribution(generator);
	}

	return values;
}





int* ValuesManager::generatePoisson(int n, float mean) {
	int* values = nullptr;

	values = new int[n];
	default_random_engine generator;
	poisson_distribution<int> distribution(mean);

	for (auto i = 0; i < n; i++) {
		values[i] = distribution(generator);
	}

	return values;
}





int* ValuesManager::generateRandom(int n, int max) {
	int* values = nullptr;

	values = new int[n];
	random_device generator;

	for (auto i = 0; i < n; i++) {
		values[i] = generator() % max;
	}

	return values;
}





void ValuesManager::print(const int* values, int n) {
	for (auto i = 0; i < n; i++) {
		cout << i << " " << values[i] << "\n";
	}
}





void ValuesManager::copy(int* destValues, const int* sourceValues, int n) {
	memcpy(destValues, sourceValues, n * sizeof(int));
}




void ValuesManager::save(string filePath, int* values, int n) {
	ofstream file(filePath);

	for (auto i = 0; i < n - 1; i++) {
		file << values[i] << "\n";
	}
	file << values[n - 1];

	file.close();
}





int* ValuesManager::read(string filePath, int* n) {
	ifstream file(filePath);
	vector<int> tempValues;
	int value;

	while (file.peek() != EOF) {
		file >> value;
		tempValues.push_back(value);
	}
	int* values = new int[tempValues.size()];

	for (auto i = 0u; i < tempValues.size(); i++) {
		values[i] = tempValues[i];
	}

	*n = static_cast<int>(tempValues.size());

	file.close();

	return values;
}




int* ValuesManager::expandToMultiple(const int* values, int n, int* expN, int factor) {
	int* expValues = nullptr;
	if (n % factor == 0) {
		*expN = n;
	} else {
		*expN = static_cast<int>(ceil((1.0f * n) / factor)) * factor;
	}

	expValues = new int[*expN];
	memcpy(expValues, values, sizeof(int) * n);

	for (auto i = n; i < *expN; i++) {
		expValues[i] = std::numeric_limits<int>::max();
	}

	return expValues;
}





ValuesManager::ValuesManager() {
}





ValuesManager::~ValuesManager() {
}
