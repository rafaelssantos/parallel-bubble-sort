#include "mergesort.h"


#include <cstring>



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
