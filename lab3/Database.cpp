#include "Database.h"
#include <iostream>

void Database::createRelations(vector<Predicate> scheme_list,
                    vector<Predicate> fact_list)
{
    for (auto current_scheme : scheme_list)
    {
        Scheme new_scheme = Scheme();
        for (int y=0;y<current_scheme.name.size();y++){
            new_scheme.push_back(current_scheme.parameter_list[y].toString());
        }

        Relation new_relation = Relation(current_scheme.name, new_scheme);
        
        // Populate tuples
        for(auto current_fact : fact_list)
        {
            if (current_fact.name == current_scheme.name)
                new_relation.addTuple(current_fact.getParameters());
        }
        this->insert(pair<string, Relation>(new_relation.name, new_relation));
    }
}


string Database::evaluateQuery(Predicate query)
{
    string output = "";
    output += query.toString() + "?";

    int match_count = 0;
    for (auto relation_iter=this->begin();relation_iter!=this->end();relation_iter++)
    {
        Relation test = relation_iter->second;

        test = select(test, query.parameter_list);
        test = project(test, query);
        test = rename(test, "", 1);

        output += test.toString() + "\n";
    }

    cout << output;
    return "";
}

void Database::evaluateQueries(vector<Predicate> query_list)
{
    for (auto current_query : query_list){
        evaluateQuery(current_query);
    }
}


Relation Database::select(Relation current_relation, vector<Parameter> parameter_list)
{
    Relation new_relation = Relation(current_relation.name, current_relation.scheme);
    map<string, int> variable_names;
    for (int index=0;index<current_relation.scheme.size();index++)
    {
        if (parameter_list[index].toString()[0] != '\'')
            variable_names.insert(pair<string, int>(parameter_list[index].toString(), index));
    }
    for (int index=0;index<current_relation.scheme.size();index++)
    {
        bool duplicate = false;
        auto duplicate_index = variable_names.find(parameter_list[index].toString());
        if (duplicate_index != variable_names.end())
        {
            // Already there
            duplicate = true;
        }
        for (auto current_tuple : current_relation.tuple_list)
        {
            if (duplicate && current_tuple[duplicate_index->second] != current_tuple[index])
            {
                cout << "mismatch! " << current_tuple[duplicate_index->second] << " " << current_tuple[index] << endl;
                continue;
            }
            else if (current_tuple[index] != parameter_list[index].toString() || parameter_list[index].toString()[0] != '\'')
            {
                // matched a terminal
                new_relation.addTuple(current_tuple);
            }
        }
    }
    return new_relation;
}


Relation Database::project(Relation current_relation, Predicate query)
{
    return current_relation;
}


Relation Database::rename(Relation current_relation, string new_name, int index)
{
    current_relation.scheme[index] = new_name;
    return current_relation;
}