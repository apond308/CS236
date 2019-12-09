#include "Relation.h"
#include <iostream>
#include <map>
#include <algorithm>

Relation::Relation(string name_in, Scheme scheme_in)
{
    this->name = name_in;
    this->scheme = scheme_in;
}

bool Relation::addTuple(Tuple to_add)
{
    return tuple_list.insert(to_add).second;
}

Relation Relation::join(Relation relation_in)
{
    Relation joined_relation = Relation(this->name, scheme);

    vector<pair<int, int>> duplicates;
    // Join schemes
    for (int x=0;x<relation_in.scheme.size();x++)
    {
        if (std::find(scheme.begin(), scheme.end(), relation_in.scheme[x]) == scheme.end())
        {
            joined_relation.scheme.push_back(relation_in.scheme[x]);
        }
        else
        {
            int index = std::find(scheme.begin(), scheme.end(), relation_in.scheme[x]) - scheme.begin();
            duplicates.push_back(pair<int, int>(index, x));
        }
    }
    

    // Find tuples to join
    auto a_tuple = tuple_list.begin();
    while(a_tuple != tuple_list.end())
    {
        auto b_tuple = relation_in.tuple_list.begin();
        while(b_tuple != relation_in.tuple_list.end())
        {
            bool valid_join = true;
            for (auto scheme_pair : duplicates)
            {
                if (a_tuple->at(scheme_pair.first) != b_tuple->at(scheme_pair.second))
                {
                    valid_join = false;
                    break;
                }
            }
            if (valid_join)
            {
                Tuple new_tuple = Tuple();
                // Join tuples
                for (int x=0;x<a_tuple->size();x++)
                {
                    new_tuple.push_back(a_tuple->at(x));
                }
                for (int x=0;x<b_tuple->size();x++)
                {
                    bool found = false;
                    for (auto val : duplicates)
                    {
                        if (val.second == x)
                        {
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                        new_tuple.push_back(b_tuple->at(x));
                }
                joined_relation.addTuple(new_tuple);
                
            }
            b_tuple++;
        }
        a_tuple++;
    }


    return joined_relation;
}

pair<Relation, Relation> Relation::unite(Relation relation_in)
{
    Relation united_relation = Relation(this->name, this->scheme);
    Relation to_print = Relation(this->name, this->scheme);

    for (auto tuple : this->tuple_list)
        united_relation.addTuple(tuple);

	for (auto tuple : relation_in.tuple_list)
    {
		bool new_element = united_relation.addTuple(tuple);
        if (new_element)
            to_print.addTuple(tuple);
    }
		
    return pair<Relation, Relation>(united_relation, to_print);

}

string Relation::toString()
{
    string temp_string = "";
    for(set<Tuple>::iterator iter = tuple_list.begin(); iter != tuple_list.end(); iter++){
        if (scheme.size()) {temp_string += "  ";}
        for (long unsigned int x=0;x<this->scheme.size();x++){    
            temp_string += this->scheme[x] + "=" + (*iter)[x] + ", ";
        }
        temp_string = temp_string.substr(0, temp_string.size()-2);
        if (scheme.size()) {temp_string += "\n";}
    }
    return temp_string;
}
