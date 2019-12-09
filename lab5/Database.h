#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <string>
#include <vector>
#include "Relation.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"

using namespace std;
class Database : public map<string, Relation>
{
public:

    void createRelations(vector<Predicate> scheme_list,
            vector<Predicate> fact_list);
    void evaluateQueries(vector<Predicate> query_list);
    void evaluateRule(Rule reference_rule);
    void evaluateRules(vector<Rule> rule_list);
    void evaluateRules_old(vector<Rule> rule_list);

    Relation select1(Relation relation_in, int index, string parameter);
    Relation select2(Relation relation_in, vector<int> indexes);
    Relation project(Relation relation_in, vector<int> names);
    Relation rename(Relation current_relation, int index, string new_name);

    Relation oldselect(Relation current_relation, vector<Parameter> parameter_list);
    Relation oldproject(Relation current_relation, vector<Parameter> parameter_list);

    Relation evaluateQuery(Relation relation_in, Predicate query);

};


#endif