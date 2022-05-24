#pragma once
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

int maxflow(List<char>& V, Matrix<int>& M, Matrix<int>& adj) {
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

