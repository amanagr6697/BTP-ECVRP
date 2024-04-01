#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <stdio.h>
#include <vector>
#include <limits>

using namespace std;

#ifndef TSP_H
#define TSP_H

class TSP
{
private:

	struct City{
		long long int x;
		long long int y;
	};

	string iFile;
	string oFile;

	// List of odd nodes
	vector<long long int>odds;

	//Smaller cost matrix to find minimum matching on odd nodes
	long long int **cost;

	//Adjacency list
	vector<long long int> *adjList;

	void findOdds();



protected:


public:
	// Number of cities
	long long int n;

	//path
	long long int **path_vals;

	//Shortest path length
	long long int pathLength;

	//euler circuit
	vector<long long int> circuit;

	vector<City> cities;

	// n x n, pairwise distances between cities
	long long int **graph;

  vector<long long int>* adjlist;

	// Constructor
	TSP(string in, string out);

	// Destructor
	~TSP();

	long long int get_distance(struct City c1, struct City c2);

	//Find perfect matching
	void perfectMatching();

	//Find Euler tour
	void euler_tour(long long int start, vector<long long int> &path);

	//Find Hamiltonian path
	void make_hamiltonian(vector<long long int> &path, long long int &pathCost);

	// Prim's algorithm
	void findMST();

	long long int getMinIndex(long long int key[], bool mst[]);

	void printResult();
	void printPath();
	void printEuler();
	void printAdjList();
	void printCities();

	long long int get_size(){return n;};

	void fillMatrix();

	long long int findBestPath(long long int start);

};

#endif
