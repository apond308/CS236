#include "Relation.h"
#include <iostream>
#include <map>
#include <algorithm>

Relation::Relation(string name_in, Scheme scheme_in)
{
    this->name = name_in;
    this->scheme = scheme_in;
}

void Relation::addTuple(Tuple to_add)
{
    tuple_list.insert(to_add);
}

Relation Relation::join(Relation relation_in)
{
    Relation joined_relation = Relation(this->name, scheme);

    map<string, tuple<int, int>> duplicates;
    // Join schemes
    for (int x=0;x<relation_in.scheme.size();x++)
    {
        if (std::find(scheme.begin(), scheme.end(), relation_in.scheme[x]) == scheme.end();)
        {
            joined_relation.scheme.push_back(relation_in.scheme[x]);
        }
        else
        {
            int index = std::find(scheme.begin(), scheme.end(), relation_in.scheme[x]) - scheme.begin();
        }
    }
    

    // Join tuples
    auto a_tuple = tuple_list.begin();
    while(a_tuple != tuple_list.end())
    {
        auto b_tuple = relation_in.tuple_list.begin();
        while(b_tuple != relation_in.tuple_list.end())
        {
            // for (int x=0;x<joined_relation.scheme.size();x++)
            // {




            // }
            b_tuple++;
        }
        a_tuple++;
    }


    return joined_relation;
}

string Relation::toString()
{
    string temp_string = "";
    for(set<Tuple>::iterator iter = tuple_list.begin(); iter != tuple_list.end(); iter++){
        if (scheme.size()) {temp_string += "\n  ";}
        for (long unsigned int x=0;x<this->scheme.size();x++){    
            temp_string += this->scheme[x] + "=" + (*iter)[x] + ", ";
        }
        temp_string = temp_string.substr(0, temp_string.size()-2);
    }
    return temp_string;
}
