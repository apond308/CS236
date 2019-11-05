#include <stdio.h>
#include <iostream>
#include "Relation.h"
#include "Database.h"
#include "Parser.h"
#include "Scanner.h"

using namespace std;
int main()
{
    Scanner scanner = Scanner();
	vector<Token> token_list = scanner.tokenize("lab3/test_file.txt");
	Parser parser = Parser(token_list);
	parser.parse();
    

	parser.printLists();

	Database database = Database();
	database.createRelations(parser.getSchemeList(), parser.getFactList(),
								parser.getRuleList(), parser.getQueryList());
}