#include <iostream>
#include <climits>
#include "tsp.h"
//#include "twoOpt.h"

int main(int argc, char** argv) {
	if(argc < 2){
		exit(-1);
	}

	// Read file names from input
	string input, output;
	input = output = argv[1];
	output.append(".tour");

	// Create new tsp object
	TSP tsp(input, output);
	long long int tsp_size = tsp.get_size();

	// Fill N x N matrix with distances between nodes
	tsp.fillMatrix();

	// Find a MST T in graph G
	tsp.findMST();

	// Find a minimum weighted matching M for odd vertices in T
	tsp.perfectMatching();
	// Loop through each index and find shortest path
	long long int best = INT_MAX;
	long long int bestIndex;
	for (long t = 0; t < tsp_size; t++) {
		long long int result = tsp.findBestPath(t);

		tsp.path_vals[t][0] = t; // set start
		tsp.path_vals[t][1] = result; // set end

		if (tsp.path_vals[t][1] < best) {
			bestIndex = tsp.path_vals[t][0];
			best = tsp.path_vals[t][1];
		}
	}

	//Create path for best tour
	tsp.euler_tour(bestIndex,tsp.circuit);
	tsp.make_hamiltonian(tsp.circuit,tsp.pathLength);

	/*
	tsp.euler_tour(0, tsp.circuit);
	cout << "euler completed" << endl;
	tsp.make_hamiltonian(tsp.circuit, tsp.pathLength);
	cout << "ham completed" << endl;
	*/

	// Store best path
	//tsp.create_tour(bestIndex);

	cout << "Final length: " << tsp.pathLength << endl;

	// Print to file
	tsp.printPath();
	tsp.printResult();
}
