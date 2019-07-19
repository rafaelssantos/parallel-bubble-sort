#ifndef MERGESORT_H
#define MERGESORT_H


#include "sortalgorithm.h"


class MergeSort {
public:
	MergeSort();

	virtual ~MergeSort();

	void sort(int* values, int n);

	void partialSort(int* values, int n, int maxRecDepth);

	void merge(int* values, int* tempValues, int begin, int mid, int end);

	void divide(int* values, int* tempValues, int begin, int end);

	void partialDivide(int* values, int* tempValues, int begin, int end, int maxRecDepth, int depth);

	int* mergeParallel(int* partA, int partASize, int* partB, int partBSize);
};

#endif    // MERGESORT_H
