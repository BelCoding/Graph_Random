#ifndef _depthbreadth_hpp_
#define _depthbreadth_hpp_

#include <unordered_map>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
#include <tr1/array>
#include <vector>
#include <map>
#include <algorithm>

using AdjacencyList = std::unordered_map<int, std::vector<int>>;


class PathVector{


	public:
	PathVector();
    ~PathVector();
	AdjacencyList::const_iterator next_it;
	int index_next;
	std::vector<int> visited; // parallel vector to path to control the visited nodes.
	std::vector<int> path; // We create a path with the nodes to follow in order BFS.
	int size_path=0;
};

#endif
