#include "hybridsort.h"


#include <cmath>
#include "bubblesort.h"
#include "mergesort.h"





HybridSort::HybridSort() {
}





HybridSort::~HybridSort() {
}




void HybridSort::sort(int* values, int n, int maxDepth) {
	int nParts = static_cast<int>(pow(2, maxDepth));
	int nPerPart = n / nParts;


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


	MergeSort merge;
	merge.partialSort(values, n, maxDepth);
}
