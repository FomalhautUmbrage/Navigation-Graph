#include "Node.h"

Node::Node(double d, double s, double a)
{
    distance = d;
    speed = s;
    adjustment = a;
}

void Node::setDistance(double d)
{
    distance = d;
}

void Node::setSpeed(double s)
{
    speed = s;
}

void Node::setAdjustment(double a)
{
    adjustment = a;
}

double Node::getDistance()
{
    return distance;
}

double Node::getSpeed()
{
    return speed;
}

double Node::getAdjustment()
{
    return adjustment;
}

double Node::calT()
{
    return distance / (speed * adjustment);
}

Node& Node::operator=(const Node& other)
{
    distance = other.distance;
    speed = other.speed;
    adjustment = other.adjustment;
    return *this;
}

bool Node::operator<( Node& rhs)
{
    return calT() > rhs.calT();
}
