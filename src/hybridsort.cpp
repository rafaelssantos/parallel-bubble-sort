#include "hybridsort.h"


#include <omp.h>
#include <cmath>
#include <iostream>
#include "bubblesort.h"
#include "logger.h"
#include "mergesort.h"



HybridSort::HybridSort() {
}





HybridSort::~HybridSort() {
}



void HybridSort::sort(int* values, int n, int maxDepth) {
	int nParts = static_cast<int>(pow(2, maxDepth));
	int nPerPart = n / nParts;

	Logger::instance().start(0);
	Logger::instance().start(1);

	BubbleSort bubble;
	for (auto i = 0; i < nParts; i++) {
		bubble.sort((values + i * nPerPart), nPerPart);
	}
	Logger::instance().stop(1, "Bubble");

	Logger::instance().start(1);
	MergeSort merge;
	merge.partialSort(values, n, maxDepth);
	Logger::instance().stop(1, "Merge");

	Logger::instance().stop(0, "Total");
}



void HybridSort::sortParallel(int* values, int n, int maxDepth, int nThreads) {
	int nParts = static_cast<int>(pow(2, maxDepth));
	int nPerPart = n / nParts;
	int nPartsPerThread = nParts / nThreads;

	Logger::instance().start(0);
	Logger::instance().start(1);

#pragma omp parallel num_threads(nThreads)
	{
		for (auto i = omp_get_thread_num() * nPartsPerThread; i < (omp_get_thread_num() + 1) * nPartsPerThread; i++) {
			BubbleSort bubble;
			bubble.sort((values + i * nPerPart), nPerPart);
		}
	}

	Logger::instance().stop(1, "Bubble");

	MergeSort merge;
	Logger::instance().start(1);
	merge.partialSortParallel(values, n, maxDepth);

	Logger::instance().stop(1, "Merge");
	Logger::instance().stop(0, "Total");
}
