#include "Predicate.h"

Predicate::Predicate(){}
Predicate::Predicate(string name_in)
{
    this->name = name_in;
}

void Predicate::addParameter(Parameter new_parameter)
{
    parameter_list.push_back(new_parameter);
}

string Predicate::toString(char terminator)
{
    string output = "";
    output += name + "(";
    for (int x=0;x<parameter_list.size()-1;x++)
    {
        output += parameter_list[x].toString() + ",";
    }
    output += parameter_list[parameter_list.size()-1].toString();
    output += ")";
    if (terminator)
        output += terminator;
    return output;
}

Tuple Predicate::getParameters()
{
    Tuple parameter_strings;
    for (int x=0;x<parameter_list.size();x++)
    {
        parameter_strings.push_back(parameter_list[x].toString());
    }
    return parameter_strings;
}