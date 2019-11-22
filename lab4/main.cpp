#include <stdio.h>
#include <iostream>
#include "Relation.h"
#include "Database.h"
#include "Parser.h"
#include "Scanner.h"

using namespace std;
int main(int argc, char* argv[])
{
	string filename = "lab4/test_file.txt";
	if (argc > 1)
		filename = argv[1];
 Scanner scanner = Scanner();
	vector<Token> token_list = scanner.tokenize(filename);
	Parser parser = Parser(token_list);
	parser.parse();

	Database database = Database();
	database.createRelations(parser.getSchemeList(), parser.getFactList());

	database.evaluateRules(parser.getRuleList());

	database.evaluateQueries(parser.getQueryList());
}


//################## JOIN TEST ########################
// int main(int argc, char* argv[])
// {
// 	string filename = "lab4/join_test.txt";
// 	if (argc > 1)
// 		filename = argv[1];

// 	Scanner scanner = Scanner();
// 	vector<Token> token_list = scanner.tokenize(filename);
// 	Parser parser = Parser(token_list);
// 	parser.parse();

// 	Database database = Database();
// 	database.createRelations(parser.getSchemeList(), parser.getFactList(), parser.getRuleList());

// 	Relation alpha = database.at("alpha");
// 	Relation beta = database.at("beta");

// 	Relation check = database.at("answer");

// 	Relation result = alpha.join(beta);

// 	cout << "Expected answer:";
// 	cout << check.toString() << endl;

// 	cout << endl;

// 	cout << "Actual answer:";
// 	cout << result.toString() << endl << endl;

// }


// #################### UNION TEST #######################
// int main(int argc, char* argv[])
// {
// 	string filename = "lab4/union_test.txt";
// 	if (argc > 1)
// 		filename = argv[1];

// 	Scanner scanner = Scanner();
// 	vector<Token> token_list = scanner.tokenize(filename);
// 	Parser parser = Parser(token_list);
// 	parser.parse();

// 	Database database = Database();
// 	database.createRelations(parser.getSchemeList(), parser.getFactList());

// 	Relation alpha = database.at("alpha");
// 	Relation beta = database.at("beta");

// 	Relation check = database.at("answer");

// 	Relation result = alpha.unite(beta);

// 	cout << "Expected answer:";
// 	cout << check.toString() << endl;

// 	cout << endl;

// 	cout << "Actual answer:";
// 	cout << result.toString() << endl << endl;

// }




// int main(int argc, char* argv[])
// {
// 	string filename = "lab4/project_test.txt";
// 	if (argc > 1)
// 		filename = argv[1];

// 	Scanner scanner = Scanner();
// 	vector<Token> token_list = scanner.tokenize(filename);
// 	Parser parser = Parser(token_list);
// 	parser.parse();

// 	Database database = Database();
// 	database.createRelations(parser.getSchemeList(), parser.getFactList());

// 	Relation test = database.at("test");

// 	vector<Parameter> parameter_list;
// 	parameter_list.push_back(Parameter("c"));
// 	parameter_list.push_back(Parameter("n"));

// 	database.project(test, parameter_list);

// }