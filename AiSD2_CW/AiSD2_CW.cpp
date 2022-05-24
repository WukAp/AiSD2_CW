#include "Karp.h"
#include <fstream>

int main() {
	Matrix<int> M;
	Matrix<int> adj;
	List<char> V;

	{
		ifstream file("input3.txt");
		if (!file.is_open())
			throw runtime_error("File was not found");
		int symb_num = 0;
		char symb;
		int cap;
		char v1, v2;
		while (!file.eof()) {
			file >> noskipws >> symb;
			if ((symb_num == 0 || symb_num == 2) && !V.contains(symb))
				V.push_back(symb);
			symb_num++;
			if (symb == '\n' || file.eof())
				symb_num = 0;
		}

		if (V.at(0) != 'S')
			throw invalid_argument("Graph should start with 'S'-vertex");

		if (V.at(V.get_size() - 1) != 'T')
			throw invalid_argument("Graph should finish with 'T'-vertex");

		file.clear();
		file.seekg(0);

		List<int> temp_list;

		for (int i = 0; i < V.get_size(); i++) {
			for (int j = 0; j < V.get_size(); j++)
				temp_list.push_back(0);
			M.push_back(temp_list);
			temp_list.reset();
		}

		while (!file.eof())	{
			if (symb_num != 4) {
				file >> noskipws >> symb;

				if (symb_num == 0)
					v1 = symb;

				else if (symb_num == 2)
					v2 = symb;
			}

			else {
				file >> cap;
				M.at(V.get_index((char)v1)).set(V.get_index((char)v2), cap);
			}

			symb_num++;
			if (symb == '\n' || file.eof())
				symb_num = 0;

		}

		for (int i = 0; i < M.get_size(); i++) {
			temp_list.reset();
			for (int j = 0; j < M.at(i).get_size(); j++) {
				temp_list.push_back(M.at(i).at(j));
			}
			adj.push_back(temp_list);
		}

		for (int i = 0; i < adj.get_size(); i++) {
			for (int j = i; j < adj.at(i).get_size(); j++) {
				adj.at(j).set(i, adj.at(i).at(j));
			}
		}

		temp_list.clear();
	}
		
	cout <<"Max flow: "<< maxflow(V, M, adj);	
	
	return 0;
}
