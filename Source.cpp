#include<fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <ctime> 
using namespace std;

/// <summary>
/// making a class of vector for the vertex of the graph
/// </summary>
class vertex
{
public:
	vector<int> neighs;
	int vertex_num;
	int dist = -1;
	string color = "white";
};


/// <summary>
/// declaring the functions
/// </summary>
/// <param name=""><>
/// <param name=""><>
/// <returns><>
vector<vertex*> build_random_graph(int, double);
int Is_Isolated(vector<vertex*>);
int connectivity(vector<vertex*>);
void BFS(vector<vertex*>, int);
int diameter(vector<vertex*>);
void freeGraph(vector<vertex*>);
void Attribute1();
void Attribute2();
void Attribute3();

void main()
{
	srand(time(NULL));
	//Attribute1();
	Attribute2();
	//Attribute3();
}


/// <summary>
/// building the graph
/// </summary>
/// <param name="v"><vertex>
/// <param name="p"><probability we recieved>
/// <returns><a graph>
vector<vertex*> build_random_graph(int v,double p)
{
	vector<vertex*> graph;
	for (int i = 0; i < v; i++)
	{
		graph.push_back(new vertex());
		graph[i]->vertex_num = i;
	}
	for (int i = 0; i < v; i++)
	{
		for (int j = 0; j < i; j++)
		{
			double random_value = (double)rand() / RAND_MAX;
			if (random_value <= p && i != j)
			{
				graph[i]->neighs.push_back(j);
				graph[j]->neighs.push_back(i);
			}
		}
	}
	return graph;
}


/// <summary>
/// checking if there is an isolated vertex in the graph
/// </summary>
/// <param name="graph"><>
/// <returns><1 if there is an isolated vertex, 0 if there isn't >
int Is_Isolated(vector<vertex*> graph)
{
	for (int i = 0; i < graph.size(); i++)
	{
		if (graph[i]->neighs.size() == 0)
			return 1;
	}
	return 0;
}


/// <summary>
/// checking the connectivity of the graph- using the isolated function also
/// </summary>
/// <param name="graph"><>
/// <returns><0 if there is a white vertex after using BFS, 1 if there is no white vertex>
int connectivity(vector<vertex*> graph)
{
	if (Is_Isolated(graph))
		return 0;
	BFS(graph, 0);
	for (int i = 0; i < graph.size(); i++)
	{
		if (graph[i]->color == "white")
			return 0;
	}
	return 1;
}


/// <summary>
/// BFS
/// </summary>
/// <param name="graph"><>
/// <param name="s"><the root vertex>
void BFS(vector<vertex*> graph,int s)
{
	int current_vertex;
	for (int i = 0; i < graph.size(); i++)
	{
		graph[i]->color = "white";
		graph[i]->dist = -1;
	}
	graph[s]->color = "red";
	graph[s]->dist = 0;
	queue<int> q;
	q.push(graph[s]->vertex_num);
	while (!q.empty())
	{
		current_vertex = q.front();
		for (int i = 0; i < graph[current_vertex]->neighs.size(); i++)
		{
			if (graph[graph[current_vertex]->neighs[i]]->color == "white")
			{
				graph[graph[current_vertex]->neighs[i]]->color = "red";
				graph[graph[current_vertex]->neighs[i]]->dist = graph[current_vertex]->dist+1;
				q.push(graph[graph[current_vertex]->neighs[i]]->vertex_num);
			}
		}
		q.pop();
		graph[current_vertex]->color = "black";
	}
}


/// <summary>
/// finding the diameter by BFS and comparing distances
/// </summary>
/// <param name="graph"><>
/// <returns><the diameter>
int diameter(vector<vertex*> graph)
{
	if (!connectivity(graph))
		return -1;
	int current_max = 0;
	for (int current_vertex = 0; current_vertex < graph.size(); current_vertex++)
	{
		for (int j = 0; j < graph.size(); j++)
		{
			BFS(graph, current_vertex);
			if (current_max < graph[j]->dist)
				current_max = graph[j]->dist;
		}
	}
	return current_max;
}


/// <summary>
/// delete memory objects
/// </summary>
/// <param name="graph"><graph>
void free_func(vector<vertex*> graph)
{
	for (int i = 0; i < graph.size(); i++)
	{
		delete graph[i];
	}
	graph.clear();
	graph.shrink_to_fit();
}


/// <summary>
/// making a file
/// </summary>
void Attribute1()
{
	double threshold1[] = { 0.002,0.003,0.004,0.005,0.006,0.5,0.6,0.7,0.8,0.999 };
	ofstream filename;
	filename.open("Attribute1.csv");
	filename << "P" << endl;
	for (int i = 0; i < 10; i++)
	{
		filename << threshold1[i];
		for (int j = 0; j < 500; j++)
		{
			vector<vertex*> graph = build_random_graph(1000, threshold1[i]);

			if (connectivity(graph))
				filename << "," << 1;
			else
				filename << "," << 0;

			free_func(graph);
		}
		filename << endl;
	}
	filename.close();
}


void Attribute2()
{
	double threshold2[] = { 0.01,0.03,0.06,0.09,0.01,0.3,0.4,0.5,0.6,0.7 };
	ofstream filename;
	filename.open("Attribute2.csv");
	filename << "P" << endl;
	for (int i = 0; i < 10; i++)
	{
		filename << threshold2[i];
		for (int j = 0; j < 500; j++)
		{
			vector<vertex*> graph = build_random_graph(1000, threshold2[i]);

			if (connectivity(graph))
			{
				int diam = diameter(graph);
				filename << "," << diam;
			}
			else
				filename << ",INFINITY";
				
			free_func(graph);
		}
		filename << endl;
	}
	filename.close();
}


void Attribute3()
{
	double threshold3[] = { 0.002,0.003,0.004,0.005,0.006,0.1,0.2,0.3,0.5,0.9 };
	ofstream filename;
	filename.open("Attribute3.csv");
	filename << "P" << endl;
	for (int i = 0; i < 10; i++)
	{
		filename << threshold3[i];
		for (int j = 0; j < 500; j++)
		{
			vector<vertex*> graph = build_random_graph(1000, threshold3[i]);

			if (Is_Isolated(graph))
				filename << "," << 1;
			else
				filename << "," << 0;
				
			free_func(graph);
		}
		filename << endl;
	}
	filename.close();
}