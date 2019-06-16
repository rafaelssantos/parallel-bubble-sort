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
	if (n % nParts) {
		for (auto i = 0; i < nParts; i++) {
			bubble.sort((values + i * nPerPart), nPerPart);
		}
	} else {
		for (auto i = 0; i < nParts; i++) {
			bubble.sort((values + i * nPerPart), nPerPart);
		}
		bubble.sort((values + (nParts - 1) * nPerPart), n % nParts);
	}
	Logger::instance().stop(1, "Bubble part");

	Logger::instance().start(1);
	MergeSort merge;
	merge.partialSort(values, n, maxDepth);
	Logger::instance().stop(1, "Merge part");
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
		BubbleSort bubble;

		for (auto i = omp_get_thread_num() * nPartsPerThread; i < (omp_get_thread_num() + 1) * nPartsPerThread; i++) {
			bubble.sort((values + i * nPerPart), nPerPart);
		}
	}

	Logger::instance().stop(1, "Bubble part");

	MergeSort merge;
	merge.partialSortParallel(values, n, maxDepth);

	Logger::instance().stop(1, "Merge part");
	Logger::instance().stop(0, "Total");
}
