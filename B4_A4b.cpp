#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <ios>
#include <iostream>
#include <bitset>

struct Element
{
	int gewicht;
	int wert;
};

int n = 500;
Element** eleArray = new Element*[n];
int count = 0;
bool *tabelle;

void biggerArray() {
	Element** tempArray;
	tempArray = new Element*[n * 2];
	for (int i = 0; i < count; i++) {
		tempArray[i] = eleArray[i];
	}
	delete []eleArray;
	eleArray = tempArray;
	n = n * 2;
}

void einlesen() {
	std::string gewicht;
	std::string wert;
	std::string delimiter = " ";

	for (std::string line; std::getline(std::cin, line);) {
		int k = line.find(delimiter);
		gewicht = line.substr(0, k);
		wert = line.substr(k + 1, line.end);
		Element* neu = new Element;
		neu->gewicht = atoi(gewicht.c_str());
		neu->wert = atoi(wert.c_str());
		eleArray[count] = neu;
		count++;
		if (count > n) {
			biggerArray();
		}
	}
}

int main(int argc, const char *argv[]) {
	einlesen();
	tabelle = new bool[count];
}