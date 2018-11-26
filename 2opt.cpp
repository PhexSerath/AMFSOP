//Lucas Petersen(581277)
//Steven Müller(581583)


#include <cstdlib>
#include <fstream>
#include <vector>

#include <io/EdgeListReader.h>



int main(int argc, const char *argv[]) {
        std::cout << "test" << std::endl;
	NetworKit::EdgeListReader reader{};
	auto g = reader.read(argv[1]);
	int size = g.numberOfNodes();
	std::vector<NetworKit::node> nodesOfGraph = g.nodes(); //Alle Knoten in einen vector schreiben.
	std::vector<int> route(size);
        for(int i = 0; i < size; i++){
            route[i] = i;
        }
        
        bool better = true;
        
        while(better) {
            better = false;
            
            for(int k = 0; k < size; k++) {
                int kNext = (k +1)%size;
                for(int l = k+2; l < size; l++) {
                    int lNext = (l +1)%size;
                    if ( g.weight(nodesOfGraph[route[k]], nodesOfGraph[route[kNext]])
                         >  g.weight(nodesOfGraph[route[l]], nodesOfGraph[route[l]])){
                        better = true;
                        int tmp = route[l];
                        route[l] = route[kNext];
                        route[kNext] = tmp;
                    }
                }
            }
            
            
        }
        
        
        for (int i = 0; i < size; i++) {// Gibt die Knoten + Farbe aus.
		std::cout << i << " ";
	}
        std::cout << std::endl;
}