#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class Node
{
private:
	double distance;
	double speed;
	double adjustment;
public:
	Node(double d = 0.0, double s = 0.0, double a = 1.0);
	void setDistance(double);
	void setSpeed(double);
	void setAdjustment(double);
	double getDistance();
	double getSpeed();
	double getAdjustment();
	double calT();
	Node& operator=(const Node& other);
	bool operator < ( Node& rhs);
};

