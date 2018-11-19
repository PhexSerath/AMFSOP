//Steven Müller (581583)
//Lucas Petersen (581277)

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
bool **tabelle;
int maxWert[1001];

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
		wert = line.substr(k + 1);
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

void solution(){
	for (int i = 0; i < count; i++)
	{
		for (int j = 1000; j >= eleArray[i]->gewicht;	j--)
		{
			if ((maxWert[j - eleArray[i]->gewicht] + eleArray[i]->wert) > maxWert[j]) {
				maxWert[j] = maxWert[j - eleArray[i]->gewicht] + eleArray[i]->wert;
				tabelle[i][j] = true;
			}
		}
	}
}

int main(int argc, const char *argv[]) {
	einlesen();
	tabelle = new bool*[count];
	for (int i = 0; i < count; i++)
	{
		tabelle[i] = new bool[1001];
		maxWert[i] = 0;
		for (int j = 0; j <= 1000; j++)
		{
			tabelle[i][j] = false;
		}
	}
	solution();
	std::cout << maxWert[1000] << std::endl;
}