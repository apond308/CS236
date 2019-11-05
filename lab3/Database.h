#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <string>
#include "Relation.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"

using namespace std;
class Database : public map<string, Relation>
{
public:

    void createRelations(vector<Predicate> scheme_list,
                         vector<Predicate> fact_list,
                         vector<Rule> rule_list,
                         vector<Predicate> query_list);


};


#endif