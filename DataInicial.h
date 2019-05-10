#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <tuple>

using namespace std;

tuple<
    std::vector<float>,
    std::vector< std::vector<float> >,
    std::vector< std::vector<float> >
    > create_vecs(int n_var, int n_res){
        std::vector<float> custo;
        custo.resize(n_var+1);

        std::vector< std::vector<float> > condicoes;
        condicoes.resize(n_res);
        for(int i = 0 ; i < n_res ; i++){
            condicoes[i].resize(n_var+1);
        }

        std::vector< std::vector<float> > certificado;
        certificado.resize(n_res+1);
        certificado[0].resize(n_res);
        for(int i = 1 ; i < certificado.size() ; i++){
            certificado[i].resize(n_res);
            certificado[i][i-1] = 1;
          }

        return {custo, condicoes, certificado};
}

tuple<int, int> get_n(ifstream& data){
    int n_var,n_res;
    string line;
    getline(data,line);
    int pos = line.find(" ");
    n_res = atoi(line.substr(0,pos).c_str());
    n_var= atoi(line.substr(pos+1).c_str());
    return {n_res, n_var};
}

void get_custo(ifstream& data, int n_var, std::vector<float>& custo){
    string line;
    getline(data,line);
    int counter = 0;
    while (counter < n_var) {
        int pos = line.find(" ");
        int teste = atof(line.substr(0,pos).c_str());
        line.erase(0,pos+1);
        custo[counter] = teste;
        counter++;
    }
}

void get_condicoes(ifstream& data, int n_var, int n_res, std::vector< std::vector<float> >& condicoes){
    string line;
    int counter = 0;
    int counter_res = 0;
    while (counter_res < n_res) {
        getline(data,line);
        counter = 0;
        while (counter < (n_var + 1)) {
            int pos = line.find(" ");
            int aux = atof(line.substr(0,pos).c_str());
            line.erase(0,pos+1);
            condicoes[counter_res][counter] = aux;
            counter++;
        }
        counter_res++;
    }
}




tuple<
    std::vector<float>,
    std::vector< std::vector<float> >,
    std::vector< std::vector<float> >
    > read_file(char const *f) {
    ifstream data;
    data.open(f);

    string line;

    auto [n_res, n_var] = get_n(data);
    auto [custo, condicoes, certificado] = create_vecs(n_var,n_res);

    get_custo(data,n_var,custo);

    get_condicoes(data,n_var,n_res,condicoes);


    return {custo, condicoes, certificado};
}
