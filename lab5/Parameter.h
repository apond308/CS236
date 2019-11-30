#ifndef PARAMETER_H
#define PARAMETER_H
using namespace std;

#include <string>

class Parameter
{
public:

    Parameter(string value);

    std::string toString() {return value;}

private:

    string value;
};

#endif