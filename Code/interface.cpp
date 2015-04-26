#include <iostream>
#include "Graph.h"

using namespace std;

void clearScreen(){
#ifndef unix
	system("cls");
#else
	system("clear");
#endif
}

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

int getInput(int min, int max){
	int choice;
	do{
		cout << "> ";
		try{
			cin >> choice;
			if(cin.fail()){
				throw -1;
			}
		}
		catch(int ex){
			cout << "Input invalido. Introduza um numero correspondente a uma das opçoes listada acima.\n";
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}
		if(choice > max || choice < min){
			cout << "O numero introduzido nao corresponde a uma opcao. Escolha uma das opcoes acima.\n";
		}
		cin.clear();
		cin.ignore(10000, '\n');
	}while(choice < min || choice > max);

	return choice;
}

int partOneTreatment(Graph<int> graph){
	clearScreen();
	cout << "No contexto escolhido (primeira parte) e necessario providenciar os seguintes parametros:\n" <<
			"Vertice que representa a central\nRaio de abrangencia da central\n";

	cout << "Introduza o numero do vertice que representa a central\n";
	int vert = getInput(0, graph.getVertexSet().size()-1);
	cout << "Introduza o raio de abrangencia pretendido\n";
	int range = getInput(1, 10000);

	cout << "Limitando o grafo ao raio de abrangencia providenciado...\n";
	graph.dijkstra(graph.getVertexSet().at(vert), range);
	cout << "Computando a arvore de expansao minima...\n";
	Graph<int> primmed = graph.prim();
	primmed.view();

	return 0;

}

int partTwoTreatment(Graph<int> graph){
	clearScreen();
	cout << "No contexto escolhido (segunda parte) nao e necessario providenciar quaisquer parametros.\n";

	cout << "Detetando subgrafos e computando arvore(s) de expensao minima...\n";
	Graph<int> primmed = graph.prim();
	primmed.view();

	return 0;
}

Graph<int> graphGen(){
	clearScreen();
	int watdo = 0;
	Graph<int> randGraph;

	cout << "O gerador aleatorio necessita que sejam providenciados os seguintes parametros:\n" <<
			"Numero de vertices\nProbabilidade de haver aresta (inteiro entre 0 e 100)\n";
	while(watdo != 1){
		cout << "Introduza o numero de vertices pretendido\n";
		int vertNum = getInput(1, 10000);
		cout << "Introduza a probabilidade de aresta\n";
		int edgeProb = getInput(0, 100);

		randGraph = randomGraph(vertNum, edgeProb);
		randGraph.view();

		cout << "Quer proceder com este grafo ou deseja gerar de novo?\n1. Proceder\n2. Gerar de novo\n";
		watdo = getInput(1, 2);
	}

	return randGraph;
}



int graphMenu(int part){
	clearScreen();
	cout << "Escolha uma opcao:\n1. Gerador aleatorio de grafos\n2. Voltar atras\n\n";
	int choice = getInput(1, 2);

	if(choice == 1){
		Graph<int> graph = graphGen();
		if(part == 1){
			partOneTreatment(graph);
		}
		else if(part == 2){
			partTwoTreatment(graph);
		}
		else{
			cout << "Erro. Situacao inesperada. Voltando ao menu principal. (ENTER para continuar)\n";
			cin.get();
		}

		cout << "ENTER para voltar ao menu principal\n";
		cin.get();
		return 0;
	}
	else if(choice == 2){
		return 0;
	}
	return 1;
}


int main(){

	int done = 0;
	while(!done){
		clearScreen();
		cout << "Escolha o contexto:\n1. Primeira parte: Nos limitados a um raio e grafo garantidamente conexo.\n" <<
			"2. Segunda parte: Nos com distancia ilimitada e possibilidade de disconexao.\n3. Sair\n";


		int choice  = getInput(1, 3);

		if(choice == 3){
			return 0;
		}

		done = graphMenu(choice);
	}
}
