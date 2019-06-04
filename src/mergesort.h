#ifndef MERGESORT_H
#define MERGESORT_H


#include "sortalgorithm.h"


class MergeSort {
public:
	MergeSort();

	virtual ~MergeSort();

	virtual void sort(int* values, int n);

	virtual void partialSort(int* values, int n, int maxDepth);

protected:
	void virtual merge(int* values, int* tempValues, int begin, int mid, int end);

	void virtual divide(int* values, int* tempValues, int begin, int end);

	void virtual divide(int* values, int* tempValues, int begin, int end, int maxDepth, int depth);
};

#endif    // MERGESORT_H
