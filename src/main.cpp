#include <iostream>
#include <string>
#include "logger.h"
#include "sortalgorithmtype.h"
#include "sortmanager.h"
#include "valuesmanager.h"

using namespace std;



int main(int argc, char* argv[]) {
	int max = 101;                     // Valor máximo gerado
	int n = 0;                         // Número total de elmentos
	bool verbose = false;              // True para imprimir os vetores. False, caso contrário
	bool readInput = false;            // True para ler valores de entrada. False, para gerar aleatórios
	bool saveInput = false;            // Salva os valores de entrada
	int mergeDepth = 0;                // Nível de recursão merge
	string baseFilePath = "data";      // Caminho do arquivo de saída
	string inputFilePath = "";         // Caminho do arquivo de entrada
	string logFilePath = "log.csv";    // Nome do arquivo de log



	/******************************* Opções ***************************************/
	/******************************************************************************/
	if (argc == 1) {
		cout << "Invalid options. Type --help or -h to see available options.\n";
		return 0;
	}
	for (auto op = 1; op < argc; op++) {
		string option(argv[op]);

		if (option.compare("--verbose") == 0 || option.compare("-v") == 0) {
			verbose = true;
		} else if (option.compare("--file") == 0 || option.compare("-f") == 0) {
			baseFilePath = argv[++op];
		} else if (option.compare("--input") == 0 || option.compare("-i") == 0) {
			inputFilePath = argv[++op];
			readInput = true;
		} else if (option.compare("--size") == 0 || option.compare("-n") == 0) {
			n = atoi(argv[++op]);
		} else if (option.compare("--save") == 0 || option.compare("-s") == 0) {
			saveInput = true;
		} else if (option.compare("--merge-depth") == 0 || option.compare("-M") == 0) {
			mergeDepth = atoi(argv[++op]);
		} else if (option.compare("--maximum") == 0 || option.compare("-m") == 0) {
			max = atoi(argv[++op]) + 1;
		} else if (option.compare("--log") == 0 || option.compare("-l") == 0) {
			Logger::instance().setEnable(true);
		} else if (option.compare("--logfile") == 0 || option.compare("-L") == 0) {
			logFilePath = argv[++op];
		} else if (option.compare("--times") == 0 || option.compare("-t") == 0) {
			Logger::instance().setTimes(atoi(argv[++op]));
		} else if (option.compare("--help") == 0 || option.compare("-h") == 0) {
			cout << "[OPTION] = description\n";
			cout << "[--file] or        [-f] = Base file path for output and generated values\n";
			cout << "[--input] or       [-i] = Set input file path and also indicates that input values will be read\n";
			cout << "[--save] or        [-s] = Save input values\n";
			cout << "[--log] or         [-l] = Enable log\n";
			cout << "[--logfile] or     [-L] = Set log file path\n";
			cout << "[--maximum] or     [-m] = Maximum value random generated\n";
			cout << "[--merge-depth] or [-M] = Merge depth\n";
			cout << "[--size] or        [-n] = Number of random generated values\n";
			cout << "[--times] or       [-t] = Number of executions for benchmark\n";
			cout << "[--verbose] or     [-v] = Display data\n";
			return 0;
		}
	}

	/******************************* Processamento ********************************/
	/******************************************************************************/

	int* input;     // Elementos de entrada
	int* output;    // Elementos ordenados

	if (n == 0 && inputFilePath.empty()) {
		cout << "Invalid options. Type --help or -h to see available options.\n";
		return 0;
	}

	if (readInput) {
		cout << ">> Reading values......................" << flush;
		input = ValuesManager::instance().read(inputFilePath, &n);
	} else {
		cout << ">> Generating random values............" << flush;
		input = ValuesManager::instance().generateRandom(n, max);
	}
	if (saveInput) {
		ValuesManager::instance().save(baseFilePath + "_input.txt", input, n);
	}
	cout << "DONE\n" << flush;


	if (verbose) {
		cout << "\nINPUT\n";
		ValuesManager::instance().print(input, n);
		cout << "\n";
	}

	output = new int[n];

	if (Logger::instance().times() > 1) {
		int time = 0;
		while (Logger::instance().hasRepeatToExec()) {
			ValuesManager::instance().copy(output, input, n);

			cout << ">> Sorting #" << time << ".........................." << flush;
			SortManager::instance().sort(SortAlgorithmType::SERIAL_HYBRID, output, n, mergeDepth);

			ValuesManager::instance().save(baseFilePath + "_ouput.txt", output, n);
			cout << "DONE\n" << flush;
			time++;
		}
	}

	else {
		ValuesManager::instance().copy(output, input, n);
		cout << ">> Sorting............................." << flush;
		SortManager::instance().sort(SortAlgorithmType::SERIAL_HYBRID, output, n, mergeDepth);
		ValuesManager::instance().save(baseFilePath + "_ouput.txt", output, n);
		cout << "DONE\n" << flush;
	}



	if (verbose) {
		cout << "\nOUTPUT\n";
		ValuesManager::instance().print(output, n);
		cout << "\n";
	}

	if (Logger::instance().isEnable()) {
		Logger::instance().save(logFilePath);
	}

	delete[] input;
	delete[] output;
	input = nullptr;
	output = nullptr;


	//	int nthreads, tid;

	//	#pragma omp parallel num_threads(4)
	//	{
	//		#pragma omp for
	//		for(int i = 0; i < 32; i++){
	//			tid = omp_get_thread_num();
	//			printf("Hello World %d from thread = %d\n", i, tid);
	//		}

	//	}

	return 0;
}
