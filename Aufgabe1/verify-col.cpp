
#include <cstdlib>
#include <fstream>
#include <vector>

#include <io/SNAPGraphReader.h>

std::vector<int> readColoring(const char *path) {
	std::vector<int> col;
	std::ifstream f{path};
	std::string line;
	
	while(std::getline(f, line)) {
		if(line.empty())
			continue;
		col.push_back(std::stoi(line));
	}
	
	return col;
}

int main(int argc, const char *argv[]) {
	// argc is the number of command line arguments.
	// argv is an array of those arguments.
	if(argc != 3) {
		std::cerr << "Expected exactly the arguments:\n"
				"verify-col <graph> <coloring>" << std::endl;
		return EXIT_FAILURE;
	}

	// Note that we read the graph as undirected and we do not remap node IDs.
	// See the SNAPGraphReader documentation for details.
	NetworKit::SNAPGraphReader reader{false, false};
	auto g = reader.read(argv[1]); // Yields NetworKit::Graph object.
	auto col = readColoring(argv[2]);

	if(col.size() != g.numberOfNodes()) {
		std::cerr << "Error: Mismatch of number of nodes\n"
				<< "Graph has " << g.numberOfNodes()
				<< " nodes, while coloring has " << col.size() << std::endl;
		return EXIT_FAILURE;
	}

	// forEdges() calls a function for each edge of the graph.
	// There is also a forNodes() function that works similarly.
	// Note that [&] makes the lambda "capture" all variables (for example col)
	// from the containing scope (i.e. they become accessible from within the lambda).
	int num_bad_edges = 0;
	g.forEdges([&] (NetworKit::node s, NetworKit::node t) {
		if(col[s] != col[t])
			return;
		std::cerr << "Error: Adjacent nodes " << s << " and " << t
				<< " both have color " << col[s] << std::endl;
		num_bad_edges++;
	});

	if(!num_bad_edges) {
		std::cout << "The coloring is valid" << std::endl;
		return EXIT_SUCCESS;
	}else{
		std::cout << "There " << (num_bad_edges > 1 ? "were " : "was ") << num_bad_edges
				<< " coloring " << (num_bad_edges > 1 ? "violations" : "violation")
				<< std::endl;
		return EXIT_FAILURE;
	}
}

