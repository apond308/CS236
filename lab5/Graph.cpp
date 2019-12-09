#include "Graph.h"
#include "Node.h"
#include <stack>
#include <set>
#include <iostream>
#include <algorithm>

Graph Graph::generateDependencyGraph(vector<Rule> rules_in)
{
    Graph new_graph = Graph();

    vector<Node> node_list;
    for (unsigned x=0;x<rules_in.size();x++)
    {
        Node new_node = Node(rules_in[x], x);
        node_list.push_back(new_node);
    }

    // Generate dependencies for each rule
    for (unsigned node_index=0;node_index<node_list.size();node_index++)
    {
        for (auto predicate : node_list[node_index].reference_rule.predicate_list)
        {
            for (unsigned x=0;x<node_list.size();x++)
            {
                if (node_list[x].reference_rule.head_predicate.name == predicate.name &&
                    std::find(node_list[node_index].dependencies.begin(), node_list[node_index].dependencies.end(), x) == node_list[node_index].dependencies.end())
                {
                    node_list[node_index].dependencies.insert(x);
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
    for (unsigned x=0;x<rules_in.size();x++)
    {
        Node new_node = Node(rules_in[x], x);
        node_list.push_back(new_node);
    }

    // Generate dependencies for each rule
    for (unsigned node_index=0;node_index<node_list.size();node_index++)
    {
        for (auto predicate : node_list[node_index].reference_rule.predicate_list)
        {
            for (unsigned x=0;x<node_list.size();x++)
            {
                if (node_list[x].reference_rule.head_predicate.name == predicate.name)
                {
                    node_list[x].dependencies.insert(node_index);
                }
            }
        }
    }
    new_graph.node_list = node_list;
    return new_graph;
}

void Graph::goDeep(Node current_node)
{
    if (visited_list.find(current_node.rule_index) != visited_list.end())
        return;
    visited_list.insert(current_node.rule_index);
    for (auto dependency : current_node.dependencies)
    {
        for (auto node=node_list.begin();node!=node_list.end();node++)
        {
            if (node->rule_index == dependency)
            {
                goDeep(*node);
            }
        }
    }
    order_list.push_back(current_node);
}

vector<Node> Graph::getPostOrder()
{
    vector<Node>::iterator current_node = node_list.begin();

    order_list.clear();
    visited_list.clear();

    while(current_node != node_list.end())
    {
        goDeep(*current_node);
        current_node++;
    }

    return order_list;
}

vector<vector<Node>> Graph::getSCCs(vector<Node> postorder_list)
{
    visited_list.clear();
    
    for(int post_index=postorder_list.size()-1;post_index>=0;post_index--)
    {
        auto node = getNodeWithIndex(postorder_list[post_index].rule_index);
        goDeep(node);
        if (order_list.size() > 0){
            sort(order_list.begin(), order_list.end());
            scc_list.push_back(order_list);
            order_list.clear();
        }
    }
    return scc_list;
}

Node Graph::getNodeWithIndex(int index)
{
    for (auto node : node_list)
    {
        if (node.rule_index == index)
            return node;
    }
    return Node(Rule(), 0);
}

string Graph::scc_toString(vector<Node> scc)
{
    string output_string = "";
    for (int x=0;x<(int)scc.size();x++)
    {
        output_string += "R" + to_string(scc[x].rule_index);
        if (x != (int)scc.size()-1)
            output_string += ",";
    }
    return output_string;
}

string Graph::sccs_toString(vector<vector<Node>> scc_list)
{
    string output_string = "";
    for (unsigned index=0;index<scc_list.size();index++)
    {
        output_string += scc_toString(scc_list[index]);
        output_string += "\n";
    }
    return output_string;
}

string Graph::toString()
{
    string output_string = "";
    for (auto node : this->node_list)
    {
        output_string += "R" + to_string(node.rule_index) + ":";
        if (node.dependencies.size() > 0)
        {
            for (auto dependency : node.dependencies)
            {
                output_string += "R" + to_string(node_list[dependency].rule_index) + ",";
            }
            output_string.pop_back();
        }
        output_string += "\n";
    }
    return output_string;
}