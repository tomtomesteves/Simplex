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

tuple<
    std::vector<float>,
    std::vector< std::vector<float> >,
    std::vector< std::vector<float> >
    > create_vecs_dual(int n_var, int n_res){

        std::vector<float> custo;
        custo.resize(n_var+1);
        std::vector< std::vector<float> > condicoes;
        condicoes.resize(n_var);
        for(int i = 0 ; i < n_res ; i++){
            condicoes[i].resize(n_res+1);
        }

        std::vector< std::vector<float> > certificado;
        certificado.resize(n_var+1);
        certificado[0].resize(n_var);
        for(int i = 1 ; i < certificado.size() ; i++){
            certificado[i].resize(n_var);
            certificado[i][i-1] = 1;
          }

        return {custo, condicoes, certificado};
}

void pivotation(
    std::vector<float>& custo,
    std::vector< std::vector<float> >& condicoes,
    std::vector< std::vector<float> >& certificado,
    int pivot_y, int pivot_x){

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
                cout << "antes pivot :: " << condicoes[j][i] << endl;
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

void dual(
  std::vector<float> custo,
  std::vector< std::vector<float> > condicoes,
  std::vector< std::vector<float> > certificado) {
  auto [custo_dual, condicoes_dual , certificado_dual] = create_vecs_dual(custo.size(),condicoes.size());
  printall(custo_dual,condicoes_dual,certificado_dual);

  for (int i = 0; i < custo_dual.size()-2; i++) {
    custo_dual[i] = condicoes[i][condicoes.size()-1];
  }
  cout << condicoes_dual.size() << endl;
  for (int i = 0; i < condicoes_dual.size()-1; i++) {
    condicoes_dual[i][condicoes_dual.size()-1] = custo[i];
    for (int  j = 0; j < condicoes_dual[i].size()-1; j++) {
      condicoes_dual[i][j] = condicoes[j][i];
    }
  }

}

std::vector<float> pl_auxiliar(
  std::vector<float> custo,
    std::vector< std::vector<float> > condicoes,
    std::vector< std::vector<float> > certificado){

      printall(custo, condicoes, certificado);

      int custo_old_size = custo.size();
      custo.resize(custo.size()+condicoes.size());
      for (int i = 0; i < custo.size(); i++) {
        custo[i] = 0;
      }
      for (int i = custo_old_size-1; i < custo.size()-1; i++) {
        custo[i] = -1;
      }
      // printall(custo, condicoes, certificado);

      int old = condicoes.size();
      int old_col = condicoes[0].size();
      for (int i = 0; i < old; i++) {
        condicoes[i].resize(condicoes[i].size() + condicoes.size());
        condicoes[i][condicoes[i].size()-1] = condicoes[i][old_col-1];
        condicoes[i][old_col-1] = 0;
      }
      for (int i = 0; i < condicoes.size(); i++) {
        if (condicoes[i][condicoes[i].size()-1] < 0) {
          for (int j = 0; j < condicoes[i].size(); j++) {
            if (condicoes[i][j] != 0) {
              condicoes[i][j] = -condicoes[i][j];
            }
          }
        }
      }
      for (int i = 0; i < condicoes.size(); i++) {
        condicoes[i][i+old_col-1] = 1;
      }
      for (int i = 0; i < custo.size()-1; i++) {
        int sum = 0;
        for (int j = 0; j < condicoes.size(); j++) {
          sum += condicoes[j][i];
        }
        custo[i] += sum;
      }
      for (int i = 0; i < custo.size()-1; i++) {
        if (custo[i] != 0) {
          custo[i] = -custo[i];
        }
      }
      cout << "testando pl aux" << endl;
      printall(custo, condicoes, certificado);
      float vo = simplex(custo, condicoes, certificado);
      if (vo == 0 ){
        cout << vo <<  "  uhulleeess" << endl;
        return certificado[0];
      }
      else {
        cout << "deu ruimmm" << endl;

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

    printall(custo, condicoes, certificado);
    for (int i = 0; i < condicoes.size(); i++) {
      if (condicoes[i][condicoes[i].size()-1] < 0) {
        cout << "criando aux" << endl;
        auto viavel = pl_auxiliar(custo,condicoes,certificado);
        // dual(custo,condicoes,certificado);

        break;
      }
    }
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
