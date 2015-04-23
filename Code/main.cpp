#include <iostream>
#include <cstdlib>
#include <boost/heap/fibonacci_heap.hpp>

#include "Graph.h"
int main(){
	Graph<int> graph = Graph<int>();

	graph.addVertex(1);
	graph.addVertex(2);
	graph.addVertex(3);
	graph.addVertex(4);
	graph.addVertex(5);
	graph.addVertex(6);

	graph.addEdge(1,2,1);
	graph.addEdge(2,1,1);
	graph.addEdge(2,3,10);
	graph.addEdge(3,2,10);
	graph.addEdge(1,4,3);
	graph.addEdge(4,1,3);
	graph.addEdge(4,5,1);
	graph.addEdge(5,4,1);
	graph.addEdge(2,5,1);
	graph.addEdge(5,2,1);
	graph.addEdge(3,6,1);
	graph.addEdge(6,3,1);

	graph.view();
	cout << "out" << endl;

	graph.prim().view();
	cout << "done" << endl;

	float dijkstra_elapsed = graph.dijkstra(graph.getVertexSet()[0], 11);
	graph.view();
	cout << "done" << endl;
	cout << "Time spent on dijkstra: " << dijkstra_elapsed << " ms" << endl;
#ifndef unix
	cin.get();
#endif

}
