//Lucas Petersen(581277)
//Steven Müller(581583)


#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>


int main(int argc, const char *argv[]) {
        
        std::string str; 
        std::vector<bool> literals;
        std::vector<bool> clauseFulfillment;
        std::vector<int> mappingLiterals;
        std::vector<std::vector<int>> positive;
        std::vector<std::vector<int>> negative;
        int clauseID = 0;
        srand(time(0));
        
        do{
            std::getline(std::cin, str);
            auto cstr = str.c_str();
            int i = 0;
            int literal = 0;
            clauseFulfillment.push_back(false);
            
            literal = atoi(&cstr[0]); //Erstes literal der Zeile wird eingelesen
            if(literal < 0){
                if(std::find(mappingLiterals.begin(), mappingLiterals.end(), -literal) == mappingLiterals.end()){
                    literals.push_back(false);
                    mappingLiterals.push_back(-literal);
                    positive.push_back(std::vector<int>());
                    negative.push_back(std::vector<int>());
                }
                int position = std::distance(mappingLiterals.begin(), std::find(mappingLiterals.begin(), mappingLiterals.end(), -literal));
                negative[position].push_back(clauseID);
                        
            }else{
                if(std::find(mappingLiterals.begin(), mappingLiterals.end(), literal) == mappingLiterals.end()){
                    literals.push_back(false);
                    mappingLiterals.push_back(literal);
                    positive.push_back(std::vector<int>());
                    negative.push_back(std::vector<int>());
                }
                int position = std::distance(mappingLiterals.begin(), std::find(mappingLiterals.begin(), mappingLiterals.end(), literal));
                positive[position].push_back(clauseID);
            }
            
            
            while(cstr[i] != '\0') { //Zeiten und weiteren Literale der Zeile werden eingelesen
                if(cstr[i] == ' '){
                    literal = atoi(&cstr[i+1]);
                    if(literal < 0){
                        if(std::find(mappingLiterals.begin(), mappingLiterals.end(), -literal) == mappingLiterals.end()){
                            literals.push_back(false);
                            mappingLiterals.push_back(-literal);
                            positive.push_back(std::vector<int>());
                            negative.push_back(std::vector<int>());
                        }
                        int position = std::distance(mappingLiterals.begin(), std::find(mappingLiterals.begin(), mappingLiterals.end(), -literal));
                        negative[position].push_back(clauseID);
                        
                    }else{
                        if(std::find(mappingLiterals.begin(), mappingLiterals.end(), literal) == mappingLiterals.end()){
                            literals.push_back(false);
                            mappingLiterals.push_back(literal);
                            positive.push_back(std::vector<int>());
                            negative.push_back(std::vector<int>());
                        }
                        int position = std::distance(mappingLiterals.begin(), std::find(mappingLiterals.begin(), mappingLiterals.end(), literal));
                        positive[position].push_back(clauseID);
                    }
                    
                }
                do {
                    i++;
                    
                }while(cstr[i] != '\0' && cstr[i] != ' ' && cstr[i] != '\n');
            }
          
            clauseID++;
        }while(!std::cin.eof());
        
        for(int j = 0; j < literals.size();j++){
            literals[j] = rand() % 2;
        }
        
        int maxbuffer = literals.size()/10;
        int maxSat = 0;
        int newMaxSat = 0;
        std::deque<int> taboo;
        int flip = rand()%literals.size();
        int maxN = 0;
        for(int j = 0; j < mappingLiterals.size(); j++){
            if(mappingLiterals[j] > maxN) maxN = mappingLiterals[j];
        }
        
        
        while(true){
            
            for(int j; j < clauseFulfillment.size(); j++){
                clauseFulfillment[j] = false;
            }
            
            newMaxSat = 0;
            
            while((std::find(taboo.begin(), taboo.end(), flip))!= taboo.end()){
                flip = rand()%literals.size();
            }
            
            taboo.push_front(flip);
            if(literals[flip]){
                literals[flip] = false;
            }else{
                literals[flip] = true;
            }
            
            if(taboo.size()>maxbuffer){
                taboo.pop_back();
            }
            
            for(int j = 0; j  < literals.size();j++){
                if(literals[j]){
                    for(int k = 0; k < positive[j].size(); k++){
                        clauseFulfillment[positive[j][k]]= true;
                    }
                }else{
                    for(int k = 0; k < negative[j].size(); k++){
                        clauseFulfillment[negative[j][k]]= true;
                    }
                }
            }
            
            for(int j = 0; j < clauseFulfillment.size();j++){
                if(clauseFulfillment[j]) newMaxSat++;
            }

            if(newMaxSat > maxSat){
                
                maxSat = newMaxSat;
                std::cout << maxSat << std::flush;
                for(int j = 0; j < maxN; j++){
                    if((std::find(mappingLiterals.begin(), mappingLiterals.end(), maxN))!= mappingLiterals.end()){
                        std::cout << " " << literals[std::distance(mappingLiterals.begin(), std::find(mappingLiterals.begin(), mappingLiterals.end(), j))] << std::flush;
                    } else {
                        std::cout << " " << 0 << std::flush;
                    }
                }
                std::cout << std::endl;
                    
            }
            
        }
        
        
}