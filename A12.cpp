#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <io/EdgeListReader.h>
using namespace std;
//Compiler version g++ 6.3.0

int maxused = 0;

std::vector<int> init(int size) { //Init the vector which holds our colours for each vector

	std::vector<int> col;


	for (int i = 0; i < size; i++)

	{

		col.push_back(-1);

	}

	return col;

}

bool coloringNode(std::vector<int> &col, NetworKit::node currNode, NetworKit::Graph &g, int grad) {

	std::vector<NetworKit::node> neighbors = g.neighbors(currNode); //Nachbarn finden

	int freecol = 1;

	int size = neighbors.size(); //Anzahl der Nachbarn

	for (int i = 0; i < size; i++) //Nachbarn durchgehen und freie Farbe ermitteln.

	{

		if (col[neighbors[i]] == freecol) { //Wenn die Farbe belegt ist nehm die nächst hoehere.

			freecol = freecol + 1;
			if (freecol>(grad + 1)) {
				return false;
			}
			i = -1; continue; //Schaue wieder alle Nachbarn von vorne an, weil ja Nachbar 1 vielleicht eine hoehere Farbe hat.

		}

	}

	col[currNode] = freecol; //weise dem Knoten die freie Farbe zu.
	return true;
}

int gradvonGraph(std::vector<NetworKit::node> nodesOfGraph, NetworKit::Graph &g) {
	int grad = 0;
	for (int i = 0; i<g.numberOfNodes(); i++) {
		std::vector<NetworKit::node> neighbors = g.neighbors(nodesOfGraph[i]); //Nachbarn finden
		if (grad<neighbors.size()) {
			grad = neighbors.size();
		}
	}
	return grad;
}

void ausgabe(int wmax, std::vector<int> &col, NetworKit::Graph &g, int grad, std::vector<NetworKit::node> nodesOfGraph) {
	int m = 0; //#klauseln
	int n = (wmax - 1);//#variablen
	m = m + wmax - 1; //jeder knoten ist gefärbt
	m = m + (wmax - 1)*(grad + 1);//jeder knoten kann nur eine Farbe haben
	for (int i = 0; i<wmax - 1; i++) {//jeder nachbar hat eine andere Farbe
		for (int j = i + 1; j<wmax - 1; j++) {
			bool t = g.hasEdge(nodesOfGraph[i], nodesOfGraph[j]);
			if (t) {
				m = m + 1;
			}
		}
	}
	m = m + (wmax - 1)*(grad + 1);//Farbe wird genutzt oder nicht
	m = m + ((grad + 1) - maxused);//ungenutzte Farben
	std::cout << "p wcnf " << n << " " << m << " " << wmax << std::endl;//erste ausgabezeile

	for (int i = 0; i<wmax - 1; i++) {//die erste harte klausel
		std::cout << wmax << " " << i << " " << col[i] << " " << 0 << std::endl;
	}
	for (int i = 0; i<wmax - 1; i++) {//jeder knoten hat nur eine Farbe
		for (int j = 0; j<grad + 1; j++) {
			if (col[i] != j) {
				std::cout << wmax << " " << i << " " << col[i] << " " << -i << j << " " << 0 << std::endl;
			}
		}
	}
	for (int i = 0; i<wmax - 1; i++) {//jeder nachbar hat eine andere Farbe
		std::vector<NetworKit::node> neighbors = g.neighbors(nodesOfGraph[i]);
		int s = neighbors.size();
		for (int j = 0; j<s; j++) {
			std::cout << wmax << " " << i << " " << col[i] << " " << -j << col[i] << " " << 0 << std::endl;
		}
	}
	for (int i = 0; i < grad + 1; i++) {//Farbe wird genutzt oder kein Knoten hat die Farbe
		bool t = false;
		for (int j = 0; j < wmax - 1; j++) {
			if (i == col[j]) {
				std::cout << wmax << " " << j << " " << col[j] << " " << i << " " << 0 << std::endl;
				t = true;
			}
		}
		if (!t) {
			for (int j = 0; j < wmax - 1; j++) {
				std::cout << wmax << " " << -j << " " << col[j] << " " << -i << " " << 0 << std::endl;
			}
		}
	}
	for (int i = maxused; i <= grad + 1; i++) {//Farbe wird nicht genutzt
		std::cout << 1 << " " << -i << " " << 0 << std::endl;
	}
}

int main(int argc, const char *argv[])
{
	NetworKit::EdgeListReader reader{ ' ', 0 };

	auto g = reader.read(argv[1]);

	int size = g.numberOfNodes();

	int wmax = size + 1;

	std::vector<NetworKit::node> nodesOfGraph = g.nodes();

	auto col = init(size);

	int grad = gradvonGraph(nodesOfGraph, g);

		for (int i = 0; i < size; i++)//Jeden Knoten durchgehen und faerben.

		{

			if (!coloringNode(col, nodesOfGraph[i], g, grad)) {
				std::cout << "Faerbung nicht moeglich."<<std::endl;
					return -1;
			}

		}
		ausgabe(wmax, col, g, grad, nodesOfGraph);


}