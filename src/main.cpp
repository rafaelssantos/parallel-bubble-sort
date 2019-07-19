#include <mpi.h>
#include <cmath>
#include <iostream>
#include <string>

#include "logger.h"
#include "sortalgorithmtype.h"
#include "sortmanager.h"
#include "valuesmanager.h"

using namespace std;


void messageError() {
	cout << "Invalid options. Type --help or -h to see available options.\nSome examples:\n\n";

	cout << "(parallel):\n";
	cout << "LINUX  : ./parallel-hybrid-sort -n 3200 -p -t 32\n";
	cout << "WINDOWS: parallel-hybrid-sort.exe -n 3200 -p -t 32\n\n";

	cout << "(serial):\n";
	cout << "LINUX  : ./parallel-hybrid-sort -n 3200\n";
	cout << "WINDOWS: parallel-hybrid-sort.exe -n 3200\n\n";

	cout << "(parallel and log):\n";
	cout << "LINUX  : ./parallel-hybrid-sort -n 3200 -p -t 32 -l\n";
	cout << "WINDOWS: parallel-hybrid-sort.exe -n 3200 -p -t 32 -l\n\n";

	cout << "(serial and log):\n";
	cout << "LINUX  : ./parallel-hybrid-sort -n 3200 -l\n";
	cout << "WINDOWS: parallel-hybrid-sort.exe -n 3200 -l\n\n";
}


int main(int argc, char* argv[]) {
	int max = 1000;         // Valor máximo gerado
	int n = 320;            // Número total de elementos
	int nThreads = 16;      // Número de threads
	int mergeDepth = 5;     // Nível de recursão merge parcial. Veja 2^5 = 32 (Vetores)
	int parallel = true;    // Execução do algoritmo paralelo

	bool verbose = false;      // True para imprimir os vetores. False, caso contrário
	bool readInput = false;    // True para ler valores de entrada. False, para gerar aleatórios

	string baseFilePath = "";     // Caminho do arquivo de saída
	string inputFilePath = "";    // Caminho do arquivo de entrada



	/******************************** MPI *****************************************/
	/******************************************************************************/
	int rank;
	int worldSize;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

	/******************************************************************************/
	/******************************************************************************/



	/******************************* Opções ***************************************/
	/******************************************************************************/
	//	if (rank == 0) {
	//		if (argc == 1) {
	//			messageError();
	//			MPI_Finalize();
	//			return 0;
	//		}
	//		for (auto op = 1; op < argc; op++) {
	//			string option(argv[op]);

	//			if (option.compare("--verbose") == 0 || option.compare("-v") == 0) {
	//				verbose = true;
	//			} else if (option.compare("--file") == 0 || option.compare("-f") == 0) {
	//				baseFilePath = argv[++op];
	//			} else if (option.compare("--input") == 0 || option.compare("-i") == 0) {
	//				inputFilePath = argv[++op];
	//				readInput = true;
	//			} else if (option.compare("--size") == 0 || option.compare("-n") == 0) {
	//				n = atoi(argv[++op]);
	//			} else if (option.compare("--merge-depth") == 0 || option.compare("-M") == 0) {
	//				mergeDepth = atoi(argv[++op]);
	//			} else if (option.compare("--maximum") == 0 || option.compare("-m") == 0) {
	//				max = atoi(argv[++op]) + 1;
	//			} else if (option.compare("--log") == 0 || option.compare("-l") == 0) {
	//				Logger::instance().setEnable(true);
	//			} else if (option.compare("--threads") == 0 || option.compare("-t") == 0) {
	//				nThreads = atoi(argv[++op]);
	//			} else if (option.compare("--parallel") == 0 || option.compare("-p") == 0) {
	//				parallel = true;
	//			} else if (option.compare("--help") == 0 || option.compare("-h") == 0) {
	//				cout << "[OPTION] = description\n";
	//				cout << "[--file] or        [-f] = Base file path for input and output and generated values\n";
	//				cout << "[--input] or       [-i] = Set input file path and also indicates that input values will be read\n";
	//				cout << "[--log] or         [-l] = Enable log\n";
	//				cout << "[--maximum] or     [-m] = Maximum value random generated\n";
	//				cout << "[--merge-depth] or [-M] = Merge depth\n";
	//				cout << "[--parallel] or    [-p] = Choose the parallle version fo the algorithm\n";
	//				cout << "[--size] or        [-n] = Number of random generated values\n";
	//				cout << "[--threads] or     [-t] = Number of executions for thread\n";
	//				cout << "[--verbose] or     [-v] = Display data\n";
	//				MPI_Finalize();
	//				return 0;
	//			}
	//		}
	//	}


	/******************************* Processamento ********************************/
	/******************************************************************************/

	int* input = nullptr;     // Elementos de entrada
	int* output = nullptr;    // Elementos ordenados

	int nExp = ValuesManager::instance().calcExpToMultiple(n, static_cast<int>(pow(2, mergeDepth)));

	if (rank == 0) {
		if (n == 0 && inputFilePath.empty()) {
			messageError();
			MPI_Finalize();
			return 0;
		}

		if (readInput) {
			if (verbose) {
				cout << ">> Reading values......................" << flush;
			}
			int* tempInput = ValuesManager::instance().read(inputFilePath, &n);
			input = ValuesManager::instance().expandToMultiple(tempInput, n, nExp);
			delete tempInput;
		} else {
			if (verbose) {
				cout << ">> Generating random values............" << flush;
			}
			int* tempInput = ValuesManager::instance().generateRandom(n, max);
			input = ValuesManager::instance().expandToMultiple(tempInput, n, nExp);
			delete tempInput;
		}



		ValuesManager::instance().save(baseFilePath + "input.txt", input, n);

		if (verbose) {
			cout << "DONE\n" << flush;
			cout << "\nINPUT\n";
			ValuesManager::instance().print(input, n);
			cout << "\n";
		}


		output = new int[nExp];


		ValuesManager::instance().copy(output, input, nExp);
		if (verbose) {
			cout << ">> Sorting............................." << flush;
		}
	}





	if (parallel) {
		SortManager::instance().sort(SortAlgorithmType::PARALLEL_HYBRID, output, nExp, mergeDepth, nThreads);
	} else {
		if (rank == 0) {
			SortManager::instance().sort(SortAlgorithmType::SERIAL_HYBRID, output, nExp, mergeDepth, nThreads);
		}
	}



	if (rank == 0) {
		ValuesManager::instance().save(baseFilePath + "output.txt", output, n);


		if (verbose) {
			cout << "DONE\n" << flush;
			cout << "\nOUTPUT\n";
			ValuesManager::instance().print(output, n);
			cout << "\n";
		}

		if (Logger::instance().isEnable()) {
			Logger::instance().print();
		}
	}


	delete[] input;
	delete[] output;
	input = nullptr;
	output = nullptr;

	MPI_Finalize();
	return 0;
}
