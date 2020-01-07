#include <stdio.h>
#include <iostream>
#include "Relation.h"
#include "Database.h"
#include "Parser.h"
#include "Scanner.h"
#include "Graph.h"
using namespace std;


// int main(int argc, char* argv[])
// {
// 	string filename = "lab5/test_file.txt";
// 	if (argc > 1)
// 		filename = argv[1];
//  	Scanner scanner = Scanner();
// 	vector<Token> token_list = scanner.tokenize(filename);
// 	Parser parser = Parser(token_list);
// 	parser.parse();

// 	Database database = Database();
// 	database.createRelations(parser.getSchemeList(), parser.getFactList());

// 	database.evaluateRules(parser.getRuleList());

// 	database.evaluateQueries(parser.getQueryList());
// }

// ########### Dependency Graph Test ############3
int main(int argc, char* argv[])
{
	vector<Rule> rule_list;



	// #### R0 ####

	// Make head predicate
	Predicate head_predicate = Predicate("Alpha");
	head_predicate.addParameter(Parameter("x"));
	head_predicate.addParameter(Parameter("y"));
	head_predicate.addParameter(Parameter("z"));

	// Make predicate 1
	Predicate predicate1 = Predicate("Bravo");
	predicate1.addParameter(Parameter("a"));
	predicate1.addParameter(Parameter("b"));
	predicate1.addParameter(Parameter("z"));

	// Make predicate 2
	Predicate predicate2 = Predicate("Charlie");
	predicate2.addParameter(Parameter("x"));
	predicate2.addParameter(Parameter("y"));
	predicate2.addParameter(Parameter("c"));

	// Create rule and add predicates
	Rule new_rule = Rule(head_predicate);
	new_rule.addPredicate(predicate1);
	new_rule.addPredicate(predicate2);

	// Add it to the list
	rule_list.push_back(new_rule);

	cout << new_rule.toString() << endl;




	// #### R1 ####

	// Make head predicate
	head_predicate = Predicate("Bravo");
	head_predicate.addParameter(Parameter("x"));
	head_predicate.addParameter(Parameter("y"));
	head_predicate.addParameter(Parameter("z"));

	// Make predicate 1
	predicate1 = Predicate("Charlie");
	predicate1.addParameter(Parameter("a"));
	predicate1.addParameter(Parameter("x"));
	predicate1.addParameter(Parameter("z"));

	// Make predicate 2
	predicate2 = Predicate("Alpha");
	predicate2.addParameter(Parameter("y"));
	predicate2.addParameter(Parameter("a"));
	predicate2.addParameter(Parameter("b"));

	// Create rule and add predicates
	new_rule = Rule(head_predicate);
	new_rule.addPredicate(predicate1);
	new_rule.addPredicate(predicate2);

	// Add it to the list
	rule_list.push_back(new_rule);

	cout << new_rule.toString() << endl;




	// #### R2 ####

	// Make head predicate
	head_predicate = Predicate("Charlie");
	head_predicate.addParameter(Parameter("x"));
	head_predicate.addParameter(Parameter("y"));
	head_predicate.addParameter(Parameter("z"));

	// Make predicate 1
	predicate1 = Predicate("Delta");
	predicate1.addParameter(Parameter("z"));
	predicate1.addParameter(Parameter("y"));
	predicate1.addParameter(Parameter("x"));

	// Create rule and add predicates
	new_rule = Rule(head_predicate);
	new_rule.addPredicate(predicate1);

	// Add it to the list
	rule_list.push_back(new_rule);

	cout << new_rule.toString() << endl;




	// #### R3 ####

	// Make head predicate
	head_predicate = Predicate("Delta");
	head_predicate.addParameter(Parameter("x"));
	head_predicate.addParameter(Parameter("y"));
	head_predicate.addParameter(Parameter("z"));

	// Make predicate 1
	predicate1 = Predicate("Charlie");
	predicate1.addParameter(Parameter("z"));
	predicate1.addParameter(Parameter("x"));
	predicate1.addParameter(Parameter("y"));

	// Create rule and add predicates
	new_rule = Rule(head_predicate);
	new_rule.addPredicate(predicate1);

	// Add it to the list
	rule_list.push_back(new_rule);

	cout << new_rule.toString() << endl;




	// #### R4 ####

	// Make head predicate
	head_predicate = Predicate("Delta");
	head_predicate.addParameter(Parameter("x"));
	head_predicate.addParameter(Parameter("y"));
	head_predicate.addParameter(Parameter("z"));

	// Make predicate 1
	predicate1 = Predicate("Echo");
	predicate1.addParameter(Parameter("z"));
	predicate1.addParameter(Parameter("y"));
	predicate1.addParameter(Parameter("x"));

	// Create rule and add predicates
	new_rule = Rule(head_predicate);
	new_rule.addPredicate(predicate1);

	// Add it to the list
	rule_list.push_back(new_rule);

	cout << new_rule.toString() << endl << endl << endl;



	Graph normal_graph = Graph::generateDependencyGraph(rule_list);

	cout << "\n################ Dependency Graph ################" << endl;
	cout << "\nExpected:\n" << "R0:R1,R2\nR1:R0,R2\nR2:R3,R4\nR3:R2\nR4:\n";
	cout << "\nActual:\n" << normal_graph.toString() << endl;

	
	Graph reverse_graph = Graph::generateReverseGraph(rule_list);

	cout << "\n################ Reverse Graph ################" << endl;
	cout << "\nExpected:\n" << "R0:R1\nR1:R0\nR2:R0,R1,R3\nR3:R2\nR4:R2\n";
	cout << "\nActual:\n" << reverse_graph.toString() << endl;


	vector<Node> postorder_list = reverse_graph.getPostOrder();
	vector<vector<Node>> scc_list = normal_graph.getSCCs(postorder_list);

	cout << "\n################ SCCs ################" << endl;
	cout << "\nExpected:\n" << "R4\nR2,R3\nR0,R1\n";
	cout << "\nActual:\n" << normal_graph.sccs_toString(scc_list) << endl;

}