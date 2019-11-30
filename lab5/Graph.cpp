#include "Graph.h"

Graph::Graph(vector<Rule> rules_in)
{
    for (auto x=0;x<rules_in.size();x++)
    {
        Node new_node = Node(rules_in[x], x);
        node_list.push_back(new_node);
    }
}

void Graph::generateDependencyGraph()
{
    // Generate dependencies for each rule
    for (auto node_index=0;node_index<node_list.size();node_index++)
    {
        for (auto predicate : node_list[node_index].reference_rule.predicate_list)
        {
            for (auto x=0;x<node_list.size();x++)
            {
                if (node_list[x].reference_rule.head_predicate.name == predicate.name)
                {
                    node_list[node_index].dependencies.push_back(x);
                }
            }
        }
    }
}