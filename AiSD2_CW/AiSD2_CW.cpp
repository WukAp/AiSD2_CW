#include "Matrix.h"
#include "Queue.h"
#include "List.h"
#include <fstream>

long INF = 100000;


int bfs(int s, int t, Matrix<int>& M, Matrix<int>& adj, List<int>& temp_list) {
	for (int i = 0; i < temp_list.get_size(); i++)
		temp_list.set(i, -1);
	temp_list.set(s, -2);

	struct pair {
		long first;
		long second;
	};

	Queue <pair> queue;
	queue.push({ s, INF });
	while (queue.get_size() != 0) {
		int curr = queue.getTop().first;
		int flow = queue.getTop().second;
		queue.takeTop();

		for (int next = 0; next < adj.at(curr).get_size(); next++) {
			if (temp_list.at(next) == -1 && M.at(curr).at(next)) {
				temp_list.set(next, curr);
				int new_flow;
				if (M.at(curr).at(next) < flow)
					new_flow = M.at(curr).at(next);
				else
					new_flow = flow;
				if (next == t)
					return new_flow;
				queue.push({ next, new_flow });
			}
		}
	}
	return 0;
}

int maxflow( List<char>&V, Matrix<int> &M, Matrix<int>& adj) {
	if (V.isEmpty())
		throw invalid_argument("Graph is empty");
	int max_flow = 0;
	List<int> parent(M.get_size(), 0);
	int new_flow;
	if (bfs(0, V.get_size() - 1, M, adj, parent) == 0)
		throw invalid_argument("No path S->T");

	while (new_flow = bfs(0, V.get_size() - 1, M, adj, parent)) {
		max_flow += new_flow;
		int cur = V.get_size() - 1;
		while (cur != 0) {
			int prev = parent.at(cur);
			M.at(prev).set(cur, M.at(prev).at(cur) - new_flow);
			M.at(cur).set(prev, M.at(cur).at(prev) + new_flow);
			cur = prev;
		}
	}
	return max_flow;
}


int main() {
	Matrix<int> M;
	Matrix<int> adj;
	List<char> V;

	{
		ifstream file("input.txt");
		if (!file.is_open())
			throw runtime_error("File was not found, check its name/location");
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
