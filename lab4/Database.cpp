#include "Database.h"
#include <iostream>
#include <algorithm>

void Database::createRelations(vector<Predicate> scheme_list,
                    vector<Predicate> fact_list)
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


Relation Database::evaluateQuery(Relation relation_in, Predicate query)
{
    if (relation_in.name == query.name)
    {
        relation_in = select(relation_in, query.parameter_list);
        relation_in = project(relation_in, query.parameter_list);
        return relation_in;
    }
    return Relation(relation_in.name, relation_in.scheme);
    
}

void Database::evaluateQueries(vector<Predicate> query_list)
{
    for (auto current_query : query_list){
        for (auto current_relation : *this)
        {
            Relation new_relation = evaluateQuery(current_relation.second, current_query);
            cout << current_query.toString() + "?";
            if (new_relation.tuple_list.size() > 0){
                cout << " Yes(" + to_string(new_relation.tuple_list.size()) + ")";
                cout << new_relation.toString();
            }
            else
                cout << " No";
            cout << endl;
        }
    }
}


void Database::evaluateRules(vector<Rule> rule_list)
{
    int tuple_count;
    int prev_tuple_count;
    do
    {
        for (auto current_rule : rule_list)
        {
            vector<Relation> relation_list;
            for (int x=0;x<current_rule.predicate_list.size();x++)
            {
                relation_list.push_back(evaluateQuery(this->find(current_rule.predicate_list[x].name)->second, current_rule.predicate_list[x]));
            }


            Relation new_relation = relation_list[0];
            for (int x=1;x<relation_list.size();x++)
            {
                new_relation = new_relation.join(relation_list[x]);
            }

            new_relation = project(new_relation, current_rule.head_predicate.parameter_list);
            new_relation.name = current_rule.head_predicate.name;


            this->find(new_relation.name)->second = this->find(new_relation.name)->second.unite(new_relation);
            cout << endl;
            
        }
        
    }while(tuple_count != prev_tuple_count);
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

    cout << current_relation.toString() << endl;
    for (auto scheme_letter : parameter_list)
    {
        if (scheme_letter.toString()[0] !='\'' && std::find(new_relation.scheme.begin(), new_relation.scheme.end(), scheme_letter.toString()) == new_relation.scheme.end())
            new_relation.scheme.push_back(scheme_letter.toString());
    }

    for (auto current_tuple : current_relation.tuple_list)
    {
        Tuple new_tuple = Tuple();
         
        for (int parameter_index=0;parameter_index<parameter_list.size();parameter_index++)
        {
            for (int scheme_index=0;scheme_index<current_relation.scheme.size();scheme_index++)
            {
                if (tolower(parameter_list[parameter_index].toString()[0]) == tolower(current_relation.scheme[scheme_index][0]))
                {
                    new_tuple.push_back(current_tuple[scheme_index]);
                    break;
                }
            }
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