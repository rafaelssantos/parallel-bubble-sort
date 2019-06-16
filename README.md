<h1> Parallel Hybrid Sort </h1>

<p> Trabalho apresentado na disciplina de Computação de Alto Desempenho do PPGCC da Unesp, ministrada pelo Prof. Dr. Aleardo Manacero. </p>


<h2> Descrição do Algoritmo </h2>

<p> Neste trabalho é implemenado um algoritmo de ordenação híbrido que é, a grosso modo, organizado em duas etapas: </p>

<ol>
	<li> Bubble Sort </li>
	<li> Merge Sort </li>
</ol>

<p>O vetor com valores de entrada é na verdade composto por subvetores, por padrão 32 (2^5), cada subvetor é ordenado pelo bubble sort. Após essa ordenação inicial, uma versão parcial do merge sort é executada a fim de obter todos os valores ordenados.
</p>


<p>No momento, há duas versões do algoritmo implementadas: </p>
<ul>
	<li>Serial</li>
	<li>Paralela em OpenMP</li>
</ul>


<h2> Uso </h2>
<p> O programa deve ser executado por linha de comando. Por meio de passagem de parâmetros é possível alterar diversas opções, entre as quais: </p>
<ul>
	<li>[--file] ou [-f] <p>Nome base dos arquivos de entrada e saída. Veja que esta opção não define o nome completo do arquivo. Por exemplo, caso a opção "-f teste" seja passada, os  valores de gerados antes da ordenaca serão salvos no arquivo "testeinput.txt" e os de saída em "testeoutput.txt" </p></li>
	<li>[--input] ou [-i] <p>Define um arquivo com valores de entrada. O programa carregará estes valores para realizar ordenação. Caso esta opção não seja definida, os valores são geradas de forma aleatória.</p> </li>
	<li>[--log] ou  [-l] <p>Habilita o modo de log, salvando tempos de execuções,</p></li>
	<li>[--logfile] ou [-L] <p>Define o arquivo de saída onde serão salvos os tempos de execução</p></li>		
	<li>[--maximum] ou [-m] <p>Define o maior valor gerado no caso da entrada ser aleatória. Intervalo: [0, -m].</p> </li>
	<li>[--merge-depth] ou [-M] <p>Define o número de subvetores no qual o vetor é dividido. Veja que esse valor não é definido de forma direta, mas sim por meio de uma potência de base 2 (2^-M). O valor 5 é utilizado por padrão, caso esta opção não seja definida. Desta forma, há por padrão 32 subvetores (2^5).</p></li>
	<li>[--parallel] ou [-p] <p>Define que o algoritmo paralelo deve ser executado. Sem esta opção, o algoritmo sequencial é executado.</p> </li>
	<li>[--size] ou [-n] <p>Quantidade total de elementos do vetor. Por causa do algoritmo, caso esse valor não seja múltiplo do número definido para subvetores, o programa altera para o pŕoximo valor múltiplo.  MAX_INT é utilizdo nos valores adicionais. Após o processamento, esses valores são descartados no resultado.</p></li>
	<li>[--threads] ou [-t] <p>Número de threads do algoritmo paralelo. Esta opção só tem efeito caso a opção do algoritmo paraleo tenha sido definida.</p></li>
	<li>[--times] ou [-x] <p>Número de execuções realizadas para teste. O log deve estar habilitado.</p></li>
	<li>[--verbose] ou  [-v] <p>Exibe os valores de entrada e saída durante a execução do programa.</p></li>
</ul>

