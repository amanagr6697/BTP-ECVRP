#include "tsp.h"


//Constructor
TSP::TSP(string in, string out){
	iFile = in;
	oFile = out;

	ifstream inStream;
	inStream.open(iFile.c_str(), ios::in);

	if(!inStream){
		cerr << "Can't open input file " << iFile << endl;
		exit(1);
	}
	
	//READ DATA
	long long int c, x, y;
	long long int count = 0;
	while(!inStream.eof()){
		inStream >> c >> x >> y;
		count++;
		struct City newCity = {x,y};
		cities.push_back(newCity);
	}
	count--;
	cout << "cities created" << endl;
	inStream.close();

	//Initialize member variables
	n = count;
	graph = new long long int*[n];
	for(long long int i = 0; i < n; i++){
		graph[i] = new long long int[n];
		for(long long int j = 0; j < n; j++){
			graph[i][j] = 0;
		}
	}

	cost = new long long int*[n];
	for(long long int i = 0; i < n; i++){
		cost[i] = new long long int[n];
	}

	path_vals = new long long int*[n];
	for(long long int i = 0; i < n; i++){
		path_vals[i] = new long long int[n];
	}

	adjlist = new vector<long long int>[n];
	for(long long int i = 0; i < cities.size(); i++){
		struct City cur = cities[i];
	}
}

//Destructor
TSP::~TSP(){
	for(long long int i = 0; i < n; i++){
		delete [] graph[i];
		delete [] cost[i];
		delete [] path_vals[i];
	}
	delete [] path_vals;
	delete [] graph;
	delete [] cost;
	delete [] adjlist;
}

long long int TSP::get_distance(struct TSP::City c1, struct TSP::City c2){
	long long int dx = pow((float)(c1.x - c2.x),2);
	long long int dy = pow((float)(c1.y - c2.y),2);
	return floor((float)(sqrt(dx+dy) + .5));
}

void TSP::fillMatrix(){
	for(long long int i = 0; i < n; i++){
		for(long long int j = 0; j < n; j++){
			graph[i][j] = graph[j][i] = get_distance(cities[i],cities[j]);
		}
	}
}

void TSP::findMST() {

  long long int *key = new long long int[n];
  bool *included = new bool[n];
  long long int *parent = new long long int[n];

  for (long long int i = 0; i < n; i++) {

    // set each key to infinity
    key[i] = std::numeric_limits<long long int>::max();

    // node node yet included in MST
    included[i] = false;

  }

  // root of MST has distance of 0 and no parent
  key[0] = 0;
  parent[0] = -1;

  for (long long int i = 0; i < n - 1; i++) {

    // find closes vertex not already in tree
    long long int k = getMinIndex(key, included);

    // set included to true for this vertex
    included[k] = true;

    // examine each unexamined vertex adjacent to most recently added
    for (long long int j = 0; j < n; j++) {

      // node exists, is unexamined, and graph[k][j] less than previous
      // key for u
      if (graph[k][j] && included[j] == false && graph[k][j] < key[j]) {

          // update parent
          parent[j] = k;

          // update key
          key[j] = graph[k][j];

      }
    }

  }

  // construct a tree by forming adjacency matrices
  for (long long int i = 0; i < n; i++) {

    long long int j = parent[i];

    if (j != -1) {

      adjlist[i].push_back(j);
      adjlist[j].push_back(i);

    }

  }

}

long long int TSP::getMinIndex(long long int key[], bool mst[]) {

  // initialize min and min_index
  long long int min = std::numeric_limits<long long int>::max();
  long long int min_index;

  // iterate through each vertex
  for (long long int i = 0; i < n; i++) {

    // if vertex hasn't been visited and has a smaller key than min
    if (mst[i] == false && key[i] < min) {

      // reassign min and min_index to the values from this node
      min = key[i];
      min_index = i;

    }

  }

  return min_index;

}

void TSP::findOdds() {

  for (long long int i = 0; i < n; i++) {

    // if degree of vertex i is odd
    if ((adjlist[i].size() % 2) != 0) {

      // push vertex to odds, which is a representation of subgraph O
      odds.push_back(i);

    }

  }

}


void TSP::perfectMatching() {
  long long int closest, length; //long long int d;
  std::vector<long long int>::iterator tmp, first;

  // Find nodes with odd degrees in T to get subgraph O
  findOdds();

  // for each odd node
  while (!odds.empty()) {
    first = odds.begin();
    vector<long long int>::iterator it = odds.begin() + 1;
    vector<long long int>::iterator end = odds.end();
    length = std::numeric_limits<long long int>::max();
    for (; it != end; ++it) {
      // if this node is closer than the current closest, update closest and length
      if (graph[*first][*it] < length) {
        length = graph[*first][*it];
        closest = *it;
        tmp = it;
      }
    } // two nodes are matched, end of list reached
    adjlist[*first].push_back(closest);
    adjlist[closest].push_back(*first);
    odds.erase(tmp);
    odds.erase(first);
  }
}


//find an euler circuit
void TSP::euler_tour(long long int start, vector<long long int> &path){
	//Create copy of adj. list
	vector<long long int> *tempList = new vector<long long int>[n];
	for(long long int i = 0; i < n; i++){
		tempList[i].resize(adjlist[i].size());
		tempList[i] = adjlist[i];
	}

	stack<long long int> stack;
	long long int pos = start;
	path.push_back(start);
	while(!stack.empty() || tempList[pos].size() > 0){
		//Current node has no neighbors
		if(tempList[pos].empty()){
			//add to circuit
			path.push_back(pos);
			//remove last vertex from stack and set it to current
			pos = stack.top();
			stack.pop();
		}
		//If current node has neighbors
		else{
			//Add vertex to stack
			stack.push(pos);
			//Take a neighbor
			long long int neighbor = tempList[pos].back();
			//Remove edge between neighbor and current vertex
			tempList[pos].pop_back();
			for(long long int i = 0; i < tempList[neighbor].size(); i++){
				if(tempList[neighbor][i] == pos){
					tempList[neighbor].erase(tempList[neighbor].begin()+i);
				}
			}
			//Set neighbor as current vertex
			pos = neighbor;
		}
	}
	path.push_back(pos);
}


//Make euler tour Hamiltonian
void TSP::make_hamiltonian(vector<long long int> &path, long long int &pathCost){

	//remove visited nodes from Euler tour
	bool *visited = new bool[n];
	for(long long int i = 0; i < n; i++){
		visited[i] = 0;
	}
	
	pathCost = 0;

	long long int root = path.front();
	vector<long long int>::iterator cur = path.begin();
	vector<long long int>::iterator iter = path.begin()+1;
	visited[root] = 1;

	//iterate through circuit
	bool addMore = true;
	while(iter != path.end()){
		if(!visited[*iter]){
			pathCost += graph[*cur][*iter];
			cur = iter;
			visited[*cur] = 1;
			iter = cur + 1;
		}	
		else{
			iter = path.erase(iter);
		}
	}
	//Add distance to root
	if ( iter != path.end() ){
		pathCost += graph[*cur][*iter];
	}
}

long long int TSP::findBestPath(long long int start){
	vector<long long int> path;
	euler_tour(start, path);
	long long int length;

	make_hamiltonian(path, length);
	return length;
}


void TSP::printResult(){
  ofstream outputStream;
  outputStream.open(oFile.c_str(), ios::out);
  outputStream << pathLength << endl;
  for (vector<long long int>::iterator it = circuit.begin(); it != circuit.end(); ++it) {
    outputStream << *it << endl;
  }
  outputStream.close();
};

void TSP::printPath(){
  cout << endl;
  for (vector<long long int>::iterator it = circuit.begin(); it != circuit.end()-1; ++it) {
    cout << *it << " to " << *(it+1) << " ";
    cout << graph[*it][*(it+1)] << endl;
  }
  cout << *(circuit.end()-1) << " to " << circuit.front();
  cout << "\nLength: " << pathLength << endl << endl;
};

void TSP::printEuler() {
  for (vector<long long int>::iterator it = circuit.begin(); it != circuit.end(); ++it)
    cout << *it << endl;
}

void TSP::printAdjList() {
  for (long long int i = 0; i < n; i++) {
    cout << i << ": "; //print which vertex's edge list follows
    for (long long int j = 0; j < (long long int)adjlist[i].size(); j++) {
      cout << adjlist[i][j] << " "; //print each item in edge list
    }
    cout << endl;
  }
};

void TSP::printCities(){
  cout << endl;
  long long int i = 0;
  for (vector<City>::iterator it = cities.begin(); it != cities.end(); ++it)
    cout << i++ << ":  " << it->x << " " << it->y << endl;
}

