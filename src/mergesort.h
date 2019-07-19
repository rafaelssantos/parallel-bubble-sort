#ifndef MERGESORT_H
#define MERGESORT_H


#include "sortalgorithm.h"


class MergeSort {
public:
	MergeSort();

	virtual ~MergeSort();

	virtual void sort(int* values, int n);

	virtual void partialSort(int* values, int n, int maxRecDepth);

	virtual void partialSortParallel(int* values, int n, int maxRecDepth);


protected:
	void virtual merge(int* values, int* tempValues, int begin, int mid, int end);

	void virtual divide(int* values, int* tempValues, int begin, int end);

	void virtual partialDivide(int* values, int* tempValues, int begin, int end, int maxRecDepth, int depth);

	void virtual partialDivideParallel(int* values, int* tempValues, int begin, int end, int maxRecDepth, int depth);
};

#endif    // MERGESORT_H
