#include<stdio.h> 
#include<string.h> 
#include<iostream>
#include<fstream>
#include<sstream>
#include <string>
#include <vector> 
#include <limits.h> 

using namespace std;

int verticesCount;

vector<vector<int>> GenerateInfintyVectorMatrix(int size);

///struct of graph
///includes adjecnymatrix and vertices
///has function as addEdge to the matrix
class Graph {
public:
	vector<vector<int>> adjencyMatrix;
	int Vertices;

	Graph(int Vertices) {
		this->Vertices = Vertices;
		adjencyMatrix = GenerateInfintyVectorMatrix(Vertices);
	}

	void addEdge(int sourceNode, int targetNode, int cost) {
		adjencyMatrix[sourceNode][targetNode] = cost;
	}
};

class SourceAndDestination {
public:
	int jh = 0;
	int jd = 0;
	int lh = 0;
	int ld = 0;
};

///method definitions
vector<vector<int>> ReadFile(string fileName);
void VectorMatrixPrinter(vector<vector<int>> matrix);
int MinDistance(vector<int>dist, vector<bool> sptSet);
Graph FillGraph(vector<vector<int>> matrix);

//fills the graph with input values
//Creates vertices and fills their edges weights
Graph FillGraph(vector<vector<int>> matrix) {
	verticesCount = matrix[0][0];
	Graph graph(verticesCount);

	for (int i = 2; i < matrix.size(); i++)
	{
		if (matrix[i].size() == 3) {
			graph.addEdge(matrix[i][0], matrix[i][1], matrix[i][2]);
		}
	}
	return graph;
}

//Function findes shortest path from source
int MinDistance(vector<int>dist, vector<bool> sptSet){
	// Initialize min value 
	int min = INT_MAX;
	int min_index = 0;

	for (int v = 0; v < verticesCount; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

//Function finds shortest path using Dijkstra Algorithm
int Dijkstra(Graph graph, int src, int destination){
	vector<int> dist (graph.Vertices);

	vector<bool> sptSet(graph.Vertices);

	// Initialize all distances as INFINITE and stpSet[] as false 
	for (int i = 0; i < graph.Vertices; i++)
		dist[i] = INT_MAX, sptSet[i] = false;
	dist[src] = 0;
	// Find shortest path for all vertices 
	for (int count = 0; count < graph.Vertices - 1; count++) {
		int u = MinDistance(dist, sptSet);

		sptSet[u] = true;

		for (int v = 0; v < graph.Vertices; v++)
			// Update dist[v]
			if (!sptSet[v] && graph.adjencyMatrix[u][v] != INT_MAX && dist[u] != INT_MAX
				&& dist[u] + graph.adjencyMatrix[u][v] < dist[v])
				dist[v] = dist[u] + graph.adjencyMatrix[u][v];
	}
	//prints the result of shortest path
	int distance = dist[destination];
	return distance;
}

///read source and destination vertices from the matrix
SourceAndDestination GetSourceAndDestination(vector<vector<int>> matrix, SourceAndDestination srcAndDest) {
	srcAndDest.jh = matrix[1][0];
	srcAndDest.jd = matrix[1][1];
	srcAndDest.lh = matrix[1][2];
	srcAndDest.ld = matrix[1][3];

	return srcAndDest;
}

int main() {
	
	//reading files with ReadFile method
	vector<vector<int>> matrix =  ReadFile("test5.txt");
	//fill the graph with matrix(output of ReadFile)
	Graph graph = FillGraph(matrix);
	//get source and destination vertices from matrixs
	SourceAndDestination srcAndDest;
	srcAndDest = GetSourceAndDestination(matrix, srcAndDest);
	int shortestPath;

	shortestPath = Dijkstra(graph, srcAndDest.jh, srcAndDest.jd);
	
	cout << "Shortest path time JH to JD   ";
	cout << shortestPath;
	cout << "\n";
	
	shortestPath = Dijkstra(graph, srcAndDest.jd, srcAndDest.jh);
	cout << "Shortest path time JD to JH   ";
	cout << shortestPath;
	cout << "\n";

	shortestPath = Dijkstra(graph, srcAndDest.lh, srcAndDest.ld);
	cout << "Shortest path time LH to LD   ";
	cout << shortestPath;
	cout << "\n";

	shortestPath = Dijkstra(graph, srcAndDest.ld, srcAndDest.lh);
	cout << "Shortest path time LD to LH   ";
	cout << shortestPath;
	cout << "\n";

}

//reads file as input like "test1.txt"
//returns 2D vector matrix
vector<vector<int>> ReadFile(string fileName) {
	vector<vector<int>> matrix;
	string line;

	ifstream myReadFile;
	myReadFile.open(fileName);
	int a;
	int lineCount = 0;
	if (myReadFile.is_open()) {
		while (myReadFile.good()) {
			getline(myReadFile, line);
			vector<int> vector;
			for (int i = 0; i < line.length(); i++) {
				if (line[i] != 32 && (line[i + 1] == 32 || line[i + 1] == NULL)) {
					if (i == 0 || (i > 0 && line[i - 1] == 32)) {
						int a = int(line[i]) - 48;
						vector.push_back(a);
					}
				}
				else if (line[i] != 32 && line[i + 1] != 32 && line[i + 1] != NULL) {
					int a = 10 * (int(line[i]) - 48) + int(line[i + 1] - 48);
					vector.push_back(a);
				}
			}
			matrix.push_back(vector);
			lineCount++;
		}
	}
	return matrix;
}

//used for visualising the input in debug mode
//not called
void VectorMatrixPrinter(vector<vector<int>> matrix) {
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			cout << matrix[i][j];
			cout << " ";
		}
		cout << "\n";
	}
}

//Generates n * n infinty vector matrix
vector<vector<int>> GenerateInfintyVectorMatrix(int size) {
	vector<vector<int>> InfinityMatrix;
	for (int i = 0; i < size; i++)
	{
		vector<int> line;
		for (int j = 0; j < size; j++)
		{
			line.push_back(INT_MAX);
		}
		InfinityMatrix.push_back(line);
	}
	return InfinityMatrix;
}
