#include "Relation.h"
#include <iostream>

Relation::Relation(string name_in, Scheme scheme_in)
{
    this->name = name_in;
    this->scheme = scheme_in;
}

void Relation::addTouple(Tuple to_add)
{

}

string Relation::toString()
{
    string temp_string = "";
    set<Tuple>::iterator iter = tuple_list.begin();
    while(iter != tuple_list.end())
    {
        for (int x=0;x<this->scheme.size();x++)
        {    
            temp_string += this->scheme[x] + "=" + (*iter)[x] + ",";
            cout << temp_string << endl;
        }
    }
}