#include <cstdlib>
#include <fstream>
#include <vector>

#include <io/SNAPGraphReader.h>


std::vector<int> init(int size) {  //Init the vector which holds our colours for each vector
	std::vector col;

	for (int i = 0; int i < size; int i++)
	{
		col.push_back(-1);
	}
	return col;
}

void coloringNode(std::vector<int> &col, Networkit::node *currNode, Networkit::Graph &g) {
	std::vector<Networkit::node> neighbors = g.neighbors(currNode); //Nachbarn finden
	int freecol = 1;
	int size = neighbor.size(); //Anzahl der Nachbarn
	for (int i = 0; i < size; i++) //Nachbarn durchgehen und freie Farbe ermitteln.
	{
		if (col[neighbors[i]] == freecol) { //Wenn die Farbe belegt ist nehm die nächst hoehere.
			freecol = freecol + 1;
			i = -1; continue; //Schaue wieder alle Nachbarn von vorne an, weil ja Nachbar 1 vielleicht eine hoehere Farbe hat.
		}
	}
	col[currNode] = freecol; //weise dem Knoten die freie Farbe zu.
}

int main(int argc, const char *argv[]) {
	NetworKit::SNAPGraphReader reader{ false, false };
	auto g = reader.read(argv[1]);
	auto col = init(g.numberOfNodes());
	int size = g.numberOfNodes();
	std::vector<Networkit::node> nodesOfGraph = g.nodes(); //Alle Knoten in einen vector schreiben.
	for (int i = 0; i < size; i++)//Jeden Knoten durchgehen und faerben.
	{
		coloringNode(col, nodesOfGraph[i], g);
	}
	for (int i = 0; i < size, i++) {// Gibt die Knoten + Farbe aus.
		std::cout << i <<" "<< col[i] << std::endl;
	}
}