#include <iostream>
#include <cstdlib>
#include <boost/heap/fibonacci_heap.hpp>

#include "Graph.h"

Graph<int> randomGraph(int numVertex, int edgeProb){

	srand(time(NULL));

	Graph<int> graph = Graph<int>();
	for(int i = 0; i < numVertex; i++){
		graph.addVertex(i);
	}

	for(int j = 0; j < numVertex; j++){
		for(int k = j+1; k < numVertex; k++){
			if(rand() % 10 < edgeProb){
				int randNum = rand() % 100;
				graph.addEdge(j, k, randNum);
				graph.addEdge(k, j, randNum);
			}
		}
	}

	return graph;
}




int main(){
	/*Graph<int> graph = Graph<int>();

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

	float dijkstra_elapsed = graph.dijkstra(graph.getVertexSet()[0], 11);
	graph.view();
	graph.prim().view();
	cout << "done" << endl;*/

	cout << "Starting Dijkstra complexity analysis.\n";
	cout << "Sparse graphs with 30% chance of edge and a range constraint of 50.\n";
	//for(int i = 5; i <= 1000; i++){
		Graph<int> gr = randomGraph(100, 3);
		gr.dijkstra(gr.getVertexSet()[1], 50);

	//}

#ifndef unix
	cin.get();
#endif

}
