#include "Graph.h"
#include "Node.h"
#include <iostream>

Graph Graph::generateDependencyGraph(vector<Rule> rules_in)
{
    Graph new_graph = Graph();

    vector<Node> node_list;
    for (auto x=0;x<rules_in.size();x++)
    {
        Node new_node = Node(rules_in[x], x);
        node_list.push_back(new_node);
    }

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
    new_graph.node_list = node_list;

    return new_graph;
}

Graph Graph::generateReverseGraph(vector<Rule> rules_in)
{
    Graph new_graph = Graph();

    vector<Node> node_list;
    for (auto x=0;x<rules_in.size();x++)
    {
        Node new_node = Node(rules_in[x], x);
        node_list.push_back(new_node);
    }

    // Generate dependencies for each rule
    for (auto node_index=0;node_index<node_list.size();node_index++)
    {
        for (auto predicate : node_list[node_index].reference_rule.predicate_list)
        {
            for (auto x=0;x<node_list.size();x++)
            {
                if (node_list[x].reference_rule.head_predicate.name == predicate.name)
                {
                    node_list[x].dependencies.push_back(node_index);
                }
            }
        }
    }
    new_graph.node_list = node_list;

    return new_graph;
}

string Graph::toString()
{
    string output_string = "";
    for (auto node : this->node_list)
    {
        output_string += "R" + to_string(node.rule_index) + ":";
        if (node.dependencies.size() > 0)
        {
            for (auto x=0;x<node.dependencies.size();x++)
            {
                output_string += " R" + to_string(node_list[node.dependencies[x]].rule_index) + ",";
            }
            output_string[output_string.size()-1] = '\n';
        }
    }
    return output_string;
}