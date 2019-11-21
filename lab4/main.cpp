#include <stdio.h>
#include <iostream>
#include "Relation.h"
#include "Database.h"
#include "Parser.h"
#include "Scanner.h"

using namespace std;
// int main(int argc, char* argv[])
// {
// 	string filename = "lab3/test_file.txt";
// 	if (argc > 1)
// 		filename = argv[1];
//  Scanner scanner = Scanner();
// 	vector<Token> token_list = scanner.tokenize(filename);
// 	Parser parser = Parser(token_list);
// 	parser.parse();

// 	Database database = Database();
// 	database.createRelations(parser.getSchemeList(), parser.getFactList(), parser.getRuleList());

// 	database.evaluateQueries(parser.getQueryList());
// }

int main(int argc, char* argv[])
{
	string filename = "lab4/join_test.txt";
	if (argc > 1)
		filename = argv[1];

	Scanner scanner = Scanner();
	vector<Token> token_list = scanner.tokenize(filename);
	Parser parser = Parser(token_list);
	parser.parse();

	Database database = Database();
	database.createRelations(parser.getSchemeList(), parser.getFactList(), parser.getRuleList());

	Relation a = database.at("alpha");
	Relation b = database.at("beta");

	Relation result = a.join(b);

}