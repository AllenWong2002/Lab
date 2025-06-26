#include "Alg.h"

int main(int argc, char *argv[]){
    int Bit = atoi(argv[1]);        // 位元數
    int Run = atoi(argv[2]);        // 執行次數
    int Iter = atoi(argv[3]);       // 世代數
    string problem = argv[4];       // 問題類型

    Alg algorithm;
    algorithm.RunALG(Bit, Run, Iter, problem);
}