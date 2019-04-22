#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <tuple>

using namespace std;

void check_custo(std::vector<float>& custo){
    for (int i = 0; i < custo.size(); i++) {
        if (custo[i] < 0) {
            std::cout << "inviavel" << endl <<"vetor custo < 0" << '\n';
        }
    }
}

void fpi_base_canonica(std::vector<float>& custo , std::vector< std::vector<float> >& condicoes, int n_res){
    custo.resize(custo.size()+n_res);
    for (int i = 0; i < custo.size(); i++) {
        if (custo[i] != 0) {
            custo[i] = -custo[i];
        }
    }

    int old_size = condicoes.size();
    for (int i = 0; i < condicoes.size(); i++) {
        condicoes[i].resize(old_size+n_res+1);
        condicoes[i][condicoes[i].size()-1] = condicoes[i][old_size];
        condicoes[i][old_size] = 0;
    }

    int counter = condicoes.size();
    for (int i = 0; i < condicoes.size(); i++) {
        condicoes[i][counter] = 1;
        counter += 1;
    }
    //// VERIFICAR SE B TEM ALGUM VALOR NEGATIVO, SE SIM PL AUXILIAR
}

void pivotation(
    std::vector<float>& custo,
    std::vector< std::vector<float> >& condicoes,
    std::vector< std::vector<float> >& certificado,
    int pivot_x, int pivot_y){

    int pivot = condicoes[pivot_y][pivot_x];
    for (int i = 0; i < certificado[pivot_y].size(); i++) {
        certificado[pivot_y][i] = certificado[pivot_y][i]/pivot;
    }
    for (int i = 0; i < condicoes[pivot_y].size(); i++) {
        condicoes[pivot_y][i] = condicoes[pivot_y][i]/pivot;
    }
    
}


void simplex(
    std::vector<float>& custo,
    std::vector< std::vector<float> >& condicoes,
    std::vector< std::vector<float> >& certificado){

    for (int i = 0; i < custo.size(); i++) {
        if(custo[i] < 0){
            float div = condicoes[0][condicoes[0].size()]/condicoes[0][i];
            int pivot = 0;
            for (int j = 1; j < condicoes.size(); j++) {
                if (div > condicoes[j][condicoes[j].size()]/condicoes[j][i]) {
                    pivot = j;
                    div = condicoes[j][condicoes[j].size()]/condicoes[j][i];
                }
            }
            pivotation(custo, condicoes, certificado, pivot, i);
        }
    }
}

void simplex_init(
    std::vector<float> custo,
    std::vector< std::vector<float> > condicoes,
    std::vector< std::vector<float> > certificado){

    fpi_base_canonica(custo, condicoes, condicoes.size());
    simplex(custo, condicoes, certificado);

    cout << endl << endl;

    for (int i = 0; i < custo.size(); i++) {
        cout << custo[i] << ' ';
    }
    cout << endl << endl;

    for (int i = 0; i < condicoes.size(); i++) {
        for (int j = 0; j < condicoes[i].size(); j++) {
            cout << condicoes[i][j] << ' ';
        }
        cout << endl;
    }

}
