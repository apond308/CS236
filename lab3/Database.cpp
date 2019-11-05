#include "Database.h"
#include <iostream>

void Database::createRelations(vector<Predicate> scheme_list,
                    vector<Predicate> fact_list,
                    vector<Rule> rule_list,
                    vector<Predicate> query_list)
{
    for (int x=0;x<scheme_list.size();x++)
    {
        Scheme new_scheme = Scheme();
        for (int y=0;y<scheme_list[x].name.size();y++){
            new_scheme.push_back(scheme_list[x].name.substr(y, 1));
        }

        Relation new_relation = Relation(scheme_list[x].name, new_scheme);
        new_relation.addTouple(scheme_list[x].getParameters());
        
        this->insert(pair<string, Relation>(new_relation.name, new_relation));
    }
}