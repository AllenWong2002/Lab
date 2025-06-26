#include "Alg.h"

int main(int argc, char *argv[])
{
    int Bit = atoi(argv[1]);            // 位元數
    int Run = atoi(argv[2]);            // 執行次數
    int Iter = atoi(argv[3]);           // 世代數
    int population = atoi(argv[4]);     // 種群大小

    Alg algorithm;
    algorithm.RunALG(Bit, Run, Iter, population);
}