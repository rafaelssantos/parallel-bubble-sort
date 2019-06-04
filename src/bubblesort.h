#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "sortalgorithm.h"


class BubbleSort : public SortAlgorithm {
public:
	BubbleSort();

	virtual ~BubbleSort();

	virtual void sort(int* values, int n) override;
};

#endif    // BUBBLESORT_H
