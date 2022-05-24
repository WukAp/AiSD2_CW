#pragma once
#include <fstream>
#include "queue.h"
#include "List.h"
#include "Matrix.h"
using namespace std;

class Edmonds_Karp
{
public:
	struct pair {
		int first;
		long second;
	};
	List<char> listofvertexes;
	Matrix<int> capacity;
	Matrix<int> adj;
	long INF = 100000;

	~Edmonds_Karp() {
		capacity.clear();
		adj.clear();
		listofvertexes.clear();
	}

	int maxflow() {
		if (listofvertexes.isEmpty())
			throw invalid_argument("Please enter data for the graph");
		int maximum_flow = 0;
		List<int> parent(capacity.get_size(), 0);
		int new_flow;
		if (bfs(0, listofvertexes.get_size() - 1, parent) == 0)
			throw invalid_argument("There are no ways from S to T at all");

		while (new_flow = bfs(0, listofvertexes.get_size() - 1, parent)) {
			maximum_flow += new_flow;
			int cur = listofvertexes.get_size() - 1;
			while (cur != 0) {
				int prev = parent.at(cur);
				capacity.at(prev).set(cur, capacity.at(prev).at(cur) - new_flow);
				capacity.at(cur).set(prev, capacity.at(cur).at(prev) + new_flow);
				cur = prev;
			}
		}
		return maximum_flow;
	}

	void input(string input) {
		ifstream file(input);
		if (!file.is_open())
			throw runtime_error("File was not found, check its name/location");
		int symb_num = 0;
		char symb;
		int cap;
		char first_vrtx, scnd_vrtx;
		//reading the vertexes list
		while (!file.eof()) {
			file >> noskipws >> symb;
			if ((symb_num == 0 || symb_num == 2) && !listofvertexes.contains(symb))
				listofvertexes.push_back(symb);
			symb_num++;
			if (symb == '\n' || file.eof())
				symb_num = 0;
		}

		if (listofvertexes.at(0) != 'S' || listofvertexes.at(listofvertexes.get_size() - 1) != 'T')
			throw invalid_argument("Please start your graph with S and finish with T");

		file.clear();
		file.seekg(0);
		List<int> temp;

		for (int i = 0; i < listofvertexes.get_size(); i++) {
			for (int j = 0; j < listofvertexes.get_size(); j++)
				temp.push_back(0);
			capacity.push_back(temp);
			temp.reset();
		}

		//reading the avaliable capacity
		while (!file.eof())
		{
			if (symb_num != 4) {
				file >> noskipws >> symb;

				if (symb_num == 0)
					first_vrtx = symb;

				else if (symb_num == 2)
					scnd_vrtx = symb;
			}

			else {
				file >> cap;
				capacity.at(listofvertexes.get_index((char)first_vrtx)).set(listofvertexes.get_index((char)scnd_vrtx), cap);
			}

			symb_num++;
			if (symb == '\n' || file.eof())
				symb_num = 0;

		}

		for (int i = 0; i < capacity.get_size(); i++) {
			temp.reset();
			for (int j = 0; j < capacity.at(i).get_size(); j++) {
				temp.push_back(capacity.at(i).at(j));
			}
			adj.push_back(temp);
		}

		for (int i = 0; i < adj.get_size(); i++) {
			for (int j = i; j < adj.at(i).get_size(); j++) {
				adj.at(j).set(i, adj.at(i).at(j));
			}
		}


		temp.reset();

		List<int> parent(capacity.get_size(), 0);

	}

	int bfs(int s, int t, List<int>& parent) {
		//s - source, t - sink
		for (int i = 0; i < parent.get_size(); i++)
			parent.set(i, -1);
		parent.set(s, -2);
		Queue <pair> queue;
		queue.push({ s, INF });
		while (queue.get_size() != 0) {
			int cur = queue.getTop().first;
			int flow = queue.getTop().second;
			queue.takeTop();

			for (int next = 0; next < adj.at(cur).get_size(); next++) {
				if (parent.at(next) == -1 && capacity.at(cur).at(next)) {
					parent.set(next, cur);
					int new_flow;
					if (capacity.at(cur).at(next) < flow)
						new_flow = capacity.at(cur).at(next);
					else
						new_flow = flow;
					if (next == t)
						return new_flow;
					queue.push({ next, new_flow });
				}
			}
		}

		//if there are no ways from s to t
		return 0;
	}
};

