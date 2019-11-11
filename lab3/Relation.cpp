#include "Relation.h"
#include <iostream>

Relation::Relation(string name_in, Scheme scheme_in)
{
    this->name = name_in;
    this->scheme = scheme_in;
}

void Relation::addTuple(Tuple to_add)
{
    tuple_list.insert(to_add);
}

string Relation::toString()
{
    string temp_string = "";
    for(set<Tuple>::iterator iter = tuple_list.begin(); iter != tuple_list.end(); iter++){
        if (scheme.size()) {temp_string += "\n  ";}
        for (int x=0;x<this->scheme.size();x++){    
            temp_string += this->scheme[x] + "=" + (*iter)[x] + ", ";
        }
        temp_string = temp_string.substr(0, temp_string.size()-2);
    }
    return temp_string;
}