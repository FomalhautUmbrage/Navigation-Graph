#pragma once

const int INF = 0x3f3f3f3f;
const int maxn = 15000;
class HeapNode
{
public:
    double d;
    int u;
    HeapNode(double D = 0.0, int U = 0.0) :d(D), u(U) {}
    bool operator < (const HeapNode& rhs) const {
        return d > rhs.d;
    }
};

class Edge
{
public:
    int from, to;
    double dist;
    Edge(int u = 0, int v = 0, double d = 0.0) :from(u), to(v), dist(d) {}
};