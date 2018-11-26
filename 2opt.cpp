//Lucas Petersen(581277)
//Steven Müller(581583)


#include <cstdlib>
#include <fstream>
#include <vector>

#include <io/EdgeListReader.h>



int main(int argc, const char *argv[]) {
        Aux::Log::setLogLevel("ERROR");
	NetworKit::EdgeListReader reader{' ', 0};
	auto g = reader.read(argv[1]);    
	int size = g.numberOfNodes();
	std::vector<NetworKit::node> nodesOfGraph = g.nodes(); //Alle Knoten in einen vector schreiben.
	std::vector<int> route(size); 
        for(int i = 0; i < size; i++){//Startroute Reihenfolge der Knoten Ids nehmen.
            route[i] = i;
        }
        
        bool better = true;
        while(better) { //aufhoeren falls keine Verbessrung gefunden wird
            better = false;
            
            for(int k = 0; k < size; k++) {
                int kNext = (k +1)%size; // Knoten nach k in der Route
                
                for(int l = k+2; l < size; l++) {
                    int lNext = (l +1)%size;// Knoten nach k in der Route
                    
                    if ( g.weight(nodesOfGraph[route[k]], nodesOfGraph[route[kNext]])
                            + g.weight(nodesOfGraph[route[l]], nodesOfGraph[route[lNext]])
                         >  g.weight(nodesOfGraph[route[k]], nodesOfGraph[route[l]])
                            + g.weight(nodesOfGraph[route[kNext]], nodesOfGraph[route[lNext]])){ //Kanten Austauch
                        better = true;
                        int tmp = route[l];
                        route[l] = route[kNext];
                        route[kNext] = tmp;
                    }
                }
            }
        }
        
        
        for (int i = 0; i < size; i++) {// Gibt die Knoten + Farbe aus.
		std::cout << route[i] << " ";
	}
        std::cout << std::endl;
}