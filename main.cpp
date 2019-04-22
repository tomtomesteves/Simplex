#include <iostream>
#include <ctime>
#include <string>
#include <fstream>

#include "DataInicial.h"
#include "simplex.h"


using namespace std;

int main(int argc, char const *argv[]) {
    ofstream outfile(argv[2]);
    auto [custo, condicoes, certificado] = read_file(argv[1]);
    simplex_init(custo, condicoes, certificado);
    return 0;
}
