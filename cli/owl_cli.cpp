#include <iostream>
#include <map>
#include <cstring>
#include "cli.hpp"
using namespace std;

void showUsage() {
    cout<<"[ Owl v"<<OWL_VERSION<<" "<<FLACO<<" ]"<<endl;
    cout<<"Useage: "<<endl;
    cout<<"      owlcli <options> <filename> "<<endl;
    cout<<"Optional Flags: "<<endl;
    cout<<"       -v   display tokens and generated AST"<<endl;
    cout<<"       -vp  include trace of parse step"<<endl;
    cout<<"       -vi  show trace of interpreter"<<endl;
    cout<<"       -vip show all of the above"<<endl;
}

int main(int argc, char* argv[]) {
    srand(time(0));
    if (argc < 2) {
        showUsage();
        return 0;
    }
    OwlCLI owlCLI;
    if (argv[1][0] == '-' && argv[1][1] == 'v') {
        owlCLI.runVerbose(argv[1], argv[2]);
    } else {
        owlCLI.runQuiet(argv[1]);
    }
    return 0;
}