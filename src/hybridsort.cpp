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



void HybridSort::sort(int* values, int n, int maxDepth) {
	int nParts = static_cast<int>(pow(2, maxDepth));
	int nPerPart = n / nParts;

	Logger::instance().start(0);
	Logger::instance().start(1);

	BubbleSort bubble;
	for (auto i = 0; i < nParts; i++) {
		bubble.sort((values + i * nPerPart), nPerPart);
	}
	Logger::instance().stop(1, "Bubble");

	Logger::instance().start(1);
	MergeSort merge;
	merge.partialSort(values, n, maxDepth);
	Logger::instance().stop(1, "Merge");

	Logger::instance().stop(0, "Total");
}



void HybridSort::sortParallel(int* values, int n, int maxDepth, int nThreads) {
	int nPerPart;
	int rank;
	int worldSize;

	//	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

	nPerPart = n / nThreads;
	int sendCounts[32];
	int sendDispls[32];

	int index = 0;
	while (index < nThreads) {
		sendCounts[index] = nPerPart;
		sendDispls[index] = index * nPerPart;
		index++;
	}
	while (index < 32) {
		sendCounts[index] = 0;
		sendDispls[index] = 0;
		index++;
	}




	if (rank < nThreads) {
		int localValues[nPerPart];

		//	std::cout << "Here :" << rank << " " << n << " " << nPerPart << "\n";

		//	MPI_Scatter(values, nPerPart, MPI_INT, localValues, nPerPart, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Scatterv(values, sendCounts, sendDispls, MPI_INT, localValues, nPerPart, MPI_INT, 0, MPI_COMM_WORLD);
		BubbleSort bubble;
		bubble.sort(localValues, nPerPart);

		// MPI_Gather(localValues, nPerPart, MPI_INT, values, nPerPart, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Gatherv(localValues, nPerPart, MPI_INT, values, sendCounts, sendDispls, MPI_INT, 0, MPI_COMM_WORLD);
	}
	int s = n / worldSize;
	int* sideA = new int[s];
	MPI_Scatter(values, s, MPI_INT, sideA, s, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Gather(sideA, s, MPI_INT, values, s, MPI_INT, 0, MPI_COMM_WORLD);


	int step = 1;
	int m;
	MPI_Status status;

	while (step < worldSize) {
		if (rank % (2 * step) == 0) {
			if (rank + step < worldSize) {
				MPI_Recv(&m, 1, MPI_INT, rank + step, 0, MPI_COMM_WORLD, &status);
				int* sideB = new int[m];
				MPI_Recv(sideB, m, MPI_INT, rank + step, 0, MPI_COMM_WORLD, &status);
				MergeSort merge;
				sideA = merge.mergeParallel(sideA, s, sideB, m);
				s = s + m;

				//				delete[] localValuesA;
				//				delete[] localValuesB;
				//				localValuesA = mergedValues;
			}
		} else {
			int near = rank - step;
			MPI_Send(&s, 1, MPI_INT, near, 0, MPI_COMM_WORLD);
			MPI_Send(sideA, s, MPI_INT, near, 0, MPI_COMM_WORLD);
			break;
		}
		step = step * 2;
	}

	if (rank == 0) {
		for (int i = 0; i < n; i++) {
			values[i] = sideA[i];
		}

		delete[] sideA;
		sideA = nullptr;
	}


	//	MPI_Gather(localValues, nPerPart, MPI_INT, values, nPerPart, MPI_INT, 0, MPI_COMM_WORLD);
	//	MPI_Scatter(values, nPerPart, MPI_INT, localValues, nPerPart, MPI_INT, 0, MPI_COMM_WORLD);


	//	if (rank == 0) {
	//		Logger::instance().start(0);
	//		Logger::instance().start(1);
	//	}




	//	Logger::instance().stop(1, "Bubble");

	//	MergeSort merge;
	//	Logger::instance().start(1);
	//	merge.partialSortParallel(values, n, maxDepth);

	//	Logger::instance().stop(1, "Merge");
	//	Logger::instance().stop(0, "Total");

	if (rank == 0) {
		std::cout << "N =" << n << "\n";
		for (auto i = 0; i < n; i++) {
			std::cout << values[i] << "\n";
		}
	}
}
