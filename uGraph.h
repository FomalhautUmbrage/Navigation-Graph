#pragma once
#include "Node.h"
#define ONCE_TIME_CREATE 100
class uGraph
{
private:
	Node** graph;
	string* nodeNames;
	int nodeCount;
	int size;
private:
	void freeGraph(int si);
	int getNodeNameIndex(string name);
	string getIndexOfName(int index);
	bool havePassed(string* paths, int len, string name);
	int findWay(string from, string to, string* paths, int node);
	bool findSmall(string from, string to, double& small, double now, string* paths, int node);
	double Dijkstra(int s, int kk);
public:
	uGraph();
	~uGraph();	
	void addNode(string name);
	bool insertEdge(string from, string to, double d, double s);
	bool print(string name);
	bool delet(string name);
	bool path(string from, string to);	
	bool traffic(string from, string to, double a);
	bool lowest(string from, string to);
};

