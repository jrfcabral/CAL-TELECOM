/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <stdlib.h>
#include <boost/heap/fibonacci_heap.hpp>
#include <boost/heap/priority_queue.hpp>
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
	bool visited;
	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
	typename boost::heap::fibonacci_heap<Vertex<T>*, compare<vertex_comparator> >::handle_type handle;
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
Vertex<T>::Vertex(T in): info(in), visited(false){}


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
	void dfs(Vertex<T> *v, vector<T> &res) const;
public:
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(Vertex<T> *v) const;
	int maxNewChildren(Vertex<T> *v, T &inf) const;
	vector<Vertex<T> * > getVertexSet() const;
	int getNumVertex() const;
	Graph<T> prim_pq();
	Graph<T> prim_fh();
	void view();

};

template <class T>
void Graph<T>::view()
{
	GraphViewer* gv = new GraphViewer(1400,800, true);
	int n = 0;
	gv->createWindow(1400, 800);
	for (unsigned int i = 0; i < vertexSet.size();i++){
		gv->addNode(vertexSet.at(i)->info);
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
Graph<T> Graph<T>::prim_pq(){

	Graph<T> result = Graph<T>();
	vector<Vertex<T>* > pq;
	vertexSet.at(0)->key = 0;
	pq.push_back(vertexSet.at(0));
	for (unsigned int i = 1; i < vertexSet.size(); i++){
		vertexSet.at(i)->key = 9999999;
		vertexSet.at(i)->visited = false;
		pq.push_back(vertexSet.at(i));
	}
	int k = pq.size();
	while(k)
	{
		Vertex<T> *v;
		unsigned int i;
		unsigned int minkey = 9999999;
		for(i = 0; i < pq.size(); i++){

			//cout << "vertice " << pq.at(i)->info << endl;
			if (pq.at(i)->key < minkey && !pq.at(i)->visited){
				v = pq.at(i);
			}


		}

		v->visited = true;
		result.addVertex(v->info);
		if (v->parent != NULL)
		result.addEdge(v->info, v->parent->info, v->key);

		k--;
		for(unsigned int j = 0; j < v->adj.size(); j++)
		{
			Vertex<T>* d = v->adj.at(j).dest;
			if (d->key > v->adj.at(j).weight  && !d->visited){
				d->key = v->adj.at(j).weight;
				d->parent = v;

			}
		}


	}
	return result;

}

template <class T>
Graph<T> Graph<T>::prim_fh(){

	Graph<T> result = Graph<T>();
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
		result.addVertex(v->info);
		if (v->parent)
			result.addEdge(v->parent->info, v->info,v->key);

		pq.pop();


		for(unsigned int i = 0; i < v->adj.size(); i++){
			Vertex<T>* d = v->adj.at(i).dest;
			if (d->key > v->adj.at(i).weight  && !d->visited){
				d->key = v->adj.at(i).weight;
				d->parent = v;
				pq.increase(d->handle);
			}
		}
	}
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




template <class T>
vector<T> Graph<T>::dfs() const {
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	vector<T> res;
	it=vertexSet.begin();
	for (; it !=ite; it++)
	    if ( (*it)->visited==false )
	    	dfs(*it,res);
	return res;
}

template <class T>
void Graph<T>::dfs(Vertex<T> *v,vector<T> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge<T> >::iterator it= (v->adj).begin();
	typename vector<Edge<T> >::iterator ite= (v->adj).end();
	for (; it !=ite; it++)
	    if ( it->dest->visited == false )
	    	dfs(it->dest, res);
}

template <class T>
vector<T> Graph<T>::bfs(Vertex<T> *v) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
			}
		}
	}
	return res;
}

template <class T>
int Graph<T>::maxNewChildren(Vertex<T> *v, T &inf) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	queue<int> level;
	int maxChildren=0;
	inf =v->info;
	q.push(v);
	level.push(0);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		int l=level.front();
		level.pop(); l++;
		int nChildren=0;
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
				level.push(l);
				nChildren++;
			}
		}
		if (nChildren>maxChildren) {
			maxChildren=nChildren;
			inf = v1->info;
		}
	}
	return maxChildren;
}



#endif /* GRAPH_H_ */