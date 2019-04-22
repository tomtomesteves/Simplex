#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <tuple>
#include <cmath>

using namespace std;

void check_custo(std::vector<float>& custo){
    for (int i = 0; i < custo.size(); i++) {
        if (custo[i] < 0) {
            std::cout << "inviavel" << endl <<"vetor custo < 0" << '\n';
        }
    }
}

void printall(
    std::vector<float>& custo,
    std::vector< std::vector<float> >& condicoes,
    std::vector< std::vector<float> >& certificado) {
    cout << endl << endl << "custo : " << endl << endl;

    for (int i = 0; i < custo.size(); i++) {
        cout << custo[i] << ' ';
    }

    cout << endl << endl << "condicoes : " << endl << endl;


    for (int i = 0; i < condicoes.size(); i++) {
        for (int j = 0; j < condicoes[i].size(); j++) {
            cout << condicoes[i][j] << ' ';
        }
        cout << endl;
    }

    cout << endl << endl << "certificado : " << endl << endl;

    for (int i = 0; i < certificado.size(); i++) {
        for (int j = 0; j < certificado[i].size(); j++) {
            cout << certificado[i][j] << ' ';
        }
        cout << endl;
    }
}


bool check_valid_base(std::vector<float>& custo, std::vector< std::vector<float> >& condicoes){
    bool test,cond_ok ;
    int counter = 0;
    for (int i = 0; i < condicoes.size(); i++) {
        for (int j = 0; j < condicoes[i].size()-1; j++) {
            if (condicoes[i][j] == 1) {
                cond_ok = false ;
                if (custo[j] == 0) {
                    cond_ok = true;
                    for (int k = 0; k < condicoes.size(); k++) {
                        if (condicoes[k][j] != 0 && k != i) {
                            cond_ok = false;
                        }
                    }
                }
            }
            if (cond_ok) {
                counter++;
                break;
            }
        }
    }
    if (counter == condicoes.size()) {
        return true;
    }
    return false;
}

void fpi_base_canonica(std::vector<float>& custo , std::vector< std::vector<float> >& condicoes, int n_res){
    if (!check_valid_base(custo,condicoes)) {
        custo.resize(custo.size()+n_res);


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
    }
    for (int i = 0; i < custo.size(); i++) {
        if (custo[i] != 0) {
            custo[i] = -custo[i];
    }
}
    //// VERIFICAR SE B TEM ALGUM VALOR NEGATIVO, SE SIM PL AUXILIAR
}

void pivotation(
    std::vector<float>& custo,
    std::vector< std::vector<float> >& condicoes,
    std::vector< std::vector<float> >& certificado,
    int pivot_x, int pivot_y){

    int pivot = condicoes[pivot_y][pivot_x];
    cout << "pivot: " << pivot << endl;
    cout << "x : " << pivot_x << endl;
    cout << "y : " << pivot_y << endl;
    for (int i = 0; i < certificado[pivot_y].size(); i++) {
        certificado[pivot_y][i] = certificado[pivot_y][i]/pivot;
    }
    for (int i = 0; i < condicoes[pivot_y].size(); i++) {
        condicoes[pivot_y][i] = condicoes[pivot_y][i]/pivot;
    }
    for (int i = 0; i < condicoes.size() && i != pivot_y; i++) {
        int mod = fmod(condicoes[i][pivot_x],condicoes[pivot_y][pivot_x]);
        cout << "mod >> " << mod << endl;
        for (int j = 0; j < condicoes[i].size(); j++) {
            condicoes[i][j] = condicoes[i][j]/(mod*condicoes[pivot_y][j]);
        }
    }
}


void simplex(
    std::vector<float>& custo,
    std::vector< std::vector<float> >& condicoes,
    std::vector< std::vector<float> >& certificado){

    for (int i = 0; i < custo.size(); i++) {
        if(custo[i] < 0){
            float div = 99999;
            if (condicoes[0][i] > 0) {
                div = condicoes[0][condicoes[0].size()]/condicoes[0][i];
            }
            int pivot = 0;
            for (int j = 1; j < condicoes.size(); j++) {
                if (condicoes[j][i] > 0) {
                    if (div > condicoes[j][condicoes[j].size()]/condicoes[j][i]) {
                        pivot = j;
                        div = condicoes[j][condicoes[j].size()]/condicoes[j][i];
                    }
                }
            }
            pivotation(custo, condicoes, certificado, pivot, i);
            printall(custo,condicoes,certificado);
        }
    }
}

void simplex_init(
    std::vector<float> custo,
    std::vector< std::vector<float> > condicoes,
    std::vector< std::vector<float> > certificado){

    fpi_base_canonica(custo, condicoes, condicoes.size());
    printall(custo,condicoes,certificado);

    simplex(custo, condicoes, certificado);

    // printall(custo,condicoes,certificado);


}
