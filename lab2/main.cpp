#include "Scanner.h"
#include "Parser.h"
#include <stdio.h>

int main()
{
	Scanner scanner = Scanner();
	vector<Token> token_list = scanner.tokenize("235/lab2/test_file.txt");
	Parser parser = Parser(token_list);
	parser.parse();
	parser.printLists();

	while(true);
}

// int main(int argc, char* argv[]){
//     string filename = argv[1];
// 	Scanner scanner = Scanner();
// 	vector<Token> token_list = scanner.tokenize(filename);
// 	Parser parser = Parser(token_list);
// 	parser.parse();
// 	parser.printLists();
// }