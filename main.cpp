#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
int main(void) {
	int rows, collums;
	cin >> rows; cin >> collums;
	//Declara uma matriz de entrada mtx para ler a entrada dos caracteres
	vector<vector<char>> mtx(rows, vector<char>(collums, '-'));

	//Declara uma matriz matrix para salvar o maior valor possivel para coluna ate a linha especificada
	vector<vector<int>> matrix(rows, vector<int>(collums, 0));

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < collums; j++) {
			cin >> mtx[i][j];
		}
	}
	
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
	vector<vector<int>> left_matrix(rows, vector<int>(collums, -1));
	vector<vector<int>> right_matrix(rows, vector<int>(collums, -1));
	stack<int> limit_stack;

	//Preenche a matriz de limites ao lado esquerdo 
	for (int i = 0; i < rows; i++) {
		while(!limit_stack.empty()) {
			limit_stack.pop();
		}
		limit_stack.push(0);
		left_matrix[i][0] = 0;

		for (int j = 1; j < collums; j++) {
			while (!limit_stack.empty()) {
				int top = limit_stack.top();
				if (matrix[i][top] >= matrix[i][j]) {
					limit_stack.pop();
					if (limit_stack.empty()) {
						left_matrix[i][j] = 0;
					}
				}
				else {
					left_matrix[i][j] = top + 1;
					break;
				}
			}
			limit_stack.push(j);
		}
	}

	//Preenche a matriz de limites ao lado direito utilizando a mesma logica
	for (int i = 0; i < rows; i++) {
		while (!limit_stack.empty()) {
			limit_stack.pop();
		}
		limit_stack.push(collums-1);
		right_matrix[i][collums-1] = collums-1;

		for (int j = collums-2; j >= 0 ; j--) {
			while (!limit_stack.empty()) {
				int top = limit_stack.top();
				if (matrix[i][top] >= matrix[i][j]) {
					limit_stack.pop();
					if (limit_stack.empty()) {
						right_matrix[i][j] = 0;
					}
				}
				else {
					right_matrix[i][j] = top - 1;
					break;
				}
			}
			limit_stack.push(j);
		}
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < collums; j++) {
			cout << matrix[i][j] << '\t';
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < collums; j++) {
			cout << left_matrix[i][j] << '\t';
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < collums; j++) {
			cout << right_matrix[i][j] << '\t';
		}
		cout << endl;
	}
}

