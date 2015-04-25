
/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <stdlib.h>
#include <boost/heap/fibonacci_heap.hpp>
#include <ctime>
#include <sstream>

#include "graphviewer.h"

using namespace std;
using namespace boost::heap;

template <class T> class Edge;
template <class T> class Graph;
struct edge_comparator;
struct vertex_comparator;

template <class T>
class Vertex{
	T info;
	vector<Edge<T>  > adj;
	Vertex<T> *path;
	int dist;
	bool visited;
	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
	typename boost::heap::fibonacci_heap<Vertex<T>*, compare<vertex_comparator> >::handle_type handle;
	bool hasParent = false;
public:
	Vertex<T>* parent;
	int key;
	Vertex(T in);
	friend class Graph<T>;

};


template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	typename vector<Edge<T> >::iterator it= adj.begin();
	typename vector<Edge<T> >::iterator ite= adj.end();
	while (it!=ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}

template <class T>
Vertex<T>::Vertex(T in): info(in), visited(false){/*path = NULL;*/ dist = 0;}


template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w) {
	Edge<T> edgeD(dest,w);
	adj.push_back(edgeD);
}

template <class T>
class Edge {
	Vertex<T> * dest;
	typename fibonacci_heap<Edge<T>, boost::heap::compare<edge_comparator> >::handle_type handle;
public:
	int weight;
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w){}

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
public:
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	vector<Vertex<T> * > getVertexSet() const;
	int getNumVertex() const;
	Graph<T> prim();
	void view();
	bool findVertex(const T &info) const;
	double dijkstra(Vertex<T> *v, int range);
};

template <class T>
void Graph<T>::view()
{
	GraphViewer* gv = new GraphViewer(1400,800, true);
	int n = 0;
	gv->createWindow(1400, 800);
	for (unsigned int i = 0; i < vertexSet.size();i++){
		gv->addNode(vertexSet.at(i)->info);
		gv->setVertexColor(vertexSet.at(i)->info, "black");
		for(unsigned int j = 0; j < vertexSet.at(i)->adj.size();j++){
			gv->addEdge(n++, vertexSet.at(i)->info, vertexSet.at(i)->adj.at(j).dest->info, EdgeType::DIRECTED);
			stringstream ss;
			ss << vertexSet.at(i)->adj.at(j).weight;
			gv->setEdgeLabel((n-1), ss.str());

		}
	}
	gv->rearrange();

}


struct edge_comparator{
	bool operator()(const Edge<int> e1, const Edge<int> e2) const{
		return e1.weight > e2.weight;
	}
};

struct vertex_comparator{
	bool operator()(const Vertex<int>* v1, const Vertex<int>* v2) const{
		//cout << "comparing" << v1->key << "with" << v2->key << endl << (v1->key < v2->key) << endl;
		return v1->key > v2->key;
	}
};

template <class T>
Graph<T> Graph<T>::prim(){

	Graph<T> result = Graph<T>();
	vector<Graph<T> > subgraphs;
	fibonacci_heap<Vertex<T>*, compare<vertex_comparator> > pq;
	vertexSet.at(0)->key = 0;
	vertexSet.at(0)->handle = pq.push(vertexSet.at(0));
	for (unsigned int i = 1; i < vertexSet.size(); i++){
		vertexSet.at(i)->key = 9999999;
		vertexSet.at(i)->handle = pq.push(vertexSet.at(i));
		vertexSet.at(i)->visited = false;
	}

	while(pq.size()){
		Vertex<T>* v = pq.top();
		v->visited = true;

		if (v->hasParent){
			result.addVertex(v->info);
			result.addEdge(v->parent->info, v->info,v->key);
		}
		else{
			subgraphs.push_back(result);
			result = Graph<T>();
			result.addVertex(v->info);
			cout << "novo subgrafo detetado" << endl;
		}


		pq.pop();


		for(unsigned int i = 0; i < v->adj.size(); i++){
			Vertex<T>* d = v->adj.at(i).dest;

			if (d->key > v->adj.at(i).weight  && !d->visited){
				d->key = v->adj.at(i).weight;
				d->parent = v;
				d->hasParent = true;
				pq.increase(d->handle);

			}
		}
	}
	for(int i = 0; i < subgraphs.size(); i++)
		subgraphs.at(i).view();
	return result;

}


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}
template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
	return vertexSet;
}

template <class T>
bool Graph<T>::addVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++)
		if ((*it)->info == in) return false;
	Vertex<T> *v1 = new Vertex<T>(in);
	vertexSet.push_back(v1);
	return true;
}

template <class T>
bool Graph<T>::removeVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++) {
		if ((*it)->info == in) {
			Vertex<T> * v= *it;
			vertexSet.erase(it);
			typename vector<Vertex<T>*>::iterator it1= vertexSet.begin();
			typename vector<Vertex<T>*>::iterator it1e= vertexSet.end();
			for (; it1!=it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}
			delete v;
			return true;
		}
	}
	return false;
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {

	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
			{ vS=*it; found++;}
		if ( (*it)->info == dest )
			{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	vS->addEdge(vD,w);
	return true;
}

template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
			{ vS=*it; found++;}
		if ( (*it)->info == dest )
			{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	return vS->removeEdgeTo(vD);
}

template<class T>
bool Graph<T>::findVertex(const T &coise)const{
	typename vector<Vertex<T> *>::iterator it = this->getVertexSet().begin();
	typename vector<Vertex<T> *>::iterator ite = this->getVertexSet().end();
	for(;it != ite; it++){
		if(coise == (*it)->info){
			return true;
		}
	}
	return false;
}

template<class T>
double Graph<T>::dijkstra(Vertex<T> *v, int range){

	clock_t begin = clock(), end;


	for(int i = 0; i < vertexSet.size(); i++){
		vertexSet.at(i)->path = NULL;
		vertexSet.at(i)->dist = 9999999;
	}

	v->dist = 0;
	fibonacci_heap<Vertex<T>*, compare<vertex_comparator> > qehuehue;
	v->handle = qehuehue.push(v);

	while(!qehuehue.empty()){
		Vertex<T> *vert = qehuehue.top();
		qehuehue.pop();
		typename vector<Edge<T> >::iterator itt= (vert->adj).begin();
		typename vector<Edge<T> >::iterator imtt= (vert->adj).end();
		for(;itt != imtt; itt++){
			Vertex<T> *w = itt->dest;
			if(vert->dist + itt->weight < w->dist){
				int old_dist = w->dist;
				w->dist = vert->dist + itt->weight;
				w->path = vert;
				if(old_dist ==  9999999){
					w->handle = qehuehue.push(w);
				}
				else{
					qehuehue.increase(w->handle);
				}
			}
		}
	}

	cout << "Node ---> keyance to \"main\" node\n";
	for(unsigned int i = 0; i < this->vertexSet.size(); i++){
		cout << i+1 << "---> " << this->vertexSet.at(i)->dist << endl;

		if(this->vertexSet.at(i)->dist > range){
			cout << "Removing node " << i+1 << endl;
			this->removeVertex(this->vertexSet.at(i)->info);
			i--;
		}

	}

	end = clock();
	return (double)begin - end;
}

#endif /* GRAPH_H_ */
