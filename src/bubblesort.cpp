#include "bubblesort.h"

BubbleSort::BubbleSort() {
}

BubbleSort::~BubbleSort() {
}

void BubbleSort::sort(int* values, int n) {
	bool swapOccurs = true;
	int tempValue;

	for (auto i = 0; i < n - 1; i++) {
		if (!swapOccurs) {
			break;
		}
		swapOccurs = false;
		for (auto j = 0; j < n - 1 - i; j++) {
			if (values[j] > values[j + 1]) {
				swapOccurs = true;
				tempValue = values[j];
				values[j] = values[j + 1];
				values[j + 1] = tempValue;
			}
		}
	}
}
