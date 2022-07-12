#include <iostream>
#include <algorithm>
#include <tuple>

#include "genMaxArea.h"

using namespace std;
int main(void) {

	int rows, collums;
	cin >> rows; cin >> collums;
	//Declara uma matriz de entrada mtx para ler a entrada dos caracteres
	vector<vector<char>> mtx(rows, vector<char>(collums, '-'));



	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < collums; j++) {
			cin >> mtx[i][j];
		}
	}
	if (collums > rows){
		vector<vector<char>> t_mtx(collums, vector<char>(rows, '-'));
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < collums; j++) {
				t_mtx[j][i] = mtx[i][j];
			}
		}
		mtx = t_mtx;
		int aux = rows;
		rows = collums; collums = aux;
	}

	//Declara uma matriz matrix para salvar o maior valor possivel para coluna ate a linha especificada
	vector<vector<int>> matrix(rows, vector<int>(collums, 0));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < collums; j++) {
			if (i == 0) {
				if (mtx[i][j] == '.') {
					matrix[i][j] = 1;
				}
			}
			else {
				if (mtx[i][j] == '.') {
					matrix[i][j] = matrix[i - 1][j] + 1;
				}
			}
		}
	}
	
	//Invoca a funcao que gera a lista das maiores areas por dimensao
	vector<int> result = genMaxArea(matrix);


	int n;
	cin >> n;
	//	Salva um vetor mesas que é uma quadrupla onde table[x]<0> e a area da mesa mesa x, table[x]<1> e o tamanho do maior lado da mesa, 
	//table[x]<2> e o tamanho do menor lado da mesa e table[x]<3> e uma flag que assume valor 1 caso o lado de maior tamanho seja a largura. 
	vector<tuple<int, int, int, bool>> tables(n);
	for (int i = 0; i < n; i++) {
		bool flag = 0;
		int higher, lower;
		cin >> higher; cin >> lower;
		if (lower > higher) {
			int temp = higher;
			higher = lower; lower = temp;
			flag = 1;
		}
		int area = higher * lower;
		tables[i] = make_tuple(area, higher, lower, flag);
	}
	//Ordena as mesas por area, de forma decrescente
	sort(tables.begin(), tables.end(), greater<tuple<int, int, int, bool>>());

	pair<int, int>chosen_table;
	for (int i = 0; i < tables.size(); i++) {
		bool already_chosen = 0;
		int bigger_side = get<1>(tables[i]);
		int smaller_side = get<2>(tables[i]);

		if (result[bigger_side] > smaller_side) {
			//Caso a mesa tenha sido rotacionada, inverte os lados
			if (get<3>(tables[i])) {
				int temp = get<1>(tables[i]);
				get<1>(tables[i]) = get<2>(tables[i]);
				get<2>(tables[i]) = temp;
				get<3>(tables[i]) = 0;
			}

			bool end = 0;
			if (already_chosen) {
				//Caso ja tenha sido escolhida alguma mesa, compara com a resposta da proxima mesa possivel
				if (get<0>(tables[i]) == get<0>(tables[i - 1])) {
					//Caso elas tenham a mesma area, compara o comprimento de cada uma das mesas
					if (get<2>(tables[i]) > get<2>(tables[i - 1])) {
						chosen_table.first = get<1>(tables[i]);
						chosen_table.second = get<2>(tables[i]);
					}
				}
				else {
					//Caso eles nao tenham a mesma area, quer dizer que a atual mesa escolhida é a otima
					end = 1;
				}
			}
			else {
				already_chosen = 1;
				chosen_table.first = get<1>(tables[i]);
				chosen_table.second = get<2>(tables[i]);
			}
			if (end == 1) {
				break;
			}
			
		}
	}
	cout << chosen_table.first << " " << chosen_table.second;
	return 0;
	
}

