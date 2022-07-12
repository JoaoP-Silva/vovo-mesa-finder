#ifndef GENMAXAREA_H
#define GENMAXAREA_H

#include <vector>
#include <stack>

using namespace std;

vector<int> genMaxArea(vector<vector<int>>& matrix) {
	int rows, collums;
	rows = matrix.size(); collums = matrix[0].size();
	vector<vector<int>> left_matrix(rows, vector<int>(collums, -1));
	vector<vector<int>> right_matrix(rows, vector<int>(collums, -1));
	stack<int> limit_stack;

	//Preenche a matriz de limites ao lado esquerdo 
	for (int i = 0; i < rows; i++) {
		while (!limit_stack.empty()) {
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
		limit_stack.push(collums - 1);
		right_matrix[i][collums - 1] = collums - 1;

		for (int j = collums - 2; j >= 0; j--) {
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

	//Gera um vetor de resultados result[i] onde i e o tamanho do maior lado de uma das solucoes possiveis. O valor inteiro salvo no
	//indice i corresponde ao maior valor dentre as solucoes que o maior lado é i.
	vector<int> result(rows, -1);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < collums; j++) {
			if (matrix[i][j] == 0) { continue; }
			int higher, lower;
			higher = right_matrix[i][j] - left_matrix[i][j] + 1;
			lower = matrix[i][j];
			if (lower > higher) {
				int temp = higher;
				higher = lower; lower = temp;
			}
			if (result[higher] < lower) {
				result[higher] = lower;
			}
		}
	}

	return result;
}


#endif
