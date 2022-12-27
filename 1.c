
//Given a nxn matrix A and a vector x of length n, their product y=A⋅x, write a program to implement the multiplication using OpenMP PARALLEL directive.
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
int main()
{
    
    srand(time(0));
    int a[10][10], x[10], i, j,y[10]={0};
    int n = rand() % 4;
    for (i = 0; i < n; i++)
    {
        x[i] = rand() % 10;
        for (j = 0; j < n; j++)
        {
            a[i][j] = rand() % 10;
        }
    }
    for (i = 0; i < n; i++)
    {
        printf("\n");
        for (j = 0; j < n; j++)
            printf("%d ", a[i][j]);
    }
    printf("\n\n");
    for (i = 0; i < n; i++)
        printf("%d ", x[i]);
    printf("\n");
#pragma omp parallel for
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            y[i] += a[i][j] * x[j];
        }
    }
    for (i = 0; i < n; i++)
        printf("%d ", y[i]);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
