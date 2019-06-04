#include "sortmanager.h"


#include "bubblesort.h"
#include "mergesort.h"





void SortManager::sort(AlgorithmType sortType, int* values, int n) {
	if (sortType == AlgorithmType::BUBBLE_SORT) {
		BubbleSort sorter;
		sorter.sort(values, n);
	} else if (sortType == AlgorithmType::MERGE_SORT) {
		MergeSort sorter;
		sorter.sort(values, n);
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
