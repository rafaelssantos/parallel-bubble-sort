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



void HybridSort::sort(int* values, int n, int mergeMaxRecDepth) {
	int partCount = static_cast<int>(pow(2, mergeMaxRecDepth));
	int partSize = n / partCount;

	Logger::instance().start(0);
	Logger::instance().start(1);

	BubbleSort bubble;
	for (auto i = 0; i < partCount; i++) {
		bubble.sort((values + i * partSize), partSize);
	}
	Logger::instance().stop(1, "Bubble");

	Logger::instance().start(1);
	MergeSort merge;
	merge.partialSort(values, n, mergeMaxRecDepth);
	Logger::instance().stop(1, "Merge");

	Logger::instance().stop(0, "Total");
}



void HybridSort::sortParallel(int* values, int n, int mergeMaxRecDepth, int threadCount) {
	int partCount = static_cast<int>(pow(2, mergeMaxRecDepth));
	int partSize = n / partCount;
	int partCountPerThread = partCount / threadCount;

	Logger::instance().start(0);
	Logger::instance().start(1);

#pragma omp parallel num_threads(threadCount)
	{
		for (auto i = omp_get_thread_num() * partCountPerThread; i < (omp_get_thread_num() + 1) * partCountPerThread; i++) {
			BubbleSort bubble;
			bubble.sort((values + i * partSize), partSize);
		}
	}

	Logger::instance().stop(1, "Bubble");

	MergeSort merge;
	Logger::instance().start(1);
	merge.partialSortParallel(values, n, mergeMaxRecDepth);

	Logger::instance().stop(1, "Merge");
	Logger::instance().stop(0, "Total");
}
