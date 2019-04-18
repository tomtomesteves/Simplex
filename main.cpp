#include <iostream>
#include <ctime>
#include <string>
#include <fstream>

#include "DataInicial.h"

using namespace std;

int main(int argc, char const *argv[]) {
    auto [custo, condicoes, certificado] = read_file(argv[1]);
    return 0;
}
