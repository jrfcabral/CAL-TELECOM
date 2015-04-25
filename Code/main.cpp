#include <iostream>
#include <cstdlib>
#include <boost/heap/fibonacci_heap.hpp>

#include "Graph.h"

Graph<int> randomGraph(int numVertex, int edgeProb){


	Graph<int> graph = Graph<int>();
	for(int i = 0; i < numVertex; i++){
		graph.addVertex(i);
	}

	for(int j = 0; j < numVertex; j++){
		for(int k = j+1; k < numVertex; k++){
			if(rand() % 100 < edgeProb){
				int randNum = rand() % 1000;
				graph.addEdge(j, k, randNum);
				graph.addEdge(k, j, randNum);
			}
		}
	}

	return graph;
}




int main(){
	srand(time(NULL));

Graph<int> graph = randomGraph(10, 10);
graph.view();
cin.get();
graph.prim().view();

#ifndef unix
	cin.get();
#endif

}
