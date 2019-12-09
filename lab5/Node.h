#ifndef NODE_H
#define NODE_H

#include <string>
#include "Rule.h"
#include <set>

using namespace std;
class Node
{
public:

    Node(Rule rule_in, int index_in);

    bool operator<(Node const& a)
    {
        return this->rule_index < a.rule_index;
    }

    Rule reference_rule;

    int rule_index;

    set<int> dependencies;


};

#endif