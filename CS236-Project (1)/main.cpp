#include <string>
#include "lexer.h"

using namespace std;

int main(int argc, char* argv[]) {
    string filename = argv[1];
    new lexer(filename);
    return 0;
}

//g++ -Wall -Werror -std=c++17 -g *.cpp -o lab1