#include "Node.h"

Node::Node(Rule rule_in, int index_in)
{
    this->reference_rule = rule_in;
    this->rule_index = index_in;
}