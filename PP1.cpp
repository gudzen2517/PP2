#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "time.h"
#include <fstream>
#include <string>
#include <omp.h>
using namespace std;

double go(double** a, double** b, double** c, int N)
{
    a = new double* [N];
    cout << "Ввод элементов первой матрицы..." << endl;
    for (int i = 0; i < N; i++)
    {
        a[i] = new double[N];
        for (int j = 0; j < N; j++)
        {
            a[i][j] = rand() % 10;
        }
    }
    ofstream fout;
    fout.open("A.txt");
  

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            fout << a[i][j] << ' ';
        fout << '\n';
    }
    fout.close();
    cout << "comlete write file A.txt!\n";





    ifstream fin;
    fin.open("A.txt");
    double** A = new double* [N];
    cout << "new A: \n";
    for (int i = 0; i < N; i++)
    {
        A[i] = new double[N];
        for (int j = 0; j < N; j++)
        {
            fin >> A[i][j];
        }
    }
    fin.close();



    b = new double* [N];
    cout << "Ввод элементов второй матрицы..." << endl;
    for (int i = 0; i < N; i++)
    {
        b[i] = new double[N];
        for (int j = 0; j < N; j++)
        {
            b[i][j] = rand() % 10;
        }
    }

    fout.open("B.txt");

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            fout << b[i][j] << ' ';
        fout << '\n';

    }
    fout.close();
    cout << "comlete write file B.txt!\n";


    fin.open("B.txt");
    double** B = new double* [N];
    cout << "new B: \n";
    for (int i = 0; i < N; i++)
    {
        B[i] = new double[N];
        for (int j = 0; j < N; j++)
        {
            fin >> B[i][j];
        }
    }
    fin.close();
    cout << "complete read files!\n";

    c = new double* [N];
    size_t count = 0;
    clock_t start = clock();
    double wtime = omp_get_wtime();
    int threads;
    omp_set_num_threads(8);
#pragma omp parallel shared(threads)
    {
        threads = omp_get_num_threads();
#pragma omp for
        for (int i = 0; i < N; i++)
        {
            c[i] = new double[N];
            for (int j = 0; j < N; j++)
            {
                c[i][j] = 0;
                for (int k = 0; k < N; k++)
                    c[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    wtime = omp_get_wtime() - wtime;
    cout << "Elapsed omp time: " << wtime << " seconds" << endl;
    double result_time = double(clock() - start) / CLOCKS_PER_SEC;
    cout << endl << "Calculation time:" << result_time << " seconds" << endl;
    cout << "Матрица произведения посчитана!" << endl;
    fout.open("C.txt");

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            fout << c[i][j] << ' ';
        fout << '\n';
    }
    fout.close();

    return result_time;
}

int main()
{
    int N = 500;
    double** a = NULL, ** b = NULL, ** c = NULL;
    system("cls");

    ofstream fio;
    fio.open("info.txt");
    for (int i = 0; i < 9; i++)
    {
        fio << N;
        fio << '\n';
        fio << "Calculation time for " << N << '*' << N << " matrix = " << go(a, b, c, N) << " seconds\n";
        N += 250;
        cout << i + 1 << endl;
    }


    fio.close();

    return 0;
}