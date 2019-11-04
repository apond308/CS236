#include "Rule.h"

Rule::Rule(Predicate predicate_in)
{
    this->head_predicate = predicate_in;
}

void Rule::addPredicate(Predicate new_predicate)
{
    predicate_list.push_back(new_predicate);
}

string Rule::toString()
{
    string output = "";
    output += head_predicate.toString();
    output += " :- ";
    for (int x=0;x<predicate_list.size()-1;x++)
    {
        output += predicate_list[x].toString();
        output += ",";
    }
    output += predicate_list[predicate_list.size()-1].toString();
    output += ".";
    return output;
}