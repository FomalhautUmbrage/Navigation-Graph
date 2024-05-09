#include "uGraph.h"
#include "PriorityQueue.h"
#include "Vector.h"
#include "HeapNode.h"
#include <cstring>

uGraph::uGraph()
{
    graph = nullptr;
    nodeNames = nullptr;
    nodeCount = 0;
    size = 0;
}

uGraph::~uGraph()
{
    freeGraph(size);
}

void uGraph::freeGraph(int si)
{
    if (graph != nullptr) {
        for (int i = 0; i < si; i++) {
            delete[] graph[i];
        }
        delete[] graph;
        graph = nullptr;
    }
    if (nodeNames != nullptr) {
        delete[] nodeNames;
        nodeNames = nullptr;
    }
}

int uGraph::getNodeNameIndex(string name)
{
    for (int i = 0; i < nodeCount; i++) {
        if (nodeNames[i] == name)
            return i;
    }
    return -1;
}

string uGraph::getIndexOfName(int index)
{
    if (index<0 || index>=nodeCount) {
        return string();
    }
    return nodeNames[index];
}

void uGraph::addNode(string name)
{
    if (nodeNames == nullptr) {
        size = ONCE_TIME_CREATE;
        nodeNames = new string[size];
        graph = new Node * [size];
        for (int i = 0; i < size; i++) {
            graph[i] = new Node[size];
        }
    }
    else if (size <= nodeCount) {
        size += ONCE_TIME_CREATE;
        string* tmps = new string[size];
        for (int i = 0; i < nodeCount; i++) {
            tmps[i] = nodeNames[i];
        }
        Node **tmpg = new Node * [size];
        for (int i = 0; i < size; i++) {
            tmpg[i] = new Node[size];
        }
        for (int i = 0; i < nodeCount; i++) {
            for (int j = 0; j < nodeCount; j++) {
                tmpg[i][j] = graph[i][j];
            }
        }
        freeGraph(size - ONCE_TIME_CREATE);
        nodeNames = tmps;
        graph = tmpg;
    }
    nodeNames[nodeCount++] = name;
}

bool uGraph::insertEdge(string from, string to, double d, double s)
{
    int indexf = getNodeNameIndex(from), indext = getNodeNameIndex(to);
    if (indexf == -1) {
        addNode(from);
        indexf = getNodeNameIndex(from);
    }
    if (indext == -1) {
        addNode(to);
        indext = getNodeNameIndex(to);
    }
    Node node(d, s);
    graph[indexf][indext] = node;
    graph[indext][indexf] = node;
    return true;
}

bool uGraph::print(string name)
{
    int index = getNodeNameIndex(name);
    bool hfind = false;
    if (index == -1) {
        return false;
    }
    for (int i = 0; i < nodeCount; i++) {
        if (i != index && graph[index][i].getDistance() != 0.0) {
            if (hfind) {
                cout << " ";
            }
            cout << nodeNames[i];
            hfind = true;
        }
    }
    return true;
}

bool uGraph::delet(string name)
{
    int index = getNodeNameIndex(name);
    if (index == -1) {
        return false;
    }
    for (int i = index; i < nodeCount - 1; i++) {
        for (int j = 0; j < nodeCount; j++) {
            graph[i][j] = graph[i + 1][j];
            graph[j][i] = graph[j][i + 1];
        }
        nodeNames[i] = nodeNames[i + 1];
    }
    nodeCount -= 1;
    return true;
}

bool uGraph::path(string from, string to)
{
    int indexf = getNodeNameIndex(from), indext = getNodeNameIndex(to);
    if (indexf == -1) {
        return false;
    }
    if (indext == -1) {
        return false;
    }
    string* paths = new string[size * size];
    int len = findWay(from, to, paths, 0);
    if (len == 0) {
        delete[] paths;
        return false;
    }
       
    for (int i = 0; i < len; i++) {
        cout << paths[i];
        if (i != len - 1) {
            cout << " ";
        }
    }
    delete[] paths;
    return true;
}

bool uGraph::havePassed(string* paths, int len, string name)
{
    for (int i = 0; i < len; i++) {
        if (paths[i] == name) {
            return true;
        }
    }
    return false;
}

int uGraph::findWay(string from, string to, string* paths, int node)
{
    int len = 0;
    int indexf = getNodeNameIndex(from), indext = getNodeNameIndex(to);
    if (from == to) {
        paths[node++] = to;
        return node;
    }
    for (int i = 0; i < nodeCount; i++) {
        if (i != indexf && graph[indexf][i].getDistance() != 0.0 && graph[indexf][i].getAdjustment() != 0.0 && !havePassed(paths, node, getIndexOfName(i))) {
            paths[node] = from;
            len = findWay(getIndexOfName(i), to, paths, node + 1);
            if (len != 0) {
                break;
            }
        }
    }
    return len;
}

bool uGraph::findSmall(string from, string to, double& small, double now, string* paths, int node)
{
    bool f = false;
    int indexf = getNodeNameIndex(from), indext = getNodeNameIndex(to);
    if (from == to) {
        if (small == -1.0 || small > now) {
            small = now;
        }
        return true;
    }
    for (int i = 0; i < nodeCount; i++) {
        if (i != indexf && graph[indexf][i].getDistance() != 0.0 && !havePassed(paths, node, getIndexOfName(i)) &&
            graph[indexf][i].getAdjustment() != 0.0) {
            paths[node] = from;
            f |= findSmall(getIndexOfName(i), to, small, now + graph[indexf][i].calT(), paths, node + 1);
        }
    }
    return f;
}

double uGraph::Dijkstra(int s, int kk)
{
    int n, m;
    n = nodeCount;
    Vector<Edge> edges;
    Vector<int> G[maxn];    //maxn要大于顶点数
    bool* done = new bool[maxn]();
    double* d = new double[maxn]();
    int* p = new int[maxn]();
    bool fi = false;
    double val = -1.0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j && graph[i][j].getDistance() != 0.0 && graph[i][j].getAdjustment() != 0.0) {
                edges.push_back(Edge(i, j, graph[i][j].calT()));
                m = edges.size();
                G[i].push_back(m - 1);
            }            
        }
    }

    PriorityQueue<HeapNode> Q;
    for (int i = 0; i < n; ++i)
        d[i] = INF;
    d[s] = 0;
    memset(done, 0, sizeof(done));
    Q.push(HeapNode(0.0, s));
    while (!Q.empty())
    {
        HeapNode x = Q.top();
        Q.pop();        
        int u = x.u;
        if (u == kk)                  //到终点就退出
        {
            val = x.d;
            fi = true;
            break;
        }
        if (done[u])
        {
            continue;
        }
        done[u] = true;
        for (int i = 0; i < G[u].size(); ++i)
        {
            Edge& e = edges[G[u][i]];
            if (d[u] + e.dist < d[e.to])
            {
                d[e.to] = d[u] + e.dist;
                p[e.to] = G[u][i];
                Q.push(HeapNode(d[e.to], e.to));
            }
        }
    }

    delete[] done;
    delete[] d;
    delete[] p;
    return val;
}


bool uGraph::traffic(string from, string to, double a)
{
    int indexf = getNodeNameIndex(from), indext = getNodeNameIndex(to);
    if (indexf == -1) {
        return false;
    }
    if (indext == -1) {
        return false;
    }
    graph[indexf][indext].setAdjustment(a);
    graph[indext][indexf].setAdjustment(a);
    return true;
}

bool uGraph::lowest(string from, string to)
{
    int indexf = getNodeNameIndex(from), indext = getNodeNameIndex(to);
    if (indexf == -1) {
        return false;
    }
    if (indext == -1) {
        return false;
    }
    /*string* paths = new string[size * size];
    double dis = -1.0;
    bool hf = findSmall(from, to, dis, 0.0, paths, 0);
    if (!hf) {
        delete[] paths;
        return false;
    }
    cout << "lowest is " << dis;
    delete[] paths;*/
    double dis = Dijkstra(indexf, indext);
    if (dis == -1.0) {
        return false;
    }
    cout << "lowest is " << dis;
    return true;
}
