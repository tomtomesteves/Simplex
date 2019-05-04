#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <tuple>
#include <cmath>

using namespace std;

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
    bool positivo = false;
    for (int i = 0; i < condicoes.size(); i++) {
      if (i != pivot_y){
        if (condicoes[i][pivot_x] != 0) {
          int mod = condicoes[i][pivot_x]/condicoes[pivot_y][pivot_x];
          if (condicoes[i][pivot_x]-(mod*condicoes[pivot_y][pivot_x]) == 0) {
            for (int j = 0; j < condicoes[i].size(); j++) {
              condicoes[i][j] = condicoes[i][j]-(mod*condicoes[pivot_y][j]);
            }
            for (int j = 0; j < certificado[i].size(); j++) {
              certificado[i+1][j] = certificado[i+1][j]-(mod*certificado[pivot_y+1][j]);
            }
          }
          else {
            for (int j = 0; j < condicoes[i].size(); j++) {
              condicoes[i][j] = condicoes[i][j]+(mod*condicoes[pivot_y][j]);
            }
            for (int j = 0; j < certificado[i].size(); j++) {
              certificado[i+1][j] = certificado[i+1][j]+(mod*certificado[pivot_y+1][j]);
            }
          }
        }
      }
    }
    int mod;
    if (custo[pivot_x] != 0) {
      mod = custo[pivot_x]/condicoes[pivot_y][pivot_x];
      for (int j = 0; j < custo.size(); j++) {
        if (custo[j]+(mod*condicoes[pivot_y][j]) == 0) {
          custo[j] = custo[j]+(mod*condicoes[pivot_y][j]);
          positivo = true;
        }
        else {
          custo[j] = custo[j]-(mod*condicoes[pivot_y][j]);
        }
      }
    }
    if (positivo) {
      for (int i = 0; i < certificado[0].size(); i++) {
        certificado[0][i] = certificado[0][i]+(mod*certificado[pivot_y+1][i]);
      }
    }
    else {
      for (int i = 0; i < certificado[0].size(); i++) {
        certificado[0][i] = certificado[0][i]-(mod*certificado[pivot_y+1][i]);
      }
    }
}


float simplex(
    std::vector<float>& custo,
    std::vector< std::vector<float> >& condicoes,
    std::vector< std::vector<float> >& certificado){
    bool inviavel = true;
    for (int i = 0; i < custo.size()-1; i++) {
        if(custo[i] < 0){
            float div = 999999;
            int pivot = 0;
            for (int j = 0; j < condicoes.size(); j++) {
              if (condicoes[j][i] > 0 && div > condicoes[j][condicoes[j].size()]/condicoes[j][i]) {
                  div = condicoes[j][condicoes[j].size()]/condicoes[j][i];
                  pivot = j;
                  inviavel = false;
              }
            }
            if(!inviavel){
              pivotation(custo, condicoes, certificado, pivot, i);
              printall(custo,condicoes,certificado);
            }
            if(inviavel){
              cout << "ilimitada" << endl;
              return {};
            }
            i = 0;
        }
    }
    return custo[custo.size()-1];
}

void check_custo(std::vector<float>& custo){
    for (int i = 0; i < custo.size(); i++) {
        if (custo[i] < 0) {
            std::cout << "inviavel" << endl <<"vetor custo < 0" << '\n';
        }
    }
}

std::vector<float> pl_auxiliar(
    std::vector<float> custo,
    std::vector< std::vector<float> > condicoes,
    std::vector< std::vector<float> > certificado){
      for (int i = 0; i < custo.size(); i++) {
        custo[i] = 0;
      }
      custo.resize(custo.size()+condicoes.size(), -1);
      int old = condicoes.size();
      for (int i = 0; i < old; i++) {
        condicoes[i].resize(condicoes[i].size() + condicoes.size());
      }
      for (int i = old; i < condicoes[0].size(); i++) {
        condicoes[i][i] = 1;
      }
      for (int i = 0; i < custo.size(); i++) {
        int sum = 0;
        for (int j = 0; j < condicoes.size(); j++) {
          sum += condicoes[j][i];
        }
        custo[i] += sum;
      }
      float vo = simplex(custo, condicoes, certificado);
      if (vo == 0 ){
        return certificado[0];
      }
      else {
        return {};
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

void fpi_base_canonica(
    std::vector<float>& custo,
    std::vector< std::vector<float> >& condicoes,
    std::vector< std::vector<float> >& certificado,
    int n_res){
    if (!check_valid_base(custo,condicoes)) {
        custo.resize(custo.size()+n_res);


        int old_size = condicoes[0].size();
        for (int i = 0; i < condicoes.size(); i++) {
            condicoes[i].resize(old_size+n_res);
            condicoes[i][condicoes[i].size()-1] = condicoes[i][old_size-1];
            condicoes[i][old_size-1] = 0;
        }

        for (int i = 0; i < condicoes.size(); i++) {
            condicoes[i][old_size-1] = 1;
            old_size += 1;
        }
    }
    for (int i = 0; i < custo.size(); i++) {
        if (custo[i] != 0) {
            custo[i] = -custo[i];
          }
    }
    for (int i = 0; i < condicoes.size(); i++) {
      if (condicoes[i][condicoes[i].size()-1] < 0) {
        auto viavel = pl_auxiliar(custo,condicoes,certificado);
        break;
      }
    }
}





void simplex_init(
    std::vector<float> custo,
    std::vector< std::vector<float> > condicoes,
    std::vector< std::vector<float> > certificado){
    // printall(custo,condicoes,certificado);

    fpi_base_canonica(custo, condicoes,certificado ,condicoes.size());
    printall(custo,condicoes,certificado);

    float vo = simplex(custo, condicoes, certificado);

    cout << "saiuuuuuuuuuuu" << endl;
}
