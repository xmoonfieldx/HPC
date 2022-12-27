// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//Consider a Scenario where a person visits a supermarket for shopping.He purchases various items in different sections such as clothing,gaming,grocery,stationary.Write an open MP program to process his bill parallely in each section and display the final amount to be paid. (sum of elements parallely)
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
int main()
{
    
    srand(time(0));
    int a[10][10], x[10], i, j,y[10]={0}, bill=0;
    int n = rand() % 7;
    for (i = 0; i < n; i++)
    {
        x[i] = rand() % 10;
        for (j = 0; j < x[i]; j++)
        {
            a[i][j] = rand() % 10;
        }
    }
    omp_set_num_threads(n);
    for (i = 0; i < n; i++)
    {
        printf("\n");
        for (j = 0; j < x[i]; j++)
            printf("%d ", a[i][j]);
    }
    printf("\n\n");
#pragma omp parallel for
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < x[i]; j++)
        {
            y[i] += a[i][j];
        }
#pragma omp critical
        bill += y[i];
    }
        printf("\nBill: %d ", bill);
}

