//Lucas Petersen(581277)
//Steven Müller(581583)


#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>

#include <components/StronglyConnectedComponents.h>



int main(int argc, const char *argv[]) {
        Aux::Log::setLogLevel("ERROR");
	bool sat = true;
        int firstLiteral = 0;
        int secondLiteral = 0;
        
        NetworKit::Graph graph{0, false, true};
        std::string str; 
        std::vector<NetworKit::node> PositiveLiterals;
        std::vector<int> mappingPositiveLiterals;
        std::vector<NetworKit::node> NegativeLiterals;
        std::vector<int> mappingNegativeLiterals;
        
        do{
            std::getline(std::cin, str);
            auto cstr = str.c_str();
            int i = 0;
            int firstLiteral = 0 + std::atoi(cstr);
            bool foundFirst = false;
            bool foundSecond = false;
            int firstPosition = 0;
            int secondPosition = 0;
            while(str[i] != ' '){
                i++;
            }
            int secondtLiteral = 0 + std::atoi(&cstr[i+1]);
            
            
            if(firstLiteral < 0){
                for(int j = 0; j < mappingNegativeLiterals.size() && !foundFirst; j++ ){
                    if(firstLiteral == mappingNegativeLiterals[j]){
                        foundFirst = true;
                        firstPosition = j;
                    } 
                }
            } else {
                for(int j = 0; j < mappingPositiveLiterals.size() && !foundFirst; j++ ){
                    if(firstLiteral == mappingPositiveLiterals[j]){
                        foundFirst = true;
                        firstPosition = j;
                    } 
                }
            }
            
            if(secondLiteral < 0){
                for(int j = 0; j < mappingNegativeLiterals.size() && !foundSecond; j++ ){
                    if(secondLiteral == mappingNegativeLiterals[j]){
                        foundSecond = true;
                        secondPosition = j;
                    } 
                }
            } else {
                for(int j = 0; j < mappingPositiveLiterals.size() && !foundSecond; j++ ){
                    if(secondLiteral == mappingPositiveLiterals[j]){
                        foundSecond = true;
                        secondPosition = j;
                    }  
                }
            }
            
            //falls erster Knoten noch nicht vorhanden
            if(!foundFirst){
                if(firstLiteral < 0){
                    mappingNegativeLiterals.push_back(firstLiteral);
                    mappingPositiveLiterals.push_back(-firstLiteral);
                    NegativeLiterals.push_back(graph.addNode());
                    PositiveLiterals.push_back(graph.addNode());
                } else{
                    mappingNegativeLiterals.push_back(-firstLiteral);
                    mappingPositiveLiterals.push_back(firstLiteral);
                    NegativeLiterals.push_back(graph.addNode());
                    PositiveLiterals.push_back(graph.addNode());
                }
            }
            
            //falls zweiter Knoten noch nicht vorhanden
            if(!foundSecond){
                if(secondLiteral < 0){
                    mappingNegativeLiterals.push_back(secondLiteral);
                    mappingPositiveLiterals.push_back(-secondLiteral);
                    NegativeLiterals.push_back(graph.addNode());
                    PositiveLiterals.push_back(graph.addNode());
                } else{
                    mappingNegativeLiterals.push_back(-secondLiteral);
                    mappingPositiveLiterals.push_back(secondLiteral);
                    NegativeLiterals.push_back(graph.addNode());
                    PositiveLiterals.push_back(graph.addNode());
                }
            }
            
            //Hier werden die Kanten hinzugefugt
            if(firstLiteral < 0){
                if(secondLiteral < 0){
                    graph.addEdge(PositiveLiterals[firstPosition], NegativeLiterals[secondPosition]);
                    graph.addEdge(PositiveLiterals[secondPosition], NegativeLiterals[firstPosition]);
                }else{
                    graph.addEdge(PositiveLiterals[firstPosition], PositiveLiterals[secondPosition]);
                    graph.addEdge(NegativeLiterals[secondPosition], NegativeLiterals[firstPosition]);
                }
            }else{
                if(secondLiteral < 0){
                    graph.addEdge(NegativeLiterals[firstPosition], NegativeLiterals[secondPosition]);
                    graph.addEdge(PositiveLiterals[secondPosition], PositiveLiterals[firstPosition]);
                }else{
                    graph.addEdge(NegativeLiterals[firstPosition], PositiveLiterals[secondPosition]);
                    graph.addEdge(NegativeLiterals[secondPosition], PositiveLiterals[firstPosition]);
                }
            }
            
            
        }while(!std::cin.eof());
        
        /*
         * checken ob Knoten und negieter Knoten in selber Koponenten liegen
         */
        NetworKit::StronglyConnectedComponents components{graph};
        components.run();
        for(int j = 0; j < mappingNegativeLiterals.size(); j++){
            if(components.componentOfNode(PositiveLiterals[j]) == components.componentOfNode(NegativeLiterals[j])){
                sat = false;
            }
        }
        
        if(sat)
            std::cout << "SAT" << std::endl;
        else
            std::cout << "UNSAT" << std::endl;
        return 0;
}