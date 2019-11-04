#include <stdio.h>
#include "Token.h"
#include "Scanner.h"
#include <unistd.h>

namespace lab1
{

    void run()
    {
        printf("Starting lab...\n");
        Scanner scanner = Scanner();
        scanner.tokenize("235/lab1/test_file.txt");
    }

}