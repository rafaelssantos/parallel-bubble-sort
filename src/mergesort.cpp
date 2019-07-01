#include "mergesort.h"

#include <mpi.h>
#include <cmath>
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





void MergeSort::partialSort(int* values, int n, int maxDepth) {
	int* tempValues = nullptr;

	tempValues = new int[n];
	memcpy(tempValues, values, n * sizeof(int));

	divide(values, tempValues, 0, n - 1, maxDepth, 0);


	delete[] tempValues;
	tempValues = nullptr;
}




void MergeSort::partialSortParallel(int* values, int n, int maxDepth) {
	//	int* tempValues = nullptr;

	//	tempValues = new int[n];
	//	memcpy(tempValues, values, n * sizeof(int));

	//	divideParallel(values, tempValues, 0, n - 1, maxDepth, 0);


	//	delete[] tempValues;
	//	tempValues = nullptr;
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





void MergeSort::divide(int* values, int* tempValues, int begin, int end, int maxDepth, int depth) {
	if (begin < end && depth <= maxDepth) {
		int mid = (begin + end) / 2;
		divide(values, tempValues, begin, mid, maxDepth, depth + 1);
		divide(values, tempValues, mid + 1, end, maxDepth, depth + 1);
		merge(values, tempValues, begin, mid, end);
	}
}



void MergeSort::divideParallel(int* values, int* tempValues, int begin, int end, int maxDepth, int depth) {
	//	if (begin < end && depth <= maxDepth) {
	//		int mid = (begin + end) / 2;


	//		int rank;
	//		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	//		int nParts = static_cast<int>(pow(2, depth));
	//		int partSize = n / nParts;

	//		MPI_Scatter(values, partSize, MPI_INT, (tempValues + rank * partSize), partSize, MPI_INT, rank, MPI_COMM_WORLD);

	//		if (rank < nParts) {
	//			divideParallel(values, (tempValues + rank * partSize), begin, mid, maxDepth, depth + 1);

	//			divideParallel(values, tempValues, mid + 1, end, maxDepth, depth + 1);

	//			MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	//			if (rank < pow(2, depth)) {
	//				MPI_Barrier(MPI_COMM_WORLD);
	//			}
	//			merge(values, tempValues, begin, mid, end);
	//		}
	//	}
}
