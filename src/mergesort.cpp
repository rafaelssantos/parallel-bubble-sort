#include "mergesort.h"

#include <cstring>
#include <iostream>



MergeSort::MergeSort() {
}





MergeSort::~MergeSort() {
}





void MergeSort::sort(int* values, int n) {
	int* tempValues = nullptr;

	tempValues = new int[n];
	memcpy(tempValues, values, n * sizeof(int));

	divide(values, tempValues, 0, n - 1);


	delete[] tempValues;
	tempValues = nullptr;
}





void MergeSort::partialSort(int* values, int n, int maxRecDepth) {
	int* tempValues = nullptr;

	tempValues = new int[n];
	memcpy(tempValues, values, n * sizeof(int));

	partialDivide(values, tempValues, 0, n - 1, maxRecDepth, 0);


	delete[] tempValues;
	tempValues = nullptr;
}





void MergeSort::merge(int* values, int* tempValues, int begin, int mid, int end) {
	int l;
	int r;
	int i;

	l = begin;
	r = mid + 1;
	i = begin;

	while (l <= mid && r <= end) {
		if (tempValues[l] < tempValues[r]) {
			values[i] = tempValues[l];
			l++;
		} else {
			values[i] = tempValues[r];
			r++;
		}
		i++;
	}

	while (l <= mid) {
		values[i] = tempValues[l];
		l++;
		i++;
	}

	while (r <= end) {
		values[i] = tempValues[r];
		r++;
		i++;
	}

	for (int i = begin; i <= end; i++) {
		tempValues[i] = values[i];
	}
}





void MergeSort::divide(int* values, int* tempValues, int begin, int end) {
	if (begin < end) {
		int mid = (begin + end) / 2;
		divide(values, tempValues, begin, mid);
		divide(values, tempValues, mid + 1, end);
		merge(values, tempValues, begin, mid, end);
	}
}





void MergeSort::partialDivide(int* values, int* tempValues, int begin, int end, int maxRecDepth, int depth) {
	if (begin < end && depth <= maxRecDepth) {
		int mid = (begin + end) / 2;
		partialDivide(values, tempValues, begin, mid, maxRecDepth, depth + 1);
		partialDivide(values, tempValues, mid + 1, end, maxRecDepth, depth + 1);
		merge(values, tempValues, begin, mid, end);
	}
}



int* MergeSort::mergeParallel(int* partA, int partASize, int* partB, int partBSize) {
	int ai, bi, ci;
	int* partC;
	int partCSize = partASize + partBSize;

	ai = 0;
	bi = 0;
	ci = 0;


	partC = new int[partCSize];
	while ((ai < partASize) && (bi < partBSize)) {
		if (partA[ai] <= partB[bi]) {
			partC[ci] = partA[ai];
			ci++;
			ai++;
		} else {
			partC[ci] = partB[bi];
			ci++;
			bi++;
		}
	}

	if (ai >= partASize) {
		for (int i = ci; i < partCSize; i++, bi++) {
			partC[i] = partB[bi];
		}
	} else if (bi >= partBSize) {
		for (int i = ci; i < partCSize; i++, ai++) {
			partC[i] = partA[ai];
		}
	}
	for (int i = 0; i < partASize; i++) {
		partA[i] = partC[i];
	}

	for (int i = 0; i < partBSize; i++) {
		partB[i] = partC[partASize + i];
	}


	return partC;
}
