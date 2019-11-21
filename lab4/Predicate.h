#ifndef PREDICATE_H
#define PREDICATE_H
using namespace std;

#include <string>
#include <vector>

#include "Parameter.h"
#include "Tuple.h"

class Predicate
{
public:

    Predicate();
    Predicate(string name_in);

    void addParameter(Parameter new_parameter);

    string toString(char terminator=0);

    string name;

    vector<Parameter> parameter_list;

    Tuple getParameters();

};

#endif