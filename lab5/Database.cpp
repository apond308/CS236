#include "Database.h"
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include "Graph.h"

using namespace std;

void Database::createRelations(vector<Predicate> scheme_list,
                    vector<Predicate> fact_list)
{
    for (auto current_scheme : scheme_list)
    {
        Scheme new_scheme = Scheme();
        for (long unsigned int y=0;y<current_scheme.parameter_list.size();y++){
            new_scheme.push_back(current_scheme.parameter_list[y].toString());
        }

        Relation new_relation = Relation(current_scheme.name, new_scheme);
        
        // Populate tuples
        for(auto current_fact : fact_list)
        {
            if (current_fact.name == current_scheme.name)
                new_relation.addTuple(current_fact.getParameters());
        }
        this->insert(pair<string, Relation>(new_relation.name, new_relation));
    }
}


Relation Database::evaluateQuery(Relation relation_in, Predicate query)
{
    Relation new_relation = relation_in;

    map<string, vector<int>> seen;
    for (int parameter_index=0;parameter_index<query.parameter_list.size();parameter_index++)
    {
        if (query.parameter_list[parameter_index].toString()[0] == '\'')
            new_relation = select1(new_relation, parameter_index, query.parameter_list[parameter_index].toString());
        else
        {
            if (seen.find(query.parameter_list[parameter_index].toString()) == seen.end())
                // Mark to keep for project and rename
                seen.insert(pair<string, vector<int>>(query.parameter_list[parameter_index].toString(), vector<int>{parameter_index}));
            else
                seen[query.parameter_list[parameter_index].toString()].push_back(parameter_index);
        }
    }

    set<int> to_project;
    for (auto see : seen)
    {
        to_project.insert(see.second[0]);
        new_relation = rename(new_relation, see.second[0], see.first);
    }
    vector<int> to_project_ordered;
    for (auto it : to_project)
    {
        to_project_ordered.push_back(it);
    }
    
    new_relation = project(new_relation, to_project_ordered);
    
    new_relation = new_relation;

    return new_relation;
    
}

void Database::evaluateQueries(vector<Predicate> query_list)
{
    cout << "Query Evaluation" << endl;
    for (auto current_query : query_list){
        for (auto current_relation : *this)
        {
            if (current_relation.second.name == current_query.name)
            {
                Relation new_relation = evaluateQuery(current_relation.second, current_query);
                cout << current_query.toString() + "?";
                if (new_relation.tuple_list.size() > 0){
                    cout << " Yes(" + to_string(new_relation.tuple_list.size()) + ")" << endl;
                    cout << new_relation.toString();
                }
                else
                    cout << " No";
            }
        }
    }
}

void Database::evaluateRule(Rule reference_rule)
{
    vector<Relation> relation_list;
    for (int x=0;x<reference_rule.predicate_list.size();x++)
    {
        relation_list.push_back(evaluateQuery(this->find(reference_rule.predicate_list[x].name)->second, reference_rule.predicate_list[x]));
    }


    Relation new_relation = relation_list[0];
    for (int x=1;x<relation_list.size();x++)
    {
        new_relation = new_relation.join(relation_list[x]);
    }

    vector<int> indexes;
    for (auto param : reference_rule.head_predicate.parameter_list)
    {
        for (int scheme_index=0;scheme_index<new_relation.scheme.size();scheme_index++)
        {
            if (new_relation.scheme[scheme_index] == param.toString())
                indexes.push_back(scheme_index);
        }
    }

    new_relation = project(new_relation, indexes);
    new_relation.name = reference_rule.head_predicate.name;

    int prev_count = this->find(new_relation.name)->second.tuple_list.size();

    pair<Relation, Relation> unite_result = this->find(new_relation.name)->second.unite(new_relation);
    this->find(new_relation.name)->second = unite_result.first;

    cout << reference_rule.toString() << endl;
    if (unite_result.second.tuple_list.size() > 0)
    {
        cout << unite_result.second.toString();
    }
}

void Database::evaluateRules(vector<Rule> rule_list)
{
    Graph normal_graph = Graph::generateDependencyGraph(rule_list);
    cout << "Dependency Graph" << endl;
	cout << normal_graph.toString() << endl;

	Graph reverse_graph = Graph::generateReverseGraph(rule_list);

	vector<Node> postorder_list = reverse_graph.getPostOrder();

	vector<vector<Node>> scc_list = normal_graph.getSCCs(postorder_list);

	cout << "Rule Evaluation" << endl;

    for (auto scc : scc_list)
    {
        cout << "SCC: " + Graph::scc_toString(scc) << endl;
        bool once = false;
        int passes = 0;
        if (scc.size() == 1 && scc.begin()->dependencies.find(scc.begin()->rule_index) == scc.begin()->dependencies.end())
        {
            once = true;
        }
        int tuple_count = 0;
        for (auto tuple : *this)
        {
            tuple_count += tuple.second.tuple_list.size();
        }
        int prev_tuple_count = tuple_count;
        do
        {
            for (auto node : scc)
            {
                evaluateRule(node.reference_rule);
            }
            passes++;
            prev_tuple_count = tuple_count;
            tuple_count = 0;
            for (auto relation : *this)
            {
                tuple_count += relation.second.tuple_list.size();
            }
        } while (!once && tuple_count != prev_tuple_count);
        cout << passes << " passes: " << Graph::scc_toString(scc) << endl;
    }
    cout << endl;
}

void Database::evaluateRules_old(vector<Rule> rule_list)
{
    int passes_completed = 0;
    int tuple_count = 0;
    int prev_tuple_count;

    Graph depencency_graph = Graph::generateDependencyGraph(rule_list);

    do
    {
        prev_tuple_count = tuple_count;
        for (auto current_rule : rule_list)
        {
            vector<Relation> relation_list;
            for (int x=0;x<current_rule.predicate_list.size();x++)
            {
                relation_list.push_back(evaluateQuery(this->find(current_rule.predicate_list[x].name)->second, current_rule.predicate_list[x]));
            }


            Relation new_relation = relation_list[0];
            for (int x=1;x<relation_list.size();x++)
            {
                new_relation = new_relation.join(relation_list[x]);
            }

            vector<int> indexes;
            for (auto param : current_rule.head_predicate.parameter_list)
            {
                for (int scheme_index=0;scheme_index<new_relation.scheme.size();scheme_index++)
                {
                    if (new_relation.scheme[scheme_index] == param.toString())
                        indexes.push_back(scheme_index);
                }
            }

            new_relation = project(new_relation, indexes);
            new_relation.name = current_rule.head_predicate.name;

            cout << current_rule.toString();
            // this->find(new_relation.name)->second = this->find(new_relation.name)->second.unite(new_relation);
        }

        tuple_count = 0;
        for (auto current_relation : *this)
        {
            for (auto current_tuple : current_relation.second.tuple_list)
                tuple_count++;
        }
        passes_completed++;

    }while(tuple_count != prev_tuple_count);
}


Relation Database::select1(Relation relation_in, int index, string parameter)
{
    Relation new_relation = Relation(relation_in.name, relation_in.scheme);

    for (auto current_tuple=relation_in.tuple_list.begin();current_tuple!=relation_in.tuple_list.end();current_tuple++)
    {
        if (current_tuple->at(index) == parameter)
            new_relation.addTuple(*current_tuple);
    }
    return new_relation;
}

Relation Database::select2(Relation relation_in, vector<int> indexes)
{
    Relation new_relation = Relation(relation_in.name, relation_in.scheme);

    for (auto current_tuple=relation_in.tuple_list.begin();current_tuple!=relation_in.tuple_list.end();current_tuple++)
    {
        string value = current_tuple->at(indexes[0]);
        bool valid = true;
        for (int x=1;x<indexes.size();x++)
        {
            if (current_tuple->at(indexes[x]) != value)
                valid = false;
        }
        if (valid)
            new_relation.addTuple(*current_tuple);
    }
    return new_relation;
}

Relation Database::project(Relation relation_in, vector<int> names)
{
    Relation new_relation = Relation(relation_in.name, Scheme());
    
    for (auto scheme_index : names)
        new_relation.scheme.push_back(relation_in.scheme[scheme_index]);
    
    for (auto current_tuple : relation_in.tuple_list)
    {
        Tuple new_tuple = Tuple();
        for (auto scheme_index : names)
        {
            new_tuple.push_back(current_tuple[scheme_index]);
        }
        new_relation.addTuple(new_tuple);
    }

    return new_relation;
}


Relation Database::oldselect(Relation current_relation, vector<Parameter> parameter_list)
{
    Relation new_relation = Relation(current_relation.name, current_relation.scheme);
    
    for (auto current_tuple : current_relation.tuple_list)
    {
        vector<string> rejected_variables;
        bool valid = true;
        for (long unsigned int index=0;index<parameter_list.size();index++)
        {
            string current_variable = parameter_list[index].toString();
            if (current_variable[0] == '\'')
            {
                // If it's a terminal, see if it matches
                if (current_variable != current_tuple[index])
                    valid = false;
            }
            else
            {
                for (long unsigned int x=index;x<parameter_list.size() && valid;x++)
                {
                    if (std::find(rejected_variables.begin(), rejected_variables.end(), current_variable) != rejected_variables.end())
                        valid = false;
                    else if (parameter_list[x].toString() == current_variable)
                    {
                        // check to see if there are other parameters of the same name
                        if (current_tuple[x] != current_tuple[index])
                        {
                            valid = false;
                            rejected_variables.push_back(parameter_list[x].toString());
                        }
                    }
                }
            }
        }
        if (valid)
            new_relation.addTuple(current_tuple);
    }
    return new_relation;
}


Relation Database::oldproject(Relation current_relation, vector<Parameter> parameter_list)
{
    Relation new_relation = Relation(current_relation.name, Scheme());

    cout << current_relation.toString() << endl;
    for (auto scheme_letter : parameter_list)
    {
        if (scheme_letter.toString()[0] !='\'' && std::find(new_relation.scheme.begin(), new_relation.scheme.end(), scheme_letter.toString()) == new_relation.scheme.end())
            new_relation.scheme.push_back(scheme_letter.toString());
    }

    for (auto current_tuple : current_relation.tuple_list)
    {
        Tuple new_tuple = Tuple();
         
        for (int parameter_index=0;parameter_index<parameter_list.size();parameter_index++)
        {
            for (int scheme_index=0;scheme_index<current_relation.scheme.size();scheme_index++)
            {
                if (tolower(parameter_list[parameter_index].toString()[0]) == tolower(current_relation.scheme[scheme_index][0]))
                {
                    new_tuple.push_back(current_tuple[scheme_index]);
                    break;
                }
            }
        }

        new_relation.addTuple(new_tuple);
    }

    return new_relation;
}


Relation Database::rename(Relation current_relation, int index, string new_name)
{
    current_relation.scheme[index] = new_name;
    return current_relation;
}