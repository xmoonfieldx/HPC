// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//Consider a Scenario where a person visits a supermarket for shopping.He purchases various items in different sections such as clothing,gaming,grocery,stationary.Write an open MP program to process his bill parallely in each section and display the final amount to be paid. (sum of elements parallely)
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	int a[10][10], bill[10] = { 0 }, total = 0, i, j, key[10];
	srand(time(0));
	int n = rand() % 10+1;
	omp_set_num_threads(n);
#pragma omp parallel for
	for (i = 0; i < n; i++)
	{
		key[i] = rand() % 10;
		for (j = 0; j < key[i]; j++)
			a[i][j] = rand() % 20;
	}
	for (i = 0; i < n; i++)
	{
		printf("\n");
		for (j = 0; j < key[i]; j++)
			printf("%d ", a[i][j]);
	}
#pragma omp parallel for
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < key[i]; j++)
			bill[i] += a[i][j];
#pragma omp critical
		total += bill[i];
	}
	printf("\n\n");
	for (i = 0; i < n; i++)
		printf("Bill: %d ", bill[i]);
	printf("\n\n");
	printf("Total: %d", total);
}
