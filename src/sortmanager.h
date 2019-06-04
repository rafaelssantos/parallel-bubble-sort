#ifndef SORTMANAGER_H
#define SORTMANAGER_H

#include "sortalgorithmtype.h"

class SortManager {
public:
	void sort(SortAlgorithmType sortType, int* values, int n, int maxDepth = 2);

	static SortManager& instance();

private:
	SortManager();

	~SortManager();
};

#endif    // SORTMANAGER_H
