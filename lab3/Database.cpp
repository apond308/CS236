#include "Database.h"
#include <iostream>
#include <algorithm>

void Database::createRelations(vector<Predicate> scheme_list,
                    vector<Predicate> fact_list, vector<Rule> rule_list)
{
    for (auto current_scheme : scheme_list)
    {
        Scheme new_scheme = Scheme();
        for (long unsigned int y=0;y<current_scheme.parameter_list.size();y++){
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

    for (auto relation_iter=this->begin();relation_iter!=this->end();relation_iter++)
    {
        if (relation_iter->second.name == query.name)
        {
            Relation test = relation_iter->second;

            test = select(test, query.parameter_list);
            test = project(test, query.parameter_list);

            if (test.tuple_list.size() > 0){
                output += " Yes(" + to_string(test.tuple_list.size()) + ")";
                output += test.toString();
            }
            else
                output += " No";
        }
    }
        
    return output;
}

void Database::evaluateQueries(vector<Predicate> query_list)
{
    for (auto current_query : query_list){
        cout << evaluateQuery(current_query) << endl;
    }
}


Relation Database::select(Relation current_relation, vector<Parameter> parameter_list)
{
    Relation new_relation = Relation(current_relation.name, current_relation.scheme);
    
    for (auto current_tuple : current_relation.tuple_list)
    {
        vector<string> rejected_variables;
        bool valid = true;
        for (long unsigned int index=0;index<parameter_list.size();index++)
        {
            string current_variable = parameter_list[index].toString();
            if (current_variable[0] == '\'')
            {
                // If it's a terminal, see if it matches
                if (current_variable != current_tuple[index])
                    valid = false;
            }
            else
            {
                for (long unsigned int x=index;x<parameter_list.size() && valid;x++)
                {
                    if (std::find(rejected_variables.begin(), rejected_variables.end(), current_variable) != rejected_variables.end())
                        valid = false;
                    else if (parameter_list[x].toString() == current_variable)
                    {
                        // check to see if there are other parameters of the same name
                        if (current_tuple[x] != current_tuple[index])
                        {
                            valid = false;
                            rejected_variables.push_back(parameter_list[x].toString());
                        }
                    }
                }
            }
        }
        if (valid)
            new_relation.addTuple(current_tuple);
    }
    return new_relation;
}


Relation Database::project(Relation current_relation, vector<Parameter> parameter_list)
{
    Relation new_relation = Relation(current_relation.name, Scheme());

    for (auto scheme_letter : parameter_list)
    {
        if (scheme_letter.toString()[0] !='\'' && std::find(new_relation.scheme.begin(), new_relation.scheme.end(), scheme_letter.toString()) == new_relation.scheme.end())
            new_relation.scheme.push_back(scheme_letter.toString());
    }

    for (auto current_tuple : current_relation.tuple_list)
    {
        Tuple new_tuple = Tuple();
        auto scheme_letter = new_relation.scheme.begin();
        while(scheme_letter != new_relation.scheme.end())
        {
            // Get value from tuple
            for (long unsigned int tuple_index=0;tuple_index<current_tuple.size();tuple_index++)
            {
                if (parameter_list[tuple_index].toString() == *scheme_letter){
                    new_tuple.push_back(current_tuple[tuple_index]);
                    break;
                }
            }
            scheme_letter++;
        }
        new_relation.addTuple(new_tuple);
    }

    return new_relation;
}


Relation Database::rename(Relation current_relation, string old_name, string new_name)
{
    for (long unsigned int x=0;x<current_relation.scheme.size();x++)
    {
        if (current_relation.scheme[x] == old_name)
            current_relation.scheme[x] = new_name;
    }
    return current_relation;
}