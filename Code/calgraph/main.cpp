#include <iostream>
#include <cstdlib>
#include <boost/heap/fibonacci_heap.hpp>
#include <chrono>
#include <fstream>
#include "Graph.h"

using namespace std;
using namespace std::chrono;
int prim_prio_test(int vertexes){
	Graph<int> graph = Graph<int>();
	//	cout << "testando prio com " << vertexes << endl;
		for(int i = 1; i < vertexes; i++)
					graph.addVertex(i);
				for(int i = 1; i < vertexes;i++)
					for (int j = i+1; j < vertexes; j++){
						graph.addEdge(i,j,i);
						graph.addEdge(j,i,i);
					}




			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			graph.prim_pq();
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
			ofstream f;
			f.open("prim_results_prio.csv", ios::out | ios::app);
			f << vertexes << "," << duration << endl;
			f.close();
}
int prim_fh_test(int vertexes){
	Graph<int> graph = Graph<int>();
		//cout << "testando com " << vertexes << endl;
		for(int i = 0; i < vertexes; i++)
			graph.addVertex(i);
		for(int i = 0; i < vertexes;i++)
			for (int j = i+1; j < vertexes; j++){
				graph.addEdge(i,j,i);
				graph.addEdge(j,i,i);
			}




		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		graph.prim_pq();
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

		t1 = high_resolution_clock::now();
		graph.prim_fh();
		t2 = high_resolution_clock::now();
		auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
		ofstream f;
		f.open("results.cvs",(ios::app));
		f << vertexes << "," << duration1 << "," << duration2 << endl;
		f.close();
}

int main(){
	fstream f;
	f.open("prim_results_fibonacci.csv", ios::trunc);
	f.close();
	f.open("prim_results_prio.csv", ios::trunc);
	f.close();

	for (int i = 2; i < 700;i++){
			cout << "teste " << i << " feito" << endl;
			prim_fh_test(i);
	}

}
