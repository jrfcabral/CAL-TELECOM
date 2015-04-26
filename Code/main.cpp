#include <iostream>
#include <cstdlib>
#include <boost/heap/fibonacci_heap.hpp>
#include <fstream>
#include "Graph.h"

Graph<int> randomGraphTests(int numVertex, int edgeProb){


	Graph<int> graph = Graph<int>();
	for(int i = 0; i < numVertex; i++){
		graph.addVertex(i);
	}

	for(int j = 0; j < numVertex; j++){
		for(int k = j+1; k < numVertex; k++){
			if(rand() % 1000 < edgeProb){
				int randNum = rand() % 1000;
				graph.addEdge(j, k, randNum);
				graph.addEdge(k, j, randNum);
			}
		}
	}

	return graph;
}

void dijkstraEdgeTests()
{
	ofstream out;
	out.open("dijsktra_edges.csv", ios::trunc);
	out << "Probability(%),Time(s)" << endl;
	for (int i = 1; i <= 1000; i++){
		Graph<int> graph = randomGraphTests(500,i);
		out << i<< ","<<graph.dijkstra(graph.getVertexSet().at(1), 10000) << endl;
		cout << i << endl;
	}
}
void dijkstraNodeTests()
{
	ofstream out;
		out.open("dijsktra_nodes.csv", ios::trunc);
		for (int i = 100; i <= 600; i++){
			Graph<int> graph = randomGraphTests(i,50);
			out << i<< ","<<graph.dijkstra(graph.getVertexSet().at(1), 10000) << endl;
			cout << i << endl;
		}
}
void primNodeTests()
{
	ofstream out;
	clock_t begin , end;
	out.open("prim_nodes.csv", ios::trunc);
	for (int i = 100; i <= 600; i++){
		Graph<int> graph = randomGraphTests(i,500);
		begin = clock();
		graph.prim();
		end = clock();
		out << i<< ","<<(double)end-begin<< endl;
		cout << i << endl;
	}
}

void primEdgeTests()
{
	ofstream out;
	clock_t begin , end;
	out.open("prim_edges.csv", ios::trunc);
	for (int i = 2; i <= 1000; i++){
		Graph<int> graph = randomGraphTests(500,i);
		begin = clock();
		graph.prim();
		end = clock();
		out << i<< ","<<(double)end-begin<< endl;
		cout << "prim" << i << endl;
	}
}
int tests(){
	srand(time(NULL));
	//dijkstraEdgeTests();
	//dijkstraNodeTests();
	primEdgeTests();
	//primNodeTests();




#ifndef unix
	cin.get();
#endif

}
