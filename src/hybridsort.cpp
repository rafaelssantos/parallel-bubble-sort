#include "hybridsort.h"


#include <mpi.h>
#include <cmath>
#include <iostream>

#include "bubblesort.h"
#include "logger.h"
#include "mergesort.h"



HybridSort::HybridSort() {
}





HybridSort::~HybridSort() {
}





void HybridSort::sort(int* values, int n, int mergeMaxRecDepth) {
	int partCount = static_cast<int>(pow(2, mergeMaxRecDepth));
	int partSize = n / partCount;

	Logger::instance().start(0);
	Logger::instance().start(1);

	BubbleSort bubble;
	for (auto i = 0; i < partCount; i++) {
		bubble.sort((values + i * partSize), partSize);
	}
	Logger::instance().stop(1, "Bubble");

	Logger::instance().start(1);
	MergeSort merge;
	merge.partialSort(values, n, mergeMaxRecDepth);
	Logger::instance().stop(1, "Merge");

	Logger::instance().stop(0, "Total");
}



void HybridSort::sortParallel(int* values, int n, int mergeMaxRecDepth, int npForBubble) {
	int nPerPart = n / npForBubble;
	int rank;
	int worldSize;


	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

	int sendCounts[worldSize];
	int sendDispls[worldSize];


	int index = 0;
	while (index < npForBubble) {
		sendCounts[index] = nPerPart;
		sendDispls[index] = index * nPerPart;
		index++;
	}
	while (index < worldSize) {
		sendCounts[index] = 0;
		sendDispls[index] = 0;
		index++;
	}




	if (rank < npForBubble) {
		int localValues[nPerPart];

		MPI_Scatterv(values, sendCounts, sendDispls, MPI_INT, localValues, nPerPart, MPI_INT, 0, MPI_COMM_WORLD);
		BubbleSort bubble;
		bubble.sort(localValues, nPerPart);

		MPI_Gatherv(localValues, nPerPart, MPI_INT, values, sendCounts, sendDispls, MPI_INT, 0, MPI_COMM_WORLD);
	}


	int partASize = n / worldSize;
	int* sideA = new int[partASize];

	MPI_Scatter(values, partASize, MPI_INT, sideA, partASize, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Gather(sideA, partASize, MPI_INT, values, partASize, MPI_INT, 0, MPI_COMM_WORLD);


	int pStride = 1;
	int partBSize;
	MPI_Status status;

	while (pStride < worldSize) {
		if (rank % (2 * pStride) == 0) {
			if (rank + pStride < worldSize) {
				MPI_Recv(&partBSize, 1, MPI_INT, rank + pStride, 0, MPI_COMM_WORLD, &status);
				int* sideB = new int[partBSize];
				MPI_Recv(sideB, partBSize, MPI_INT, rank + pStride, 0, MPI_COMM_WORLD, &status);
				MergeSort merge;
				sideA = merge.mergeParallel(sideA, partASize, sideB, partBSize);
				partASize = partASize + partBSize;

				//				delete[] localValuesA;
				//				delete[] localValuesB;
				//				localValuesA = mergedValues;
			}
		} else {
			int nearRank = rank - pStride;
			MPI_Send(&partASize, 1, MPI_INT, nearRank, 0, MPI_COMM_WORLD);
			MPI_Send(sideA, partASize, MPI_INT, nearRank, 0, MPI_COMM_WORLD);
			break;
		}

		pStride = pStride * 2;
	}

	if (rank == 0) {
		for (int i = 0; i < n; i++) {
			values[i] = sideA[i];
		}

		delete[] sideA;
		sideA = nullptr;
	}


	if (rank == 0) {
		std::cout << "N =" << n << "\n";
		for (auto i = 0; i < n; i++) {
			std::cout << values[i] << "\n";
		}
	}
}
