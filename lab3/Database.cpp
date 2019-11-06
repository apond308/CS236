#include "Database.h"
#include <iostream>

void Database::createRelations(vector<Predicate> scheme_list,
                    vector<Predicate> fact_list,
                    vector<Rule> rule_list,
                    vector<Predicate> query_list)
{
    for (auto current_scheme : scheme_list)
    {
        Scheme new_scheme = Scheme();
        for (int y=0;y<current_scheme.name.size();y++){
            new_scheme.push_back(current_scheme.name.substr(y, 1));
        }

        Relation new_relation = Relation(current_scheme.name, new_scheme);
        

        // Populate tuples
        for(auto current_fact : fact_list)
        {
            if (current_fact.name == current_scheme.name)
                new_relation.addTouple(current_fact.getParameters());
        }
        
        this->insert(pair<string, Relation>(new_relation.name, new_relation));
    }
}