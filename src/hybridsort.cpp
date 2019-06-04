#include "hybridsort.h"


#include <cmath>
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
	Logger::instance().stop(1, "Bubble Sort");

	Logger::instance().start(1);
	MergeSort merge;
	merge.partialSort(values, n, maxDepth);
	Logger::instance().stop(1, "Merge Sort");
	Logger::instance().stop(0, "Hybrid Sort");
}
