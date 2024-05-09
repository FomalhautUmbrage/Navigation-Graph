#pragma once
#include <exception>
#include <string>
#include <iostream>
using namespace std;

class illegal_exception :
    public exception
{
public:
    illegal_exception(string msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }

private:
    string message;
};

