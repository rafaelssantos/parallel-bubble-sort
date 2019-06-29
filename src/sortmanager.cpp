#include "sortmanager.h"


#include "bubblesort.h"
#include "hybridsort.h"
#include "mergesort.h"




void SortManager::sort(SortAlgorithmType sortType, int* values, int n, int maxDepth, int nThtreads) {
	if (sortType == SortAlgorithmType::SERIAL_BUBBLE) {
		BubbleSort sorter;
		sorter.sort(values, n);
	} else if (sortType == SortAlgorithmType::SERIAL_MERGE) {
		MergeSort sorter;
		sorter.sort(values, n);
	} else if (sortType == SortAlgorithmType::SERIAL_HYBRID) {
		HybridSort sorter;
		sorter.sort(values, n, maxDepth);
	} else if (sortType == SortAlgorithmType::PARALLEL_HYBRID) {
		HybridSort sorter;
		sorter.sortParallel(values, n, maxDepth, nThtreads);
	}
}





SortManager& SortManager::instance() {
	static SortManager instance;
	return instance;
}





SortManager::SortManager() {
}





SortManager::~SortManager() {
}
