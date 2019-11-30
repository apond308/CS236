#ifndef NODE_H
#define NODE_H

#include <string>
#include "Rule.h"

using namespace std;
class Node
{
public:

    Node(Rule rule_in, int index_in);

    Rule reference_rule;

    int rule_index;

    vector<int> dependencies;


};

#endif