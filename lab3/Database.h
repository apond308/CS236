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
            vector<Predicate> fact_list, vector<Rule> rule_list);
    void evaluateQueries(vector<Predicate> query_list);

    Relation select(Relation current_relation, vector<Parameter> parameter_list);
    Relation project(Relation current_relation, vector<Parameter> parameter_list);
    Relation rename(Relation current_relation, string old_name, string new_name);

private:
    string evaluateQuery(Predicate query);

};


#endif