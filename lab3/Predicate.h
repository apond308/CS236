#ifndef PREDICATE_H
#define PREDICATE_H
using namespace std;

#include <string>
#include <vector>

#include "Parameter.h"

class Predicate
{
public:

    Predicate();
    Predicate(string name_in);

    void addParameter(Parameter new_parameter);

    string toString(char terminator=0);

private:

    string name;

    vector<Parameter> parameter_list;

};

#endif