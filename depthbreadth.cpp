#include "depthbreadth.hpp"


PathVector::PathVector():index_next(0),size_path(0){}
PathVector::~PathVector(){}

template <typename Callable>
void iterate_dfs(const AdjacencyList &dag, PathVector& vis, int root, Callable &&fnc){
	// interate the dag in depth first fashion and call the function "fnc" on every edge like so f(current edge)

	fnc(root); // Print the current node
	// Find the root node given.
	vis.next_it = dag.find(root);
		// When a edge is not already in the Path vector we have to:
	vis.path.push_back(root); //put the node in the path vector

	//path.visited.push_back(1); //mark as visited node // not used
	//path.size_path++; // not used

	if( vis.next_it != dag.end() ){

		// Follow edges, dfs path
		for(auto& edge : vis.next_it->second ){

			vis.index_next++;
			//std::cout << path.index_next << "[index_next] " << path.size_path << "[size_path] " << edge << "[edge] " << std::endl;
			if(std::find(vis.path.begin(), vis.path.end(), edge) == vis.path.end() ){ iterate_dfs(dag, vis, edge, fnc); }
		}
	}
}


template <typename Callable>
void iterate_bfs(const AdjacencyList &dag, int root, Callable &&fnc){
	// interate the dag in breadth first fashion and call the function "fnc" on every edge like so f(current edge)

	PathVector vis; //Visited nodes

	// next_it will find the root node given.
	// Iterator over the nodes
	//	vis.index_next = 0;

	// parallel vector to path to control the visited nodes.
	// We create a path with the nodes to follow in order BFS.
	//vis.size_path=0;

	// Assuming that the first node root is in the list, if does not it just will go out after first iteration.
	vis.path.push_back(root);// put the root node in the list
	vis.visited.push_back(0); // mark as a not visited node
	vis.size_path++;

	while(vis.index_next < vis.size_path ){

		fnc(vis.path[vis.index_next]); //Current edge that we are looking for //Print the current node

		vis.next_it = dag.find(vis.path[vis.index_next]); // find in dag (Full Graph), the current node in the vis.
		if( vis.visited[vis.index_next] == 0 && vis.next_it != dag.end() ){ // SAFE, not to follow the edges in case does not exist
			//When we find It exist in the graph and It is not visited
			vis.visited[vis.index_next] = 1;
			//Marked as Visited and follow his edges:

			for(auto& edge : vis.next_it->second ){ // Iterate in breadth first fashion over the vector which contains all the edges on each node.

				if( std::find(vis.path.begin(), vis.path.end(), edge) == vis.path.end() ){ // #include <algorithm>
					// When a edge is not already in the Path vector we have to:

					vis.path.push_back(edge); //put the node in the path vector
					vis.visited.push_back(0); //mark as a not visited node
					vis.size_path++;
				}
			}
		}

	++vis.index_next;
	}
}


int main(){

/*	AdjacencyList dag{
		{0, {1, 2}},
		{1, {3, 4}}
	};
*/

/*
	AdjacencyList dag{
		{0, {1, 2}},
		{1, {4, 5}},
		{2, {3, 4}},
		{3, {1, 2}},
		{4, {3, 5}},
		{5, {7, 2}},
		{6, {6, 5}},
		{7, {4, 6}},

	};
*/
	const int MAX_NODES = 30;
    srand( (int)time(0) );
	AdjacencyList dag;
	int TOT_Nodes = ( 5 + rand() % MAX_NODES );
	std::cout << "Random Graph generated: " << std::endl;

	for(int i = 0; i < TOT_Nodes; i++){

		std::cout << i << " | ";
		int TOT_edges = (rand() % TOT_Nodes );
		std::vector<int> v;
		for(int ii = 0; ii < TOT_edges; ii++){
			int ran_n = rand() % TOT_Nodes;
			v.push_back( ran_n );
			std::cout << ran_n << " ";

		}
		std::cout << std::endl;

		dag.emplace(i,v);
	}

	auto print = [](int node){ std::cout << node << '\n';};

	PathVector path;
//	path.size_path = 0;
//	path.index_next=0;

	path.path.push_back(0);// put the root node in the list
	path.visited.push_back(0); // mark as a not visited node
	path.size_path++;

	std::cout << "\n-------------\n\n";
	std::cout << "DFS:\n";
	iterate_dfs(dag, path, 0, print);

	std::cout << "\n-------------\n\n";
	std::cout << "BFS:\n";
	iterate_bfs(dag, 0, print);

return 0;
}

/*
DFS:
0
1
4
3
2
5
7
6


BFS:
0
1
2
4
5
3
7
6

*/
