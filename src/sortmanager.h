#ifndef SORTMANAGER_H
#define SORTMANAGER_H

#include "algorithmtype.h"

class SortManager {
public:
	void sort(AlgorithmType sortType, int* values, int n);

	static SortManager& instance();

private:
	SortManager();
	~SortManager();
};

#endif    // SORTMANAGER_H
