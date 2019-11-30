#ifndef RULE_H
#define RULE_H
using namespace std;

#include <string>

#include "Predicate.h"

class Rule
{
public:

    Rule(Predicate predicate_in);

    std::string toString();

    void addPredicate(Predicate new_predicate);


    Predicate head_predicate;

    vector<Predicate> predicate_list;

};

#endif