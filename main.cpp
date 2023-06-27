#include <iostream>
#include<vector>
#include<string>
#include <cmath>
#include <fstream>

using namespace std;
vector<vector<int>> dp;
vector<vector<int>> dp2;

int minDistance(string word1, string word2);
int solve(int i, int j, const string &word1, const string &word2);
int verificar(string word1, string word2, int D);
int solve2(int i, int j, const string &word1, const string &word2);
int adaptiva(string word1, string word2);

int main()
{

    srand(time(NULL));
    //Abrir archivos de texto...
    string w1 = "";
    string w2 = "";
    string nombreArchivo1 = ".txt";
    ifstream archivo(nombreArchivo.c_str());
    string linea;
    // Obtener línea de archivo, y almacenar contenido en "linea"
    while (getline(archivo, linea)) {
        w1 += linea;
    }
    string nombreArchivo2 = ".txt";
    ifstream archivo2(nombreArchivo2.c_str());
    string linea2;
    // Obtener línea de archivo, y almacenar contenido en "linea"
    while (getline(archivo2, linea2)) {
        w2 += linea2;
    }

    //Medir tiempo
    string outfile_name =  "programacion_dinamica_d1.csv";
  	ofstream outfile(outfile_name);
  	string column_names = "distancia,time[ms],metodo\n";
  	outfile << column_names;
	//forma clasica
	double mm_total_time = 0;
  	auto start_time = std::chrono::high_resolution_clock::now();
  	int n1 = clasica(w1, w2);
    auto end_time = std::chrono::high_resolution_clock::now();
	mm_total_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
	outfile << n1 << "," << mm_total_time<< ","  <<"Clasico"<<endl;

    //forma adaptativa
	double mm_total_time = 0;
  	auto start_time = std::chrono::high_resolution_clock::now();
  	int n2 = adaptiva(w1, w2);
    auto end_time = std::chrono::high_resolution_clock::now();
	mm_total_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
	outfile << n2 << "," << mm_total_time<< ","  <<"Adaptativo"<<endl;

	outfile.close();

    return 0;
}


int clasica(string word1, string word2) {  // Version recursiva de edit dustance entregada en clase por el ayudante y editada para solo usar insert y delete
    dp.assign(word1.size(), vector<int>(word2.size(), -1));
    return solve(0, 0, word1, word2);
}
int solve(int i, int j, const string &word1, const string &word2) {
    if (i >= word1.size() || j >= word2.size())
        return (word2.size() - j) + (word1.size() - i);
    if(i == word1.size()) return word2.size() - j;
    if(j == word2.size()) return word1.size() - i;

    if (dp[i][j] != -1) return dp[i][j];

    if (word1[i] == word2[j])
        return dp[i][j] = solve(i+1, j+1, word1, word2);

    int insert = 1 + solve(i, j+1, word1, word2);
    int dlete = 1 + solve(i+1, j, word1, word2);

    return dp[i][j] = min(insert, dlete);
}

int verificar(string word1, string word2, int D){ // version iterativa de edit distance entregada en clases por el ayudante y editada para devolver d si d < D

    int m = word1.size();
    int n = word2.size();

    int dp[m+1][n+1];
    for(int i = 0; i <= m; i++) dp[i][0] = i;
    for(int j=0; j <= n; j++) dp[0][j] = j;

    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++){
            if(word1[i-1] == word2[j-1]) dp[i][j] = dp[i-1][j-1];
            else{
                dp[i][j] = 1 + min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1]));
            }
            if(dp[i][j] > D){
                return D-1;
            }
        }
    return m+n+1;

}

int adaptiva(string word1, string word2){

    int n = word1.size();
    int m = word2.size();

    int d = -1;
    int D = 1;
    while(true){
        int result = verificar(word1, word2, D);
        if(result > D){
            break;
        }
        d = result;
        D *= 2;
    }
    if(d == n+m+1){
        dp.assign(word1.size(), vector<int>(word2.size(), -1));
        return solve(d, d, word1, word2);
    }
    else{
        dp2.assign(word1.size(), vector<int>(word2.size(), -1));
        return solve2(d, d, word1, word2);
    }
}
