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

int main(int argc, const char *argv[]) {
	NetworKit::SNAPGraphReader reader{ false, false };
	auto g = reader.read(argv[1]); // Yields NetworKit::Graph object.
	auto col = init(g.numberOfNodes());



}