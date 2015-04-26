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
			if(rand() % 100 < edgeProb){
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
	for (int i = 1; i <= 100; i++){
		int time = 0;
		for(int k = 0; k < 10;k++){
			Graph<int> graph = randomGraphTests(200,i);
			time += graph.dijkstra(graph.getVertexSet().at(1), 10000);
			graph.apagar();
		}
		out << i<< ","<< time/10 << endl;
		cout << i << endl;
	}
}
void dijkstraNodeTests()
{
	ofstream out;
		out.open("dijsktra_nodes.csv", ios::trunc);
		for (int i = 100; i <= 600; i++){
			int time = 0;
			for(int k = 0; k < 10;k++){
				Graph<int> graph = randomGraphTests(i,300);
				time += graph.dijkstra(graph.getVertexSet().at(1), 10000);
				graph.apagar();
			}
			out << i<< ","<< time/10 << endl;
			cout << i << endl;
		}
}
void primNodeTests()
{
	ofstream out;
	clock_t begin , end;
	out.open("prim_nodes.csv", ios::trunc);
	for (int i = 100; i <= 600; i++){
		begin = clock();
		for (int k = 0; k < 10; k++){
			Graph<int> graph = randomGraphTests(i,300);
			graph.prim();
			graph.apagar();
		}
		end = clock();
		out << i<< ","<<(end-begin)/10<< endl;
		cout << i << endl;
	}
}

void primEdgeTests()
{
	ofstream out;
	clock_t begin , end;
	out.open("prim_edges.csv", ios::trunc);
	for (int i = 2; i <= 100; i++){
		begin = clock();
		for (int k=0;k < 10; k++){
			Graph<int> graph = randomGraphTests(200,i);
			graph.prim();
			graph.apagar();
		}
		end = clock();
		out << i<< ","<<(end-begin)/10<< endl;
		cout << "prim" << i << endl;
	}
}
int tests(){
	srand(time(NULL));
	dijkstraEdgeTests();
	//dijkstraNodeTests();
	//primEdgeTests();
	//primNodeTests();




#ifndef unix
	cin.get();
#endif

}
